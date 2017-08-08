//
//  sobel_edge.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/24.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "sobel_edge.hpp"


int SOBEL_EDGE::Init ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    userData->programObject = xl_esLoadProgram(userData->vShader, userData->fShader);
    
    userData->textureId = LoadTexture(userData->platformData, (char *)userData->buffer, userData->buffer_width, userData->buffer_height);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    return TRUE;
}


void SOBEL_EDGE::Draw ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    GLfloat vVertices[] = {
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
    
    glViewport(0, 0, esContext->width, esContext->height);
    
    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glUseProgram(userData->programObject);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, userData->textureId);
    
    //参数
    GLint wLoc = glGetUniformLocation(userData->programObject, "texelWidth");
    GLfloat texelWidth = 1.0 / userData->buffer_width;
    glUniform1f(wLoc, texelWidth);
    
    GLint hLoc = glGetUniformLocation(userData->programObject, "texelHeight");
    GLfloat texelHeight = 1.0 / userData->buffer_height;
    glUniform1f(hLoc, texelHeight);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void SOBEL_EDGE::Update ( ESContext *esContext, float deltaTime ) {
    
    
    
}


///
// Cleanup
//
void SOBEL_EDGE::ShutDown ( ESContext *esContext )
{
    UserData *userData = (UserData *)esContext->userData;
    
    // Delete texture object
    glDeleteTextures ( 1, &userData->textureId );
    
    // Delete program object
    glDeleteProgram ( userData->programObject );
}

int SOBEL_EDGE::esMain(ESContext *esContext) {
    if ( !Init ( esContext ) )
    {
        return GL_FALSE;
    }
    
    esRegisterDrawFunc ( esContext, Draw );
    esRegisterShutdownFunc ( esContext, ShutDown );
    //    esRegisterUpdateFunc(esContext, Update);
    
    return GL_TRUE;
    
}
