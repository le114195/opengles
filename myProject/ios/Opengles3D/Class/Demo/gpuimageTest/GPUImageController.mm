//
//  GPUImageController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/25.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "GPUImageController.h"
#import "GPUImage.h"
#include "OpencvHeader.h"
#include <math.h>
#include <limits>
#include <opencv2/imgproc.hpp>

using namespace cv;


@interface GPUImageController ()

@property (nonatomic, strong) UIImageView       *imgView;
    
@end

@implementation GPUImageController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.imgView = [[UIImageView alloc] initWithFrame:self.view.bounds];
    
    [self.view addSubview:self.imgView];
    
    UIImage *image = [UIImage imageNamed:@"test002.jpg"];
    
    
    
    GPUImageBilateralFilter *twofilter = [[GPUImageBilateralFilter alloc] init];
    [twofilter setValue:@2.0 forKey:@"blurRadiusInPixels"];
    
    UIImage *newImg = [twofilter imageByFilteringImage:image];
    
    GPUImageSmoothToonFilter *filter = [[GPUImageSmoothToonFilter alloc] init];
    
    [filter setValue:@1.6 forKey:@"blurRadiusInPixels"];
    [filter setValue:@0.16 forKey:@"threshold"];
    [filter setValue:@10.0 forKey:@"quantizationLevels"];
    

    self.imgView.image = [filter imageByFilteringImage:newImg];
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*

cv::Mat L0Smoothing(cv::Mat &im8uc3, double lambda = 2e-2, double kappa = 2.0) {
    // convert the image to double format
    int row = im8uc3.rows, col = im8uc3.cols;
    cv::Mat S;
    im8uc3.convertTo(S, CV_64FC3, 1. / 255.);
    // 2*2 的卷积核
    cv::Mat fx(1, 2, CV_64FC1);
    cv::Mat fy(2, 1, CV_64FC1);
    fx.at<double>(0) = 1; fx.at<double>(1) = -1;
    fy.at<double>(0) = 1; fy.at<double>(1) = -1;
    
    // 把一个空间点扩散函数转换为频谱面的光学传递函数
    cv::Size sizeI2D = im8uc3.size();
    cv::Mat otfFx = psf2otf(fx, sizeI2D);
    cv::Mat otfFy = psf2otf(fy, sizeI2D);
    
    // FNormin1 = fft2(S);
    cv::Mat FNormin1[3];    // 注意：DFT以后，FNormal为两个通道
    cv::Mat single_channel[3];
    cv::split(S, single_channel);   // 分裂为三个通道
    for (int k = 0; k < 3; k++) {
        // 离散傅里叶变换，指定输出复数格式（默认是CCS格式）
        cv::dft(single_channel[k], FNormin1[k], cv::DFT_COMPLEX_OUTPUT);
    }
    
    // F(∂x)∗F(∂x)+F(∂y)∗F(∂y);
    cv::Mat Denormin2(row, col, CV_64FC1);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cv::Vec2d &c1 = otfFx.at<cv::Vec2d>(i, j);
            cv::Vec2d &c2 = otfFy.at<cv::Vec2d>(i, j);
            // 0: Real, 1: Image
            Denormin2.at<double>(i, j) = sqrt(c1[0]) + sqrt(c1[1]) + sqrt(c2[0]) + sqrt(c2[1]);
        }
    }
    
    double beta = 2.0*lambda;
    double betamax = 1e5;
    
    while (beta < betamax) {
        // F(1)+β(F(∂x)∗F(∂x)+F(∂y)∗F(∂y))
        cv::Mat Denormin = 1.0 + beta*Denormin2;
        
        // h-v subproblem
        // 三个通道的 ∂S/∂x ∂S/∂y
        cv::Mat dx[3], dy[3];
        for (int k = 0; k < 3; k++) {
            cv::Mat shifted_x = single_channel[k].clone();
            circshift(shifted_x, 0, -1);
            dx[k] = shifted_x - single_channel[k];
            
            cv::Mat shifted_y = single_channel[k].clone();
            circshift(shifted_y, -1, 0);
            dy[k] = shifted_y - single_channel[k];
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // (∂S/∂x)^2 + (∂S/∂y)^2
                double val =
                sqrt(dx[0].at<double>(i, j)) + sqrt(dy[0].at<double>(i, j)) +
                sqrt(dx[1].at<double>(i, j)) + sqrt(dy[1].at<double>(i, j)) +
                sqrt(dx[2].at<double>(i, j)) + sqrt(dy[2].at<double>(i, j));
                
                // (∂S/∂x)^2 + (∂S/∂y)^2  < λ/β
                if (val < lambda / beta) {
                    dx[0].at<double>(i, j) = dx[1].at<double>(i, j) = dx[2].at<double>(i, j) = 0.0;
                    dy[0].at<double>(i, j) = dy[1].at<double>(i, j) = dy[2].at<double>(i, j) = 0.0;
                }
            }
        }
        
        // S subproblem
        for (int k = 0; k < 3; k++) {
            // 二阶导
            cv::Mat shift_dx = dx[k].clone();
            circshift(shift_dx, 0, 1);
            cv::Mat ddx = shift_dx - dx[k];
            
            cv::Mat shift_dy = dy[k].clone();
            circshift(shift_dy, 1, 0);
            cv::Mat ddy = shift_dy - dy[k];
            
            cv::Mat Normin2 = ddx + ddy;
            cv::Mat FNormin2;
            // 离散傅里叶变换，指定输出复数格式（默认是CCS格式）
            cv::dft(Normin2, FNormin2, cv::DFT_COMPLEX_OUTPUT);
            
            // F(g)+β(F(∂x)∗F(h)+F(∂y)∗F(v))
            cv::Mat FS = FNormin1[k] + beta*FNormin2;
            
            // 论文的公式(8)：F^-1括号中的内容
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    FS.at<cv::Vec2d>(i, j)[0] /= Denormin.at<double>(i, j);
                    FS.at<cv::Vec2d>(i, j)[1] /= Denormin.at<double>(i, j);
                    //std::cout<< FS.at<cv::Vec2d>(i, j)[0] / Denormin.at<double>(i, j) <<std::endl;
                }
            }
            
            // 论文的公式(8)：傅里叶逆变换
            cv::Mat ifft;
            cv::idft(FS, ifft, cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    single_channel[k].at<double>(i, j) = ifft.at<cv::Vec2d>(i, j)[0];
                    //std::cout<< ifft.at<cv::Vec2d>(i, j)[0] <<std::endl;
                }
            }
        }
        beta *= kappa;
        std::cout << '.';
    }  
    cv::merge(single_channel, 3, S);  
    return S;  
}


