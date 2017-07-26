//
//  FrameBufferView.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "FrameBufferView.h"
#import <OpenGLES/ES2/gl.h>
#import "GLUtil.h"
#import "framebuffer.hpp"
#import "OpenglesTool.h"
#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>

@implementation FrameBufferView
{
    
//    GLuint          _program;
    
    FRAMEBUFFER_DEMO2 demo;
    
}

- (instancetype)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame]) {
        [self setupGLData];
    }
    return self;
}

- (void)layoutSubviews
{
    [EAGLContext setCurrentContext:_context];
    
    demo.destoryRenderAndFrameBuffer();
    
    demo.setupFrameAndRenderBuffer();
    
    // 为 color renderbuffer 分配存储空间
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
    
    demo.render();
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
}


- (void)setupGLData
{
    NSString *vertFile = [[NSBundle mainBundle] pathForResource:@"frame_buffer_shader.vs" ofType:nil];
    NSString *fragFile = [[NSBundle mainBundle] pathForResource:@"frame_buffer_shader.frag" ofType:nil];
    
    
    demo.vShader = vertFile.UTF8String;
    demo.fShader = fragFile.UTF8String;
    
    demo.s_width = self.frame.size.width;
    demo.s_height = self.frame.size.height;
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    void *buffer = [OpenglesTool getBuffer:image];
    demo.textureId = createTexture2D(GL_RGBA, image.size.width, image.size.height, buffer);
    demo.Init();
}


- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    int width = demo.s_width;
    int height = demo.s_height;
    
    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
    
    char *buffer = (char *)malloc(sizeof(char) * width * height * 4);

    
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    
    
    
    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
    
    cv::Mat src;
    src.create(height, width, CV_8UC4);
    memcpy(src.data, buffer, width * height * 4);
    
    UIImage *img = MatToUIImage(src);
    
    NSLog(@"%@", NSStringFromCGSize(img.size));
    
    free(buffer);
}

@end
