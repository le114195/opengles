//
//  3d_demo1.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "3d_demo1.hpp"



GLuint DEMO1::LoadTexture2(void *ioContext, char *buffer, int width, int height) {
    
    GLuint texId;
    
    glGenTextures ( 1, &texId );
    glBindTexture ( GL_TEXTURE_2D, texId );
    
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    
    return texId;
}


int DEMO1::Init ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
        char *vShader;
        char *fShader;
    
        xl_readFileStr(&vShader, "3d_demo1_shader.vs");
        xl_readFileStr(&fShader, "3d_demo1_shader.frag");
    
    userData->programObject = xl_esLoadProgram(vShader, fShader);
    
    userData->baseMapLoc = glGetUniformLocation(userData->programObject, "s_baseMap");
    userData->lightMapLoc = glGetUniformLocation(userData->programObject, "s_lightMap");
    
    userData->baseMapTexId = LoadTexture2(userData->platformData, (char *)userData->buffer1, userData->buffer1_width, userData->buffer1_height);
    
    userData->img2TexId = LoadTexture2(userData->platformData, userData->buffer2, userData->buffer2_width, userData->buffer2_height);
    
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    
    return TRUE;
}


void DEMO1::Draw ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    GLfloat rate = 1.0 * esContext->width / esContext->height;
    
    GLfloat vVertices[] = {
        -1.0f,  1.0f, 0.0f,  // Position 0
        0.0f,  0.0f,        // TexCoord 0
        -1.0f, -1.0f, 0.0f,  // Position 1
        0.0f,  1.0f,        // TexCoord 1
        1.0f, -1.0f, 0.0f,  // Position 2
        1.0f,  1.0f,        // TexCoord 2
        1.0f,  1.0f, 0.0f,  // Position 3
        1.0f,  0.0f,         // TexCoord 3
        
        -0.5f,  0.5f * rate, 0.0f,  // Position 0
        0.0f,  0.0f,        // TexCoord 0
        -0.5f, -0.5f * rate, 0.0f,  // Position 1
        0.0f,  1.0f,        // TexCoord 1
        0.5f, -0.5f * rate, 0.0f,  // Position 2
        1.0f,  1.0f,        // TexCoord 2
        0.5f,  0.5f * rate, 0.0f,  // Position 3
        1.0f,  0.0f         // TexCoord 3
    };
    GLushort indices[] = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7 };
    
    glViewport(0, 0, esContext->width, esContext->height);
    
    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glUseProgram(userData->programObject);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, userData->baseMapTexId);
    
    glUniform1f(userData->baseMapLoc, 0);
    
    glUniform1f(glGetUniformLocation(userData->programObject, "alpha_t"), 1.0);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, userData->img2TexId);
    
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glUniform1f(glGetUniformLocation(userData->programObject, "alpha_t"), 0.5);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices + 6);
}


///
// Cleanup
//
void DEMO1::ShutDown ( ESContext *esContext )
{
    UserData *userData = (UserData *)esContext->userData;
    
    // Delete texture object
    glDeleteTextures ( 1, &userData->baseMapTexId );
    glDeleteTextures ( 1, &userData->lightMapTexId );
    
    // Delete program object
    glDeleteProgram ( userData->programObject );
}

int DEMO1::esMain(ESContext *esContext) {
    if ( !Init ( esContext ) )
    {
        return GL_FALSE;
    }
    
    esRegisterDrawFunc ( esContext, Draw );
    esRegisterShutdownFunc ( esContext, ShutDown );
    
    return GL_TRUE;

}