cv::Mat psf2otf(cv::Mat psf, cv::Size size)
{
    cv::Mat otf = cv::Mat::zeros(size.height,size.width,psf.type());
    
    // Pad the PSF to outSize
    cv::Size dftSize;
    
    // compute the size of DFT transform
    dftSize.width  = getOptimalDFTSize(size.width);
    dftSize.height = getOptimalDFTSize(size.height);
    
    // allocate temporary buffers and initialize them with 0's
    cv::Mat temp(dftSize, psf.type(), Scalar::all(0));
    
    //copy psf to the top-left corners of temp
    cv::Mat roipsf(temp,cv::Rect(0,0,psf.cols,psf.rows));
    psf.copyTo(roipsf);
    
    // Circularly shift otf so that the "center" of the PSF is at the
    // (0,0) element of the array.
    Mat psf2 = temp.clone();
    
    int cx = psf.cols/2;
    int cy = psf.rows/2;
    
    cv::Mat p0(temp, cv::Rect(0, 0, cx, cy));                   // Top-Left - Create a ROI per quadrant
    cv::Mat p1(temp, cv::Rect(cx, 0, psf2.cols-cx, cy));            // Top-Right
    cv::Mat p2(temp, cv::Rect(0, cy, cx, psf2.rows - cy));      // Bottom-Left
    cv::Mat p3(temp, cv::Rect(cx,cy, psf2.cols-cx, psf2.rows - cy)); // Bottom-Right
    
    
    cv::Mat q0(psf2, cv::Rect(0, 0,  psf2.cols-cx, psf2.rows - cy));// Top-Left - Create a ROI per quadrant
    cv::Mat q1(psf2, cv::Rect(psf2.cols-cx, 0, cx, psf2.rows - cy));// Top-Right
    cv::Mat q2(psf2, cv::Rect(0, psf2.rows - cy, psf2.cols-cx, cy));        // Bottom-Left
    cv::Mat q3(psf2, cv::Rect(psf2.cols-cx, psf2.rows - cy,cx,cy)); // Bottom-Right
    
    // swap quadrants (Top-Left with Bottom-Right)
    p0.copyTo(q3);
    p3.copyTo(q0);
    
    // swap quadrant (Top-Right with Bottom-Left)
    p1.copyTo(q2);
    p2.copyTo(q1);
    
    // Computer the OTF
    Mat planes[] = {Mat_<float>(psf2), Mat::zeros(psf2.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);
    
    dft(complexI, complexI);
    
    otf = complexI;
    
    return otf(Range(0,size.height),Range(0,size.width));
}
 
 */


@end
