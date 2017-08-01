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
    
    demo.Init();
}




- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
//    glBindFramebuffer(GL_FRAMEBUFFER, demo.frameBuffer);
    
    
    demo.buffer1 = (unsigned char *)malloc(sizeof(unsigned char) * demo.s_width * demo.s_height);
    
    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
    
    glReadPixels(0, 0, demo.s_width, demo.s_height, GL_RGBA, GL_UNSIGNED_BYTE, demo.buffer1);
    
    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
    
    free(demo.buffer1);
}





@end
