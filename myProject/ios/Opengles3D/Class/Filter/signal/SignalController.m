//
//  SignalController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/15.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "SignalController.h"
#import "SignalView.h"
#import "OpenglesTool.h"
#import <AVFoundation/AVFoundation.h>
#include "XMCamera.h"

@interface SignalController ()

@property (nonatomic, assign) BOOL          isFirst;

@property (nonatomic, weak) SignalView       *blendView;

@property (nonatomic, strong) XMCamera      *camera;

@end

@implementation SignalController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.navigationController.navigationBarHidden = YES;
    
    self.camera = [[XMCamera alloc] init];
    
    self.isFirst = YES;
    
    SignalView *bView = [[SignalView alloc] initWithFrame:self.view.bounds];
    self.blendView = bView;
    [self.view addSubview:bView];
    
    __weak __typeof(self)weakSelf = self;
    self.camera.VideoDataBlock = ^(unsigned char *buffer, size_t width, size_t height) {
        __strong __typeof(weakSelf)strongSelf = weakSelf;
        [strongSelf.blendView needRend:buffer width:(int)width height:(int)height];
    };
    
    [self.camera startCaptureSession];
    
    
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}






@end
