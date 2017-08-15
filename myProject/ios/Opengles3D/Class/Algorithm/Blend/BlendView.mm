//
//  BlendView.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/15.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "BlendView.h"
#import "BlendRend.hpp"
#import "OpenglesTool.h"
#include "OpencvHeader.h"

@implementation BlendView
{
    BlendRend demo;
    
    double lastTime;
    
    int    blend_t;
}


- (instancetype)initWithFrame:(CGRect)frame
{
    if ([super initWithFrame:frame]) {
        blend_t = 0;
        lastTime = 0;
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
    
    demo.render(0);
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}


- (void)setupGLData
{
    demo.vShader = [OpenglesTool readFileData:@"soft_light_shader.vs"];
    demo.fShader = [OpenglesTool readFileData:@"soft_light_shader.frag"];
    
    demo.normalVShader = [OpenglesTool readFileData:@"normal_blend_shader.vs"];
    demo.normalFShader = [OpenglesTool readFileData:@"normal_blend_shader.frag"];
    
    demo.randNoseVShader = [OpenglesTool readFileData:@"rand_nose_shader.vs"];
    demo.randNoseFShader = [OpenglesTool readFileData:@"rand_nose_shader.frag"];
    
    demo.s_width = self.frame.size.width;
    demo.s_height = self.frame.size.height;
    
    demo.Init();
    
//    UIImage *originImg = [UIImage imageNamed:@"blend_origin.png"];
//    unsigned char *buffer = [OpenglesTool getBuffer:originImg];
//    demo.textureId = createTexture2D(GL_RGBA, originImg.size.width, originImg.size.height, buffer);
    
    UIImage *blendImg = [UIImage imageNamed:@"nose_alpha60.png"];
    unsigned char *blendBuffer = [OpenglesTool getBuffer:blendImg];
    demo.blendTextureId = createTexture2D(GL_RGBA, blendImg.size.width, blendImg.size.height, blendBuffer);
    
    free(blendBuffer);
}


- (void)needRend:(unsigned char *)buffer width:(int)width height:(int)height {
    
    double time = (double)[[NSDate date] timeIntervalSince1970] * 1000;
    
    if (lastTime == 0) {
        lastTime = time;
    }
    
    demo.setTexture(buffer, width, height, GL_RGBA);
    
    demo.render(time - lastTime);
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
    
    lastTime = time;
    
}


- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    glDeleteTextures(1, &demo.blendTextureId);
    blend_t++;
    
    if (blend_t > 4) {
        blend_t = 0;
    }

    switch (blend_t) {
        case 0:

            break;
            
        default:
            break;
    }

}



@end
