//
//  one_input.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/3.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "one_input.hpp"
#include "dynamic_shader.hpp"



void OneInput_C::setupFrameBuffer2()
{
    textureId2 = createTexture2D(GL_RGBA, s_width, s_height, NULL);
    glGenFramebuffers(1, &framebuffer2);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer2);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId2, 0);
    
    textureId3 = createTexture2D(GL_RGBA, s_width, s_height, NULL);
    glGenFramebuffers(1, &framebuffer3);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer3);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId3, 0);
    
    textureId4 = createTexture2D(GL_RGBA, s_width, s_height, NULL);
    glGenFramebuffers(1, &framebuffer4);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer4);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId4, 0);
    
    textureId5 = createTexture2D(GL_RGBA, s_width, s_height, NULL);
    glGenFramebuffers(1, &framebuffer5);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer5);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId5, 0);
    
    
}

void OneInput_C::Init()
{
//    programObject = gl_esLoadProgram(vShader, fShader);//素描
    
//    programObject = gl_esLoadProgram(bvShader, bfShader);//双边模糊
    
    programObject = gl_esLoadProgram(tonsureVShader, tonsureFShader);//颜色梯度
    
    
    toonProgram = gl_esLoadProgram(toonVShader, toonFSahder);
    
    gProgram = gl_esLoadProgram(g_vShader, g_fShader);
}



void OneInput_C::setTexture(unsigned char *buffer, int width, int height, GLenum format)
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

void OneInput_C::render()
{
//    static GLfloat vVertices[] = {
//        -1.0f,  1.0f, 0.0f,  // Position 0
//        0.0f,  0.0f,        // TexCoord 0
//        -1.0f, -1.0f, 0.0f,  // Position 1
//        0.0f,  1.0f,        // TexCoord 1
//        1.0f, -1.0f, 0.0f,  // Position 2
//        1.0f,  1.0f,        // TexCoord 2
//        1.0f,  1.0f, 0.0f,  // Position 3
//        1.0f,  0.0f,         // TexCoord 3
//    };
    
    static GLfloat vVertices[] = {
        -1.0f,  1.0f, 0.0f,  // Position 0
        0.0f,  1.0f,        // TexCoord 0
        -1.0f, -1.0f, 0.0f,  // Position 1
        0.0f,  0.0f,        // TexCoord 1
        1.0f, -1.0f, 0.0f,  // Position 2
        1.0f,  0.0f,        // TexCoord 2
        1.0f,  1.0f, 0.0f,  // Position 3
        1.0f,  1.0f,         // TexCoord 3
    };
    
    
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer2);
    glUseProgram(programObject);
    
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
//    
//    GLint xx = glGetUniformLocation(toonProgram, "texelWidth");
//    GLint yy = glGetUniformLocation(toonProgram, "texelHeight");
//    
//    glUniform1f(xx, 1.0 / s_width);
//    glUniform1f(yy, 1.0 / s_height);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    glFlush();
    
    
    

}


void OneInput_C::renderToon()
{
//    static GLfloat vVertices[] = {
//        -1.0f,  1.0f, 0.0f,  // Position 0
//        0.0f,  0.0f,        // TexCoord 0
//        -1.0f, -1.0f, 0.0f,  // Position 1
//        0.0f,  1.0f,        // TexCoord 1
//        1.0f, -1.0f, 0.0f,  // Position 2
//        1.0f,  1.0f,        // TexCoord 2
//        1.0f,  1.0f, 0.0f,  // Position 3
//        1.0f,  0.0f,         // TexCoord 3
//    };
    
    static GLfloat vVertices[] = {//倒转
        -1.0f,  1.0f, 0.0f,  // Position 0
        0.0f,  1.0f,        // TexCoord 0
        -1.0f, -1.0f, 0.0f,  // Position 1
        0.0f,  0.0f,        // TexCoord 1
        1.0f, -1.0f, 0.0f,  // Position 2
        1.0f,  0.0f,        // TexCoord 2
        1.0f,  1.0f, 0.0f,  // Position 3
        1.0f,  1.0f,         // TexCoord 3
    };
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer2);
    glUseProgram(gProgram);
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    GLint gW = glGetUniformLocation(gProgram, "texelWidthOffset");
    GLint gh = glGetUniformLocation(gProgram, "texelHeightOffset");
    
    glUniform1f(gW, 1.0 / s_width);
    glUniform1f(gh, 0.0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    glFlush();
    
    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer3);
    glUseProgram(gProgram);
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    GLint gW1 = glGetUniformLocation(gProgram, "texelWidthOffset");
    GLint gh1 = glGetUniformLocation(gProgram, "texelHeightOffset");
    
    glUniform1f(gW1, 0.0);
    glUniform1f(gh1, 1.0 / s_height);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId2);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    glFlush();
    
    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer4);
    glUseProgram(toonProgram);
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    GLint tw = glGetUniformLocation(toonProgram, "texelWidth");
    GLint th = glGetUniformLocation(toonProgram, "texelHeight");
    
    glUniform1f(tw, 1.0 / s_width);
    glUniform1f(th, 1.0 / s_height);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    
    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer5);
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
    glBindTexture(GL_TEXTURE_2D, textureId4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    
}






