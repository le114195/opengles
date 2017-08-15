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
#include "dynamic_shader.hpp"
#include "OpencvHeader.h"
#import "UIView+XL.h"

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
    
    demo.setupFrameBuffer2();
    
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
    
    demo.bvShader = [OpenglesTool readFileData:@"bilateral_shader.vs"];
    demo.bfShader = [OpenglesTool readFileData:@"bilateral_shader.frag"];
    
    demo.tonsureVShader = [OpenglesTool readFileData:@"tonsure_shader.vs"];
    demo.tonsureFShader = [OpenglesTool readFileData:@"tonsure_shader.frag"];
    
    demo.gradualVShader = [OpenglesTool readFileData:@"gradual_shader.vs"];
    demo.gradualFShader = [OpenglesTool readFileData:@"gradual_shader.frag"];
    
    demo.signalVShader = [OpenglesTool readFileData:@"signal_shader.vs"];
    demo.signalFShader = [OpenglesTool readFileData:@"signal_shader.frag"];
    
    demo.motionVShader = [OpenglesTool readFileData:@"motionblur_shader.vs"];
    demo.motionFShader = [OpenglesTool readFileData:@"motionblur_shader.frag"];
    
    std::string vShaderStr, fShaderStr;
    
    gaussianVertexShaderStr(vShaderStr, 1.5);
    gaussianFragmentShaderStr(fShaderStr, 1.5);
    
    demo.g_vShader = vShaderStr.c_str();
    demo.g_fShader = fShaderStr.c_str();
    
    UIImage *image = [UIImage imageNamed:@"IMG_1873.JPG"];
    UIImage *image2 = [UIImage imageNamed:@"IMG_1848.JPG"];
    
    unsigned char *buffer = [OpenglesTool getBuffer:image];
    demo.buffer2 = [OpenglesTool getBuffer:image2];
    demo.buffer2_w = image2.size.width;
    demo.buffer2_h = image2.size.height;
    
    demo.s_width = self.frame.size.width;
    demo.s_height = self.frame.size.height;
    
    demo.outBuffer = (unsigned char *)malloc(sizeof(char) * demo.s_width * demo.s_height * 4);
    
    demo.setTexture(buffer, image.size.width, image.size.height, GL_RGBA);
    demo.Init();
}


- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
//    xx = !xx;
//    if (xx) {
//        demo.render();
//    }else {
//        demo.renderToon();
//    }
//    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
//    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
//    
//    glBindFramebuffer(GL_FRAMEBUFFER, demo.framebuffer2);
//    
//    glReadPixels(0, 0, demo.s_width, demo.s_height, GL_RGBA, GL_UNSIGNED_BYTE, demo.outBuffer);
//    
//    NSLog(@"%f", [[NSDate date] timeIntervalSince1970]);
//    
//    cv::Mat src;
//    src.create(demo.s_height, demo.s_width, CV_8UC4);
//    memcpy(src.data, demo.outBuffer, demo.s_width * demo.s_height * 4);
//    
//    UIImage *newImg = MatToUIImage(src);
//    
//    NSLog(@"%@", NSStringFromCGSize(newImg.size));
    
    self.controller.navigationController.title = @"算法";
    
    
}




@end
