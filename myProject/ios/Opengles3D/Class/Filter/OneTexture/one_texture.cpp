//
//  one_texture.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/22.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "one_texture.hpp"

int FILTER_ONE_TEXTURE::Init ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    userData->programObject = xl_esLoadProgram(userData->vShader, userData->fShader);
    
    userData->textureId = LoadTexture(userData->platformData, (char *)userData->buffer, userData->buffer_width, userData->buffer_height);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    userData->colorMap[0] = 1.0;
    userData->colorMap[1] = 0.0;
    userData->colorMap[2] = 0.0;
    
    return TRUE;
}


void FILTER_ONE_TEXTURE::Draw ( ESContext *esContext ) {
    
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
    
    GLint mapColorLoc = glGetUniformLocation(userData->programObject, "colorMap");
    glUniform3fv(mapColorLoc, 1, &userData->colorMap[0]);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void FILTER_ONE_TEXTURE::Update ( ESContext *esContext, float deltaTime ) {
    
    
}


///
// Cleanup
//
void FILTER_ONE_TEXTURE::ShutDown ( ESContext *esContext )
{
    UserData *userData = (UserData *)esContext->userData;
    
    // Delete texture object
    glDeleteTextures ( 1, &userData->textureId );
    
    // Delete program object
    glDeleteProgram ( userData->programObject );
}

int FILTER_ONE_TEXTURE::esMain(ESContext *esContext) {
    if ( !Init ( esContext ) )
    {
        return GL_FALSE;
    }
    
    esRegisterDrawFunc ( esContext, Draw );
    esRegisterShutdownFunc ( esContext, ShutDown );
//    esRegisterUpdateFunc(esContext, Update);
    
    return GL_TRUE;
    
}

