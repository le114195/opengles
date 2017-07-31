//
//  Filter2Controller.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "Filter2Controller.h"
#import "filter_demo2.hpp"
#import "OpenglesTool.h"
#import <AVFoundation/AVFoundation.h>
#import "XMCamera.h"
#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>


@interface Filter2Controller ()<AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic, assign) CGFloat           time;

@property (nonatomic, strong) XMCamera          *camera;

@end

@implementation Filter2Controller
{
    CGFloat bufferWidth;
    CGFloat bufferHeight;
    
    unsigned char *buffer;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.camera = [[XMCamera alloc] init];
    
    [self setupGL];
    
    __weak __typeof(self)weakSelf = self;
    self.camera.VideoDataBlock = ^(unsigned char *buf, size_t width, size_t height) {
        __strong __typeof(weakSelf)strongSelf = weakSelf;
        strongSelf->buffer = buf;
        strongSelf->bufferHeight = height;
        strongSelf->bufferWidth = width;
    };
    
    [self.camera startCaptureSession];
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    memset( &_esContext, 0, sizeof( _esContext ) );
    
    
    _esContext.userData = malloc(sizeof(FILTER_DEMO2::UserData));
    
    FILTER_DEMO2::UserData *userData = (FILTER_DEMO2::UserData *)_esContext.userData;
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    userData->buffer1 = (char *)[OpenglesTool getBuffer:image];
    userData->buffer1_width = image.size.width;
    userData->buffer1_height = image.size.height;
    
    FILTER_DEMO2 demo;
    demo.esMain(&_esContext);
}



- (void)update
{
    if ( _esContext.updateFunc )
    {
        FILTER_DEMO2::UserData *userData = (FILTER_DEMO2::UserData *)_esContext.userData;
        
        userData->buffer1 = (char *)buffer;
        userData->buffer1_width = bufferWidth;
        userData->buffer1_height = bufferHeight;
        
        _esContext.updateFunc( &_esContext, self.timeSinceLastUpdate );
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    _esContext.width = (GLint)view.drawableWidth;
    _esContext.height = (GLint)view.drawableHeight;
    
    if ( _esContext.drawFunc )
    {
        _esContext.drawFunc( &_esContext );
    }
}


@end
