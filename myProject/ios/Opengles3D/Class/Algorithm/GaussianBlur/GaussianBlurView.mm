//
//  GaussianBlurView.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "GaussianBlurView.h"
#import "gaussian_blur.hpp"
#import "OpenglesTool.h"

@implementation GaussianBlurView
{
    GAUSSIAN_BLUR_DEMO demo;
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
    demo.setupFrameBuffer2();
    
    // 为 color renderbuffer 分配存储空间
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
    
    demo.render();
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupGLData
{
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    void *buffer = [OpenglesTool getBuffer:image];
    
    demo.s_width = self.frame.size.width;
    demo.s_height = self.frame.size.height;
    
    demo.Init();
    
    demo.textureId1 = createTexture2D(GL_RGBA, image.size.width, image.size.height, buffer);
    
    
}





@end
