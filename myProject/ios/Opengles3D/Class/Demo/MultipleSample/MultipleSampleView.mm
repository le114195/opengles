//
//  MultipleSampleView.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/27.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "MultipleSampleView.h"
#import "OpenglesTool.h"
#include "multiple_sample.hpp"
#include "OpencvHeader.h"

@implementation MultipleSampleView
{
    MULTIPLE_SAMPLE demo;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    if ([super initWithFrame:frame]) {
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

    //创建离屏framebuffer
    demo.setupFrameBuffer2();
    
    //渲染
    demo.render();
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupGLData
{
    demo.vShader = [OpenglesTool readFileData:@"double_sample_shader.vs"];
    demo.fShader = [OpenglesTool readFileData:@"double_sample_shader_bw.frag"];
    demo.fShader2 = [OpenglesTool readFileData:@"double_sample_shader_mosaic.frag"];
    demo.fShader3 = [OpenglesTool readFileData:@"multiple_sample_shader.frag"];
    
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    void *buffer = [OpenglesTool getBuffer:image];
    
    demo.s_width = self.frame.size.width;
    demo.s_height = self.frame.size.height;
    
    demo.textureId1 = createTexture2D(GL_RGBA, image.size.width, image.size.height, buffer);
    demo.outBuffer = (unsigned char*)malloc(sizeof(char)*demo.s_width * demo.s_height * 4);
    
    demo.Init();
}


- (void)needRend:(unsigned char *)buffer width:(int)width height:(int)height {
    
    demo.setTexture(buffer, width, height, GL_RGBA);
    
    demo.render();
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
    
    glBindFramebuffer(GL_FRAMEBUFFER, demo.framebuffer1);
    
    NSLog(@"start = %f", [[NSDate date] timeIntervalSince1970]);
    glReadPixels(0, 0, demo.s_width, demo.s_height, GL_RGBA, GL_UNSIGNED_BYTE, demo.outBuffer);
    NSLog(@"end = %f", [[NSDate date] timeIntervalSince1970]);
}



- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    glBindFramebuffer(GL_FRAMEBUFFER, demo.framebuffer2);
    
    
    
    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
    
    glReadPixels(0, 0, demo.s_width, demo.s_height, GL_RGBA, GL_UNSIGNED_BYTE, demo.outBuffer);
    
    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
    
    cv::Mat src1;
    src1.create(demo.s_height, demo.s_width, CV_8UC4);
    memcpy(src1.data, demo.outBuffer, demo.s_height * demo.s_width * 4);
    UIImage *image1 = MatToUIImage(src1);
    
    
    free(demo.buffer1);
}





@end
