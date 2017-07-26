//
//  xl_blend.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "xl_blend.hpp"

int BLEND_XL::Init ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    userData->programObject = xl_esLoadProgram(userData->vShaderStr, userData->fShaderStr);
    
    userData->tex1Loc = glGetUniformLocation(userData->programObject, "s_baseMap");
    
    userData->alphaLoc = glGetUniformLocation(userData->programObject, "alpha");
    
    userData->offsetLoc = glGetUniformLocation(userData->programObject, "offset");
    
    userData->fstepLoc = glGetUniformLocation(userData->programObject, "fstep");
    
    userData->tex1Id = LoadTexture(userData->platformData, (char *)userData->buffer1, userData->buffer1_width, userData->buffer1_height);
    
    userData->alpha = 0.2;
    userData->offset = 0;
    userData->fstep = 0.001;
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    return TRUE;
}


void BLEND_XL::Draw ( ESContext *esContext ) {
    
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
    glBindTexture(GL_TEXTURE_2D, userData->tex1Id);
    
    //参数
    glUniform1f(userData->alphaLoc, userData->alpha);
    glUniform1f(userData->offsetLoc, userData->offset);
    glUniform1f(userData->fstepLoc, userData->fstep);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void BLEND_XL::Update ( ESContext *esContext, float deltaTime ) {
    UserData *userData = (UserData *)esContext->userData;
    
    static float time = 0;
    time += deltaTime;
    if (time > 2.0) {
        time = 0;
    }
    
    static int status = 1;
    
    userData->offset += deltaTime * 0.2 * status;
    
    if (userData->offset > 0.2) {
        status = -1;
    }else if (userData->offset <= 0) {
        status = 1;
    }
}


///
// Cleanup
//
void BLEND_XL::ShutDown ( ESContext *esContext )
{
    UserData *userData = (UserData *)esContext->userData;
    
    // Delete texture object
    glDeleteTextures ( 1, &userData->tex1Id );
    glDeleteTextures ( 1, &userData->tex2Id );
    
    // Delete program object
    glDeleteProgram ( userData->programObject );
}

int BLEND_XL::esMain(ESContext *esContext) {
    if ( !Init ( esContext ) )
    {
        return GL_FALSE;
    }
    
    esRegisterDrawFunc ( esContext, Draw );
    esRegisterShutdownFunc ( esContext, ShutDown );
    esRegisterUpdateFunc(esContext, Update);
    
    return GL_TRUE;
    
}


