//
//  gaussian_blur.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "gaussian_blur.hpp"
#include <math.h>
#include <string>
#include "dynamic_shader.hpp"



void GAUSSIAN_BLUR_DEMO::setupFrameBuffer2()
{
    textureId2 = createTexture2D(GL_RGBA, s_width, s_height, NULL);
    glGenFramebuffers(1, &framebuffer1);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId2, 0);
}

void GAUSSIAN_BLUR_DEMO::Init()
{
    std::string vShaderStr, fShaderStr;
    
    gaussianVertexShaderStr(vShaderStr, 12);
    gaussianFragmentShaderStr(fShaderStr, 12);
    
    programObject = gl_esLoadProgram(vShaderStr.c_str(), fShaderStr.c_str());
    
    widthLoc = glGetUniformLocation(programObject, "texelWidthOffset");
    heightLoc = glGetUniformLocation(programObject, "texelHeightOffset");
}

void GAUSSIAN_BLUR_DEMO::render()
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
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1);
    
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glUniform1f(widthLoc, 1.0 / s_width);
    glUniform1f(heightLoc, 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId1);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    
    
    static GLfloat vVertices2[] = {
        -1.0f,  1.0f, 0.0f,  // Position 0
        0.0f,  1.0f,        // TexCoord 0
        -1.0f, -1.0f, 0.0f,  // Position 1
        0.0f,  0.0f,        // TexCoord 1
        1.0f, -1.0f, 0.0f,  // Position 2
        1.0f,  0.0f,        // TexCoord 2
        1.0f,  1.0f, 0.0f,  // Position 3
        1.0f,  1.0f,         // TexCoord 3
    };
    glUseProgram(programObject);//黑白
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices2);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices2[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glUniform1f(widthLoc, 0);
    glUniform1f(heightLoc, 1.0 / s_height);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId2);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}




