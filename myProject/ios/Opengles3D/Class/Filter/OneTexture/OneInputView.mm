//
//  OneInputView.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/3.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "OneInputView.h"
#import "OpenglesTool.h"
#include "one_input.hpp"

@implementation OneInputView
{
    OneInput_C demo;
    BOOL xx;
}


- (instancetype)initWithFrame:(CGRect)frame
{
    if ([super initWithFrame:frame]) {
        [self setupGLData];
        xx = YES;
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
    demo.vShader = [OpenglesTool readFileData:@"sketch_shader.vs"];
    demo.fShader = [OpenglesTool readFileData:@"sketch_shader.frag"];
    
    demo.toonVShader = [OpenglesTool readFileData:@"toon_shader.vs"];
    demo.toonFSahder = [OpenglesTool readFileData:@"toon_shader.frag"];
    
    demo.s_width = self.frame.size.width;
    demo.s_height = self.frame.size.height;
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    unsigned char *buffer = [OpenglesTool getBuffer:image];
    
    demo.s_width = self.frame.size.width;
    demo.s_height = self.frame.size.height;
    
//    demo.textureId = createTexture2D(GL_RGBA, image.size.width, image.size.height, buffer);
    
    demo.setTexture(buffer, image.size.width, image.size.height, GL_RGBA);
    
    
    demo.Init();
}


- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    xx = !xx;
    if (xx) {
        demo.render();
    }else {
        demo.renderToon();
    }
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}




@end
