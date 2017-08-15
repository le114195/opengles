//
//  BlendViewController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/15.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "BlendViewController.h"
#import "BlendView.h"
#import "OpenglesTool.h"
#import <AVFoundation/AVFoundation.h>
#include "XMCamera.h"

@interface BlendViewController ()

@property (nonatomic, assign) BOOL          isFirst;

@property (nonatomic, weak) BlendView       *blendView;

@property (nonatomic, strong) XMCamera      *camera;

@end

@implementation BlendViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    self.camera = [[XMCamera alloc] init];
    
    self.isFirst = YES;
    
    BlendView *bView = [[BlendView alloc] initWithFrame:self.view.bounds];
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

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
