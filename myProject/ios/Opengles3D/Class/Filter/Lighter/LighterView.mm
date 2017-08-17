//
//  LighterView.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/17.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "LighterView.h"
#import "OpenglesTool.h"
#include "OpencvHeader.h"
#include "LighterFilter.hpp"


@implementation LighterView
{
    LighterFilter demo;
    
    double lastTime;
    
    int    blend_t;
    
    float speed;
    
    int rendStatus;
    
}
- (instancetype)initWithFrame:(CGRect)frame
{
    if ([super initWithFrame:frame]) {
        blend_t = 0;
        lastTime = 0;
        speed = 1.0;
        rendStatus = 0;
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
    
    //    demo.render(0);
    //
    //    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    //    [_context presentRenderbuffer:GL_RENDERBUFFER];
}


- (void)setupGLData
{
    demo.vShader = [OpenglesTool readFileData:@"lighter_shader.vs"];
    demo.fShader = [OpenglesTool readFileData:@"lighter_shader.frag"];
    
    
    demo.zoomVShader = [OpenglesTool readFileData:@"zoom_blur_shader.vs"];
    demo.zoomFShader = [OpenglesTool readFileData:@"zoom_blur_shader.frag"];
    
    demo.s_width = self.frame.size.width;
    demo.s_height = self.frame.size.height;
    
    demo.Init();
}


- (void)needRend:(unsigned char *)buffer width:(int)width height:(int)height {
    
    double time = (double)[[NSDate date] timeIntervalSince1970] * 1000;
    
    if (lastTime == 0) {
        lastTime = time;
    }
    
    demo.setTexture(buffer, width, height, GL_RGBA);
    
    double duration = (time - lastTime) * speed;
    
    switch (rendStatus) {
        case 0:
            demo.render(duration);
            break;
            
        case 1:
            demo.renderZoom(duration);
            break;
            
        default:
            break;
    }
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
    lastTime = time;
}


- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    rendStatus ++;
    
    if (rendStatus > 1) {
        rendStatus = 0;
    }
}


@end
