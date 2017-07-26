//
//  new_opengles_base.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "new_opengles_base.hpp"


void NEW_OPENGLES_BASE::setupFrameAndRenderBuffer()
{
    glGenRenderbuffers(1, &colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderBuffer);
    
    glGenFramebuffers(1, &frameBuffer);
    // 设置为当前 framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    // 将 _colorRenderBuffer 装配到 GL_COLOR_ATTACHMENT0 这个装配点上
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, colorRenderBuffer);
}


void NEW_OPENGLES_BASE::destoryRenderAndFrameBuffer()
{
    glDeleteFramebuffers(1, &frameBuffer);
    frameBuffer = 0;
    glDeleteRenderbuffers(1, &colorRenderBuffer);
    colorRenderBuffer = 0;
}


