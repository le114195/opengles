//
//  real_time_render.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/27.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "real_time_render.hpp"
#include <thread>


void REALTIMERENDER::Init()
{
    
    programObject = gl_esLoadProgram(vShader, fShader);
}

void REALTIMERENDER::thread_func()
{
    
}


void REALTIMERENDER::setTexture(unsigned char *buffer, int width, int height, GLenum format)
{
    if (textureId == 0 || textureWidth != width || textureHeight != height) {
        textureId = createTexture2D(format, width, height, buffer);
        textureWidth = width;
        textureHeight = height;
    }else {
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, buffer);
    }
}

void REALTIMERENDER::render()
{
    static GLfloat vVertices[] = {
        -1.0f,  1.0f, 0.0f,  // Position 0
        0.0f,  0.0f,        // TexCoord 0
        -1.0f, -1.0f, 0.0f,  // Position 1
        0.0f,  1.0f,        // TexCoord 1
        1.0f, -1.0f, 0.0f,  // Position 2
        1.0f,  1.0f,        // TexCoord 2
        1.0f,  1.0f, 0.0f,  // Position 3
        1.0f,  0.0f,         // TexCoord 3
    };
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    
    glUseProgram(programObject);
    
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    
    setupSignalP();
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}



void REALTIMERENDER::setupSignalP() {
    
    //信号干扰参数
    float location[3] = {0.1, 0.3, 0.5};
    float width[3] = {0.05, 0.07, 0.15};
    
    GLint locationLoc = glGetUniformLocation(programObject, "location");
    GLint widthLoc = glGetUniformLocation(programObject, "width");
    
    glUniform1fv(locationLoc, 3, location);
    glUniform1fv(widthLoc, 3, width);
}



