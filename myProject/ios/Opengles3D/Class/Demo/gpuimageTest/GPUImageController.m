//
//  GPUImageController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/25.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "GPUImageController.h"
#import "GPUImage.h"

@interface GPUImageController ()

@property (nonatomic, strong) UIImageView       *imgView;
    
@end

@implementation GPUImageController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.imgView = [[UIImageView alloc] initWithFrame:self.view.bounds];
    
    [self.view addSubview:self.imgView];
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    
    
    
    GPUImageGaussianBlurFilter *filter = [[GPUImageGaussianBlurFilter alloc] init];
    
    [filter setValue:@12 forKey:@"blurRadiusInPixels"];
    
    
    self.imgView.image = [filter imageByFilteringImage:image];
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
