//
//  color_shake.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/24.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "color_shake.hpp"

void textureScale(ESContext *esContext);


int COLOR_SHAKE::Init ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    userData->programObject = xl_esLoadProgram(userData->vShader, userData->fShader);
    
    userData->textureId = LoadTexture(userData->platformData, (char *)userData->buffer, userData->buffer_width, userData->buffer_height);
    
    userData->offsetLoc = glGetUniformLocation(userData->programObject, "offset");
    userData->texScaleLoc = glGetUniformLocation(userData->programObject, "texScale");
    
    
    userData->offset[0] = 0.02;
    userData->offset[1] = 0.02 * 0.6;
    
    userData->texScale = 1.0;
    
    textureScale(esContext);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    return TRUE;
}


void textureScale(ESContext *esContext)
{
    COLOR_SHAKE::UserData *userData = (COLOR_SHAKE::UserData *)esContext->userData;
    
    float offsetV;
    offsetV = 1.0 - 1.0 / userData->texScale;
    
    ESMatrix modelview;
    // Generate a model view matrix to rotate/translate the cube
    esMatrixLoadIdentity ( &modelview );
    
    // Translate away from the viewer
    esTranslate ( &modelview, offsetV, offsetV, 0.0 );
    
    // Rotate the cube
    esRotate ( &modelview,0, 0.0, 0.0, 1.0 );
    
    //缩放
    esScale(&modelview, 1.0 - 2 * offsetV, 1.0 - 2 * offsetV, 1.0);
    userData->mvpMatrix = modelview;
}


void COLOR_SHAKE::draw_img(ESContext *esContext, void *buffer) {
    
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
    glUniform2fv(userData->offsetLoc, 1, &userData->offset[0]);
    glUniform1f(userData->texScaleLoc, userData->texScale);
    
    GLint mLoc = glGetUniformLocation(userData->programObject, "u_mvpMatrix");
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, &userData->mvpMatrix.m[0][0]);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    
    glReadPixels(0, 0, esContext->width, esContext->height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
}

void COLOR_SHAKE::Draw ( ESContext *esContext ) {
    
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
    glUniform2fv(userData->offsetLoc, 1, &userData->offset[0]);
    glUniform1f(userData->texScaleLoc, userData->texScale);
    
    GLint mLoc = glGetUniformLocation(userData->programObject, "u_mvpMatrix");
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, &userData->mvpMatrix.m[0][0]);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void COLOR_SHAKE::Update ( ESContext *esContext, float deltaTime ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    userData->offset[0] += 0.02 * deltaTime * 2;
    userData->offset[1] = 0.6 * userData->offset[0];
    
    if (userData->offset[0] > 0.02) {
        userData->offset[0] = 0;
        userData->offset[1] = 0;
    }
    
    userData->texScale += 0.06 * deltaTime * 2;
    if (userData->texScale > 1.06) {
        userData->texScale = 1.0;
    }
    
    textureScale(esContext);
}

///
// Cleanup
//
void COLOR_SHAKE::ShutDown ( ESContext *esContext )
{
    UserData *userData = (UserData *)esContext->userData;
    
    // Delete texture object
    glDeleteTextures ( 1, &userData->textureId );
    
    // Delete program object
    glDeleteProgram ( userData->programObject );
}

int COLOR_SHAKE::esMain(ESContext *esContext) {
    if ( !Init ( esContext ) )
    {
        return GL_FALSE;
    }
    
    esRegisterDrawFunc ( esContext, Draw );
    esRegisterShutdownFunc ( esContext, ShutDown );
//    esRegisterUpdateFunc(esContext, Update);
    
    return GL_TRUE;
}
