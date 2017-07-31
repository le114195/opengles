//
//  RealTimeController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/27.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "RealTimeController.h"
#import "RealTimeView.h"
#import "OpenglesTool.h"
#import <AVFoundation/AVFoundation.h>
#include "XMCamera.h"



@interface RealTimeController ()

@property (nonatomic, assign) BOOL          isFirst;

@property (nonatomic, strong) RealTimeView  *realView;

@property (nonatomic, strong) XMCamera      *camera;

@end

@implementation RealTimeController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.camera = [[XMCamera alloc] init];
    
    
    
    self.isFirst = YES;
    
    self.realView = [[RealTimeView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:_realView];
    
    
    __weak __typeof(self)weakSelf = self;
    self.camera.VideoDataBlock = ^(unsigned char *buffer, size_t width, size_t height) {
        __strong __typeof(weakSelf)strongSelf = weakSelf;
        [strongSelf.realView needRend:buffer width:(int)width height:(int)height];
    };
    
    [self.camera startCaptureSession];

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



@end
