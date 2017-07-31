//
//  filter_demo1.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "filter_demo1.hpp"


int FILTER_DEMO1::Init ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    userData->programObject = xl_esLoadProgram(userData->vShader, userData->fShader);
    
    userData->baseMapLoc = glGetUniformLocation(userData->programObject, "colorMap");
    
    userData->tex1Id = LoadTexture(userData->platformData, userData->buffer1, userData->buffer1_width, userData->buffer1_height);
    
    userData->alphaLoc = glGetUniformLocation(userData->programObject, "alpha");
    userData->scaleLoc = glGetUniformLocation(userData->programObject, "scale");
    
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    
    return TRUE;
}


void FILTER_DEMO1::Draw ( ESContext *esContext ) {
    
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
    GLushort indices[] = { 0, 1, 2, 0, 2, 3};
    
    glViewport(0, 0, esContext->width, esContext->height);
    
    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glUseProgram(userData->programObject);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, userData->tex1Id);
    
    glUniform1f(userData->alphaLoc, 0.3);
    glUniform1f(userData->scaleLoc, 1.3);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}


void FILTER_DEMO1::Update ( ESContext *esContext, float deltaTime ) {
    
}

///
// Cleanup
//
void FILTER_DEMO1::ShutDown ( ESContext *esContext )
{
    UserData *userData = (UserData *)esContext->userData;
    
    // Delete texture object
    glDeleteTextures ( 1, &userData->tex1Id );
    
    // Delete program object
    glDeleteProgram ( userData->programObject );
}

int FILTER_DEMO1::esMain(ESContext *esContext) {
    if ( !Init ( esContext ) )
    {
        return GL_FALSE;
    }
    
    esRegisterUpdateFunc(esContext, Update);
    esRegisterDrawFunc ( esContext, Draw );
    esRegisterShutdownFunc ( esContext, ShutDown );
    
    return GL_TRUE;
    
}


