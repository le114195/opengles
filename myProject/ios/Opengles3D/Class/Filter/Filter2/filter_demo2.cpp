//
//  filter_demo2.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "filter_demo2.hpp"


int FILTER_DEMO2::Init ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    
    char vShader[] =
    "attribute vec4 a_position;   \n"
    "attribute vec2 a_texCoord;   \n"
    "varying vec2 v_texCoord;                       \n"
    "void main()                                \n"
    "{                                          \n"
    "   gl_Position = a_position;               \n"
    "   v_texCoord = a_texCoord;                \n"
    "}                                          \n";
    
    char fShader[] =
    "precision mediump float;                               \n"
    "varying vec2 v_texCoord;                               \n"
    "uniform sampler2D s_baseMap;                           \n"
    "uniform float alpha;                                   \n"
    "uniform float offset;                                  \n"
    "uniform float fstep;                                   \n"
    "void main()                                            \n"
    "{                                                      \n"
    
    "  vec2 out_texCoord = vec2(v_texCoord.x + offset, v_texCoord.y);     \n"
    
    "  vec4 sample0,sample1,sample2,sample3;           \n"
    "  sample0=texture2D(s_baseMap,vec2(out_texCoord.x-fstep,out_texCoord.y-fstep)); \n"
    "  sample1=texture2D(s_baseMap,vec2(out_texCoord.x+fstep,out_texCoord.y-fstep)); \n"
    "  sample2=texture2D(s_baseMap,vec2(out_texCoord.x+fstep,out_texCoord.y+fstep)); \n"
    "  sample3=texture2D(s_baseMap,vec2(out_texCoord.x-fstep,out_texCoord.y+fstep)); \n"
    "  vec4 color=(sample0+sample1+sample2+sample3) / 4.0; \n"
    
    "  gl_FragColor = vec4(color.b, color.g, color.r, alpha);           \n"
    "}                                                                  \n";
    
    
    userData->programObject = xl_esLoadProgram(vShader, fShader);
    
    userData->baseMapLoc = glGetUniformLocation(userData->programObject, "s_baseMap");
    
    userData->tex1Id = LoadTexture(userData->platformData, userData->buffer1, userData->buffer1_width, userData->buffer1_height);
    
    userData->alphaLoc = glGetUniformLocation(userData->programObject, "alpha");
    
    userData->offsetLoc = glGetUniformLocation(userData->programObject, "offset");
    
    userData->fstepLoc = glGetUniformLocation(userData->programObject, "fstep");
    
    userData->alpha = 0.3;
    userData->offset = 0.1;
    userData->fstep = 0.0015;
    
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    
    return TRUE;
}


void FILTER_DEMO2::Draw ( ESContext *esContext ) {
    
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
    GLushort indices[] = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7 };
    
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
    
    glUniform1f(userData->baseMapLoc, 0);
    glUniform1f(userData->alphaLoc, 1.0);
    glUniform1f(userData->offsetLoc, 0.0);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, userData->tex1Id);
    
    glUniform1f(userData->alphaLoc, userData->alpha);
    glUniform1f(userData->offsetLoc, userData->offset);
    glUniform1f(userData->fstepLoc, userData->fstep);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, userData->tex1Id);
    glUniform1f(userData->alphaLoc, userData->alpha);
    glUniform1f(userData->offsetLoc, -userData->offset);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void FILTER_DEMO2::Update ( ESContext *esContext, float deltaTime ) {
    UserData *userData = (UserData *)esContext->userData;
    
    static float time = 0;
    time += deltaTime;
    if (time > 2.0) {
        time = 0;
    }
    
    
    glDeleteTextures(userData->programObject, &userData->tex1Id);
    
    static int status = 1;
    
    userData->offset += deltaTime * 0.2 * status;
    
    
    if (userData->offset > 0.2) {
        status = -1;
    }else if (userData->offset <= 0) {
        status = 1;
    }
    
    
    userData->tex1Id = LoadTexture(userData->platformData, userData->buffer1, userData->buffer1_width, userData->buffer1_height);
}

///
// Cleanup
//
void FILTER_DEMO2::ShutDown ( ESContext *esContext )
{
    UserData *userData = (UserData *)esContext->userData;
    
    // Delete texture object
    glDeleteTextures ( 1, &userData->tex1Id );
    
    // Delete program object
    glDeleteProgram ( userData->programObject );
}

int FILTER_DEMO2::esMain(ESContext *esContext) {
    if ( !Init ( esContext ) )
    {
        return GL_FALSE;
    }
    
    esRegisterDrawFunc ( esContext, Draw );
    esRegisterShutdownFunc ( esContext, ShutDown );
    esRegisterUpdateFunc(esContext, Update);
    
    return GL_TRUE;
    
}

