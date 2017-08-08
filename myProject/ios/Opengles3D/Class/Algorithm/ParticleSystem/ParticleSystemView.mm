//
//  ParticleSystemView.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/7.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "ParticleSystemView.h"
#include "ParticleSystem.hpp"
#import "OpenglesTool.h"

@implementation ParticleSystemView
{
    ParticleSystem demo;
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
    demo.vShader = [OpenglesTool readFileData:@"particle_shader.vs"];
    demo.fShader = [OpenglesTool readFileData:@"particle_shader.frag"];
    
    UIImage *image = [UIImage imageNamed:@"testimg.png"];
    
    demo.s_width = self.bounds.size.width;
    demo.s_height = self.bounds.size.width;
    
    unsigned char *buffer = [OpenglesTool getBuffer:image];
    
    demo.textureId = createTexture2D(GL_RGBA, image.size.width, image.size.height, buffer);
    
    demo.Init();
}



- (void)needRend:(float)time {
    
    demo.Update(time);
    
    demo.render();
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
//    glReadPixels(0, 0, demo.s_width, demo.s_height, GL_RGBA, GL_UNSIGNED_BYTE, demo.outBuffer);
}




@end
