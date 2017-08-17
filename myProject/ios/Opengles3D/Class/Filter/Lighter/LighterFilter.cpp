//
//  LighterFilter.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/17.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "LighterFilter.hpp"


void LighterFilter::Init()
{
    programObject = gl_esLoadProgram(vShader, fShader);
    
    zoomProgram = gl_esLoadProgram(zoomVShader, zoomFShader);
}



void LighterFilter::setTexture(unsigned char *buffer, int width, int height, GLenum format)
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


void LighterFilter::renderZoom(double duration)
{
    static double time = 0;
    
    time += duration;
    
    if (time > 2000.0) {
        time = 0;
    }
    
    float scale = 0.0;
    if (time > 0 && time < 800) {
        scale = (1.0 - time / 800.0) * 0.1;
    }
    
    GLfloat vVertices[] = {
        -1.0f,  1.0f, 0.0f,  // Position 0
        scale,  scale,        // TexCoord 0
        -1.0f, -1.0f, 0.0f,  // Position 1
        scale,  1.0f - scale,        // TexCoord 1
        1.0f, -1.0f, 0.0f,  // Position 2
        1.0f - scale,  1.0f - scale,        // TexCoord 2
        1.0f,  1.0f, 0.0f,  // Position 3
        1.0f - scale,  scale,         // TexCoord 3
    };
    
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glUseProgram(zoomProgram);
    
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    updateZoom(time);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void LighterFilter::render(double duration)
{
    static double time = 0;
    
    time += duration;
    
    if (time > 4000.0) {
        time = 0;
    }
    
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
    
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glUseProgram(programObject);
    
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    updateLight(time);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}


void LighterFilter::updateLight(double time)
{
    static float strength = 0;
    
    if (time > 0 && time < 2000) {
        strength = time / 2000.0 * 1.0;
    }else if (time > 2000 && time < 4000) {
        strength = (4000.0 - time) / 2000.0 * 1.0;
    }
    
    glUniform1f(glGetUniformLocation(programObject, "strength"), strength);
}


void LighterFilter::updateZoom(double time)
{
    
    float blurSize = 0.0;
    if (time > 0 && time < 800) {
        blurSize = (1.0 - time / 800.0) * 5;
    }
    
    glUniform2f(glGetUniformLocation(zoomProgram, "blurCenter"), 0.5, 0.5);
    glUniform1f(glGetUniformLocation(zoomProgram, "blurSize"), blurSize);
}


LighterFilter::~LighterFilter()
{
    glDeleteTextures(1, &textureId);
    destoryRenderAndFrameBuffer();
    glDeleteProgram(programObject);
    glDeleteProgram(zoomProgram);
}

