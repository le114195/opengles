//
//  OpenglesBase.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "OpenglesBase.hpp"

GLuint opengles_base::LoadTexture(void *ioContext, char *buffer, int width, int height)
{
    GLuint texId;
    
    glGenTextures ( 1, &texId );
    glBindTexture ( GL_TEXTURE_2D, texId );
    
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    
    return texId;
}

GLuint opengles_base::createVBO(GLenum target, int usage, int datSize, void *data)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(target, vbo);
    glBufferData(target, datSize, data, usage);
    return vbo;
}
