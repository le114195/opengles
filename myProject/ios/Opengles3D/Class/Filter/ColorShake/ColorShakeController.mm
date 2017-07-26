//
//  ColorShakeController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/24.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "ColorShakeController.h"
#include "color_shake.hpp"
#import "OpenglesTool.h"
#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>

@interface ColorShakeController ()

@end

@implementation ColorShakeController

- (void)viewDidLoad {
    [super viewDidLoad];
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
    _esContext.userData = malloc(sizeof(COLOR_SHAKE::UserData));
    
    COLOR_SHAKE::UserData *userData = (COLOR_SHAKE::UserData *)_esContext.userData;
    
    userData->vShader = [OpenglesTool readFileData:@"color_shake_shader3.vs"];
    userData->fShader = [OpenglesTool readFileData:@"color_shake_shader3.frag"];
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    userData->buffer = [OpenglesTool getBuffer:image];
    userData->buffer_width = image.size.width;
    userData->buffer_height = image.size.height;
    
    COLOR_SHAKE demo;
    demo.esMain(&_esContext);
}

- (void)update
{
    if ( _esContext.updateFunc )
    {
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

    
- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    int width = _esContext.width;
    int height = _esContext.height;
    
    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
    
    char *buffer = (char *)malloc(sizeof(char) * width * height * 4);
    
    COLOR_SHAKE::draw_img(&_esContext, buffer);
    
    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
    
    cv::Mat src;
    src.create(height, width, CV_8UC4);
    memcpy(src.data, buffer, width * height * 4);
    
    UIImage *img = MatToUIImage(src);
    
    NSLog(@"%@", NSStringFromCGSize(img.size));
    
    free(buffer);
}
    
@end
