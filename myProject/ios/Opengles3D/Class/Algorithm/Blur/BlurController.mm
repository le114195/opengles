//
//  BlurController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/24.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "BlurController.h"
#include "filter_blur.hpp"
#import "OpenglesTool.h"
#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>

@interface BlurController ()

@property (nonatomic, assign) CGFloat       time;
@property (nonatomic, assign) int           count;

@end

@implementation BlurController

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
    _esContext.userData = malloc(sizeof(FILTER_BLUR::UserData));
    
    FILTER_BLUR::UserData *userData = (FILTER_BLUR::UserData *)_esContext.userData;
    
    userData->vShader = [OpenglesTool readFileData:@"blur_shader3.vs"];
    userData->fShader = [OpenglesTool readFileData:@"blur_shader3.frag"];
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    userData->buffer = [OpenglesTool getBuffer:image];
    userData->buffer_width = image.size.width;
    userData->buffer_height = image.size.height;
    
    FILTER_BLUR demo;
    demo.esMain(&_esContext);
}


- (void)update
{
    if ( _esContext.updateFunc )
    {
        self.time += self.timeSinceLastUpdate;
        
        int count = self.time / 0.25;
        
        if (count > self.count) {
            self.count = count;
            _esContext.updateFunc( &_esContext, self.timeSinceLastUpdate );
        }
    }
}

//- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
//{
//    _esContext.width = (GLint)view.drawableWidth;
//    _esContext.height = (GLint)view.drawableHeight;
//    
//    if ( _esContext.drawFunc )
//    {
//        _esContext.drawFunc( &_esContext );
//    }
//}

    
    
- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    int width = _esContext.width;
    int height = _esContext.height;
    
    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
    
    char *buffer = (char *)malloc(sizeof(char) * width * height * 4);
    
    FILTER_BLUR::draw_img(&_esContext, buffer, width, height);

    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
    
    cv::Mat src;
    src.create(height, width, CV_8UC4);
    memcpy(src.data, buffer, width * height * 4);
    
    UIImage *img = MatToUIImage(src);
    
    NSLog(@"%@", NSStringFromCGSize(img.size));
    
    free(buffer);
}

@end
