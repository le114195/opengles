//
//  filter_scale.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "filter_scale.hpp"

int FILTER_SCALE::Init ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    //    char *vShader;
    //    char *fShader;
    //
    //    xl_readFileStr(&vShader, "shader.vs");
    //    xl_readFileStr(&fShader, "shader.frag");
    
    
    char vShader[] =
    "#version 300 es                            \n"
    "uniform mat4 u_mvpMatrix;                   \n"
    "uniform mat4 u_vMvpMatrix;                   \n"
    "layout(location = 0) in vec4 a_position;   \n"
    "layout(location = 1) in vec4 a_texCoord;   \n"
    "out vec2 v_texCoord;                       \n"
    "void main()                                \n"
    "{                                          \n"
    "   gl_Position = u_vMvpMatrix * a_position;               \n"
    "   vec4 xx = u_mvpMatrix * a_texCoord;    \n"
    "   v_texCoord = vec2(xx.r, xx.g);                \n"
    "}                                          \n";
    
    char fShader[] =
    "#version 300 es                                     \n"
    "precision mediump float;                            \n"
    "in vec2 v_texCoord;                                 \n"
    "layout(location = 0) out vec4 outColor;             \n"
    "uniform sampler2D s_baseMap;                        \n"
    "uniform float alpha;                                \n"
    "void main()                                         \n"
    "{                                                   \n"
    "  vec4 xx = texture( s_baseMap, v_texCoord );       \n"
    "  outColor = vec4(xx.r, xx.g, xx.b, alpha);           \n"
    "}                                                   \n";
    
    userData->programObject = xl_esLoadProgram(vShader, fShader);
    
    userData->tex1Id = LoadTexture(userData->platformData, userData->buffer1, userData->buffer1_width, userData->buffer1_height);
    
    userData->mvpLoc = glGetUniformLocation(userData->programObject, "u_mvpMatrix");
    
    userData->vMvpLoc = glGetUniformLocation(userData->programObject, "u_vMvpMatrix");
    
    userData->baseMapLoc = glGetUniformLocation(userData->programObject, "s_baseMap");
    
    userData->alphaLoc = glGetUniformLocation(userData->programObject, "alpha");
    
    userData->offset = 0;
    userData->scaleStatus = 0;
    
    userData->angle = 90;
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    return TRUE;
}



void FILTER_SCALE::Draw ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    GLfloat vVertices[] = {
        -0.5f,  0.5f, 0.0f,  // Position 0
        0.0f,  0.0f,        // TexCoord 0
        -0.5f, -0.5f, 0.0f,  // Position 1
        0.0f,  1.0f,        // TexCoord 1
        0.5f, -0.5f, 0.0f,  // Position 2
        1.0f,  1.0f,        // TexCoord 2
        0.5f,  0.5f, 0.0f,  // Position 3
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
    
    glUniform1f(userData->baseMapLoc, 0);
    glUniform1f(userData->alphaLoc, 1.0);
    
    // Load the MVP matrix
    glUniformMatrix4fv ( userData->mvpLoc, 1, GL_FALSE, ( GLfloat * ) &userData->mvpMatrix.m[0][0] );
    glUniformMatrix4fv ( userData->vMvpLoc, 1, GL_FALSE, ( GLfloat * ) &userData->vMvpMatrix.m[0][0] );
    
    //启动深度测试
//    glEnable(GL_DEPTH_TEST);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}


void FILTER_SCALE::Update ( ESContext *esContext, float deltaTime ) {
    UserData *userData = (UserData *)esContext->userData;
    
    static int status = 1;
    
    glDeleteTextures(userData->programObject, &userData->tex1Id);
    
    userData->offset += status * deltaTime * 0.3;
    if (userData->offset > 0.3) {
        status = -1;
    }else if (userData->offset < 0) {
        status = 1;
    }
    
    ESMatrix modelview;
    // Generate a model view matrix to rotate/translate the cube
    esMatrixLoadIdentity ( &modelview );
    
    // Translate away from the viewer
    esTranslate ( &modelview, userData->offset, userData->offset, 0.0 );
    
    // Rotate the cube
    esRotate ( &modelview,0, 0.0, 0.0, 1.0 );
    
    //缩放
    esScale(&modelview, 1.0 - 2 * userData->offset, 1.0 - 2 * userData->offset, 1.0);
    userData->mvpMatrix = modelview;
    
    userData->angle += 1.0;
    if (userData->angle > 360) {
        userData->angle = -360;
    }
    
    
    
    ESMatrix vModelview;
    ESMatrix perspective;
    float    aspect;
    
    aspect = ( GLfloat ) esContext->width / ( GLfloat ) esContext->height;
    
    // Generate a perspective matrix with a 60 degree FOV
    esMatrixLoadIdentity ( &perspective );
    esPerspective ( &perspective, 30.0f, aspect, 5.0f, 20.0f );
    
    // Generate a model view matrix to rotate/translate the cube
    esMatrixLoadIdentity ( &vModelview );
    
    // Translate away from the viewer
    esTranslate ( &vModelview, 0.0, 0.0, 0.0 );
    
    // Rotate the cube
    esRotate ( &vModelview, userData->angle, 0.0, 0.0, 1.0 );
    
    //缩放
    esScale(&vModelview, 1.0, 1.0, 1.0);
    esMatrixMultiply ( &userData->vMvpMatrix, &vModelview, &perspective );
    
    userData->tex1Id = LoadTexture(userData->platformData, userData->buffer1, userData->buffer1_width, userData->buffer1_height);
}



///
// Cleanup
//
void FILTER_SCALE::ShutDown ( ESContext *esContext )
{
    UserData *userData = (UserData *)esContext->userData;
    
    // Delete texture object
    glDeleteTextures ( 1, &userData->tex1Id );
    
    // Delete program object
    glDeleteProgram ( userData->programObject );
}

int FILTER_SCALE::esMain(ESContext *esContext) {
    if ( !Init ( esContext ) )
    {
        return GL_FALSE;
    }
    
    esRegisterUpdateFunc(esContext, Update);
    esRegisterDrawFunc ( esContext, Draw );
    esRegisterShutdownFunc ( esContext, ShutDown );
    
    return GL_TRUE;
    
}

