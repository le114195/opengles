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
#include "L0Smoothing.hpp"

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
    
//    cv::Mat src;
//    UIImageToMat(image, src);
//    cv::Mat dst = dstL0Smoothing(src);
//    UIImage *newImg = MatToUIImage(dst);
//    NSLog(@"%@", NSStringFromCGSize(newImg.size));
    
    
    
    GPUImageSmoothToonFilter *filter = [[GPUImageSmoothToonFilter alloc] init];
    
    [filter setValue:@1.5 forKey:@"blurRadiusInPixels"];
    [filter setValue:@0.25 forKey:@"threshold"];
    [filter setValue:@15.0 forKey:@"quantizationLevels"];

    
//    GPUImageToonFilter *filter = [[GPUImageToonFilter alloc] init];
//    
//    [filter setValue:@0.25 forKey:@"threshold"];
//    [filter setValue:@10.0 forKey:@"quantizationLevels"];

    
//    GPUImageBilateralFilter *filter = [[GPUImageBilateralFilter alloc] init];
    
    
    UIImage *newImage = [filter imageByFilteringImage:image];
    
    self.imgView.image = newImage;
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}




@end
