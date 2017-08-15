//
//  BlendRend.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/15.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "BlendRend.hpp"



void BlendRend::Init()
{
    programObject = gl_esLoadProgram(randNoseVShader, randNoseFShader);
}


void BlendRend::setTexture(unsigned char *buffer, int width, int height, GLenum format)
{
    if (textureId == 0 || textureWidth != width || textureHeight != height) {
        textureId = createTexture2D(format, width, height, buffer);
        textureWidth = width;
        textureHeight = height;
    }else {
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, buffer);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void BlendRend::render(double duration)
{
    static GLfloat vVertices[] = {
        -1.0f,  1.0f, 0.0f,  // Position 0
        0.0f,  0.0f,        // TexCoord 0
        0.0f,  0.0f,
        -1.0f, -1.0f, 0.0f,  // Position 1
        0.0f,  1.0f,        // TexCoord 1
        0.0f,  1.0f,
        1.0f, -1.0f, 0.0f,  // Position 2
        1.0f,  1.0f,        // TexCoord 2
        1.0f,  1.0f,
        1.0f,  1.0f, 0.0f,  // Position 3
        1.0f,  0.0f,         // TexCoord 3
        1.0f,  0.0f,
    };
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    
    glUseProgram(programObject);
    
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), &vVertices[3]);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), &vVertices[5]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(glGetUniformLocation(programObject, "inputImageTexture"), 0);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, blendTextureId);
    glUniform1i(glGetUniformLocation(programObject, "inputImageTexture2"), 1);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}



