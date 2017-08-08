//
//  MultipleSampleController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/27.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "MultipleSampleController.h"
#import "MultipleSampleView.h"
#import "XMCamera.h"


@interface MultipleSampleController ()

@property (nonatomic, strong) XMCamera      *camera;

@property (nonatomic, strong) MultipleSampleView *filterView;

@end

@implementation MultipleSampleController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.camera = [[XMCamera alloc] init];
    
    // Do any additional setup after loading the view.
    self.filterView = [[MultipleSampleView alloc] initWithFrame:self.view.bounds];
    
    [self.view addSubview:self.filterView];
    
    
    __weak __typeof(self)weakSelf = self;
    self.camera.VideoDataBlock = ^(unsigned char *buffer, size_t width, size_t height) {
        __strong __typeof(weakSelf)strongSelf = weakSelf;
        [strongSelf.filterView needRend:buffer width:(int)width height:(int)height];
    };
    
    [self.camera startCaptureSession];
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
