//
//  L0Smoothing.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/8.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "L0Smoothing.hpp"

#include <iostream>
#include <vector>
#include "MatLib.hpp"


cv::Mat L0Smoothing2(cv::Mat &im8uc3, double lambda = 2e-2, double kappa = 2.0) {
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
            Denormin2.at<double>(i, j) = sqr(c1[0]) + sqr(c1[1]) + sqr(c2[0]) + sqr(c2[1]);
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
                sqr(dx[0].at<double>(i, j)) + sqr(dy[0].at<double>(i, j)) +
                sqr(dx[1].at<double>(i, j)) + sqr(dy[1].at<double>(i, j)) +
                sqr(dx[2].at<double>(i, j)) + sqr(dy[2].at<double>(i, j));
                
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

cv::Mat L0Smoothing(cv::Mat &im8uc3, double lambda = 2e-2, double kappa = 2.0) {
    // convert the image to double format
    int row = im8uc3.rows, col = im8uc3.cols;
    cv::Mat S;
    im8uc3.convertTo(S, CV_64FC3, 1./255.);
    
    cv::Mat fx(1,2,CV_64FC1);
    cv::Mat fy(2,1,CV_64FC1);
    fx.at<double>(0) = 1; fx.at<double>(1) = -1;
    fy.at<double>(0) = 1; fy.at<double>(1) = -1;
    
    cv::Size sizeI2D = im8uc3.size();
    cv::Mat otfFx = psf2otf(fx, sizeI2D);
    cv::Mat otfFy = psf2otf(fy, sizeI2D);
    
    cv::Mat Normin1[3];
    cv::Mat single_channel[3];
    cv::split(S, single_channel);
    for (int k = 0; k < 3; k++) {
        cv::dft(single_channel[k], Normin1[k], cv::DFT_COMPLEX_OUTPUT);
    }
    cv::Mat Denormin2(row, col, CV_64FC1);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cv::Vec2d &c1 = otfFx.at<cv::Vec2d>(i,j), &c2 = otfFy.at<cv::Vec2d>(i,j);
            Denormin2.at<double>(i,j) = sqr(c1[0]) + sqr(c1[1]) + sqr(c2[0]) + sqr(c2[1]);
        }
    }
    
    double beta = 2.0*lambda;
    double betamax = 1e5;
    
    while (beta < betamax) {
        cv::Mat Denormin = 1.0 + beta*Denormin2;
        
        // h-v subproblem
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
                double val =
                sqr(dx[0].at<double>(i,j)) + sqr(dy[0].at<double>(i,j)) +
                sqr(dx[1].at<double>(i,j)) + sqr(dy[1].at<double>(i,j)) +
                sqr(dx[2].at<double>(i,j)) + sqr(dy[2].at<double>(i,j));
                
                if (val < lambda / beta) {
                    dx[0].at<double>(i,j) = dx[1].at<double>(i,j) = dx[2].at<double>(i,j) = 0.0;
                    dy[0].at<double>(i,j) = dy[1].at<double>(i,j) = dy[2].at<double>(i,j) = 0.0;
                }
            }
        }
        
        // S subproblem
        for (int k = 0; k < 3; k++) {
            cv::Mat shift_dx = dx[k].clone();
            circshift(shift_dx, 0, 1);
            cv::Mat ddx = shift_dx - dx[k];
            
            cv::Mat shift_dy = dy[k].clone();
            circshift(shift_dy, 1, 0);
            cv::Mat ddy = shift_dy - dy[k];
            cv::Mat Normin2 = ddx + ddy;
            cv::Mat FNormin2;
            cv::dft(Normin2, FNormin2, cv::DFT_COMPLEX_OUTPUT);
            cv::Mat FS = Normin1[k] + beta*FNormin2;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    FS.at<cv::Vec2d>(i,j)[0] /= Denormin.at<double>(i,j);
                    FS.at<cv::Vec2d>(i,j)[1] /= Denormin.at<double>(i,j);
                }
            }
            cv::Mat ifft;
            cv::idft(FS, ifft, cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    single_channel[k].at<double>(i,j) = ifft.at<cv::Vec2d>(i,j)[0];
                }
            }
        }
        beta *= kappa;
        std::cout << '.';
    }
    cv::merge(single_channel, 3, S);
    return S;
}

cv::Mat dstL0Smoothing(cv::Mat src)
{
    cv::Mat res = L0Smoothing(src, 0.001);
    return res;
}

