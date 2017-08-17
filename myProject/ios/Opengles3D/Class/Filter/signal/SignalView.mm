//
//  SignalView.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/15.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "SignalView.h"
#include "SignalRender.hpp"
#import "OpenglesTool.h"
#include "OpencvHeader.h"

@implementation SignalView
{
    SignalRender demo;
    
    double lastTime;
    
    int    blend_t;
    
    float speed;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    if ([super initWithFrame:frame]) {
        blend_t = 0;
        lastTime = 0;
        speed = 1.0;
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
    
    demo.setupFrameBuffer2();
//    
//    demo.render(0);
//    
//    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
//    [_context presentRenderbuffer:GL_RENDERBUFFER];
}


- (void)setupGLData
{
    demo.vShader = [OpenglesTool readFileData:@"origin_shader.vs"];
    demo.fShader = [OpenglesTool readFileData:@"origin_shader.frag"];
    
    
    //运动模糊
    demo.motionVShader = [OpenglesTool readFileData:@"motionblur_shader.vs"];
    demo.motionFShader = [OpenglesTool readFileData:@"motionblur_shader.frag"];
    
    //随机噪声
    demo.randNoseVShader = [OpenglesTool readFileData:@"rand_nose_shader.vs"];
    demo.randNoseFShader = [OpenglesTool readFileData:@"rand_nose_shader.frag"];
    
    //线条
    demo.lineVShader = [OpenglesTool readFileData:@"normal_blend_shader.vs"];
    demo.lineFShader = [OpenglesTool readFileData:@"normal_blend_shader.frag"];
    
    //信号干扰
    demo.signalVShader = [OpenglesTool readFileData:@"signal_shader.vs"];
    demo.signalFShader = [OpenglesTool readFileData:@"signal_shader.frag"];
    
    //位置偏移
    demo.offsetVShader = [OpenglesTool readFileData:@"offset_shader.vs"];
    demo.offsetFShader = [OpenglesTool readFileData:@"offset_shader.frag"];
    
    //alpha_blend
    demo.alphaVShader = [OpenglesTool readFileData:@"alpha_blend_shader.vs"];
    demo.alphaFShader = [OpenglesTool readFileData:@"alpha_blend_shader.frag"];
    
    demo.s_width = self.frame.size.width;
    demo.s_height = self.frame.size.height;
    
    demo.Init();
    
    //    UIImage *originImg = [UIImage imageNamed:@"blend_origin.png"];
    //    unsigned char *buffer = [OpenglesTool getBuffer:originImg];
    //    demo.textureId = createTexture2D(GL_RGBA, originImg.size.width, originImg.size.height, buffer);
    
    UIImage *blendImg = [UIImage imageNamed:@"nose_alpha60.png"];
    unsigned char *blendBuffer = [OpenglesTool getBuffer:blendImg];
    demo.blendTextureId = createTexture2D(GL_RGBA, blendImg.size.width, blendImg.size.height, blendBuffer);
    
    UIImage *lineBlendImg = [UIImage imageNamed:@"line2.png"];
    unsigned char *lineBlendBuffer = [OpenglesTool getBuffer:lineBlendImg];
    demo.lineBlendTexture = createTexture2D(GL_RGBA, lineBlendImg.size.width, lineBlendImg.size.height, lineBlendBuffer);
    
    UIImage *edgeBlendImg = [UIImage imageNamed:@"edge_dim.png"];
    unsigned char *edgeBlendBuffer = [OpenglesTool getBuffer:edgeBlendImg];
    demo.edgeTexture = createTexture2D(GL_RGBA, edgeBlendImg.size.width, edgeBlendImg.size.height, edgeBlendBuffer);
    
    UIImage *noseBlendImg = [UIImage imageNamed:@"nose8.png"];
    unsigned char *noseBlendBuffer = [OpenglesTool getBuffer:noseBlendImg];
    demo.noseBlendTextureId = createTexture2D(GL_RGBA, noseBlendImg.size.width, noseBlendImg.size.height, noseBlendBuffer);
    
    
    free(noseBlendBuffer);
    free(lineBlendBuffer);
    free(blendBuffer);
}


- (void)needRend:(unsigned char *)buffer width:(int)width height:(int)height {
    
    double time = (double)[[NSDate date] timeIntervalSince1970] * 1000;
    
    if (lastTime == 0) {
        lastTime = time;
    }
    
    demo.setTexture(buffer, width, height, GL_RGBA);
    
    demo.rend((time - lastTime) * speed);
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
    lastTime = time;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    speed *= 0.5;
    if (speed < 0.1) {
        speed = 1.0;
    }
}




@end
