//
//  RealTimeView.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/27.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "RealTimeView.h"
#import "OpenglesTool.h"
#include "real_time_render.hpp"
#include "OpencvHeader.h"

@implementation RealTimeView
{
    REALTIMERENDER demo;
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
    
    demo.render();
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}


- (void)setupGLData
{
    demo.vShader = [OpenglesTool readFileData:@"signal_shader.vs"];
    demo.fShader = [OpenglesTool readFileData:@"signal_shader.frag"];
    
    demo.s_width = self.frame.size.width;
    demo.s_height = self.frame.size.height;
    
    demo.outBuffer = (unsigned char *)malloc(sizeof(char) * demo.s_width * demo.s_height * 4);
    
    demo.Init();
}


- (void)needRend:(unsigned char *)buffer width:(int)width height:(int)height {
    
    demo.setTexture(buffer, width, height, GL_RGBA);
    
    demo.render();
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
//    glReadPixels(0, 0, demo.s_width, demo.s_height, GL_RGBA, GL_UNSIGNED_BYTE, demo.outBuffer);
}



@end
