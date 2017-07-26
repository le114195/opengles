//
//  3d_demo5.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/17.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "3d_demo5.hpp"
#include "demo_data.h"


/** 数据类型1 */
int demo5_data1(GLfloat **vertices, GLuint **indices, GLfloat **colors);

int DEMO5::Init(ESContext *esContext) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    const char vShaderStr[] =
    "#version 300 es                             \n"
    "uniform mat4 u_mvpMatrix;                   \n"
    "layout(location = 0) in vec4 a_position;    \n"
    "layout(location = 1) in vec2 a_color;       \n"
    "out vec2 v_texCoord;                           \n"
    "void main()                                 \n"
    "{                                           \n"
    "   v_texCoord = a_color;                       \n"
    "   gl_Position = u_mvpMatrix * a_position;  \n"
    "}                                           \n";
    
    const char fShaderStr[] =
    "#version 300 es                                     \n"
    "precision mediump float;                            \n"
    "in vec2 v_texCoord;                                 \n"
    "layout(location = 0) out vec4 outColor;             \n"
    "uniform sampler2D s_baseMap;                        \n"
    "void main()                                         \n"
    "{                                                   \n"
    "  vec4 xx = texture( s_baseMap, v_texCoord );      \n"
    "  outColor = vec4(xx.r, xx.g, xx.b, 1.0);         \n"
    "}                                                   \n";
    

    //加载着色器
    userData->programObject = xl_esLoadProgram(vShaderStr, fShaderStr);
    
    //参数
    userData->mvpLoc = glGetUniformLocation(userData->programObject, "u_mvpMatrix");
    
    //纹理加载
    userData->texId = LoadTexture(userData->platData, userData->buffer, userData->buffer_width, userData->buffer_height);
    
    userData->numIndices = demo5_data1(&userData->vertices, &userData->indices, &userData->colors);
    
    return TRUE;
}


void DEMO5::Update(ESContext *esContext, float deltaTime) {
    
    UserData *userData = (UserData *)esContext->userData;
    ESMatrix perspective;
    ESMatrix modelview;
    float    aspect;
    
    // Compute a rotation angle based on time to rotate the cube
    userData->angle += ( deltaTime * 40.0f );
    
    if ( userData->angle >= 360.0f )
    {
        userData->angle -= 360.0f;
    }
    
    // Compute the window aspect ratio
    aspect = ( GLfloat ) esContext->width / ( GLfloat ) esContext->height;
    
    // Generate a perspective matrix with a 60 degree FOV
    esMatrixLoadIdentity ( &perspective );
    esPerspective ( &perspective, 90.0f, aspect, 1.0f, 20.0f );
    
    // Generate a model view matrix to rotate/translate the cube
    esMatrixLoadIdentity ( &modelview );
    
    // Translate away from the viewer
    esTranslate ( &modelview, 0.0, 0.0, -2.0 );
    
    // Rotate the cube
    esRotate ( &modelview, userData->angle, 1.0, 0.0, 1.0 );
    
    // Compute the final MVP by multiplying the
    // modevleiw and perspective matrices together
    esMatrixMultiply ( &userData->mvpMatrix, &modelview, &perspective );
}


void DEMO5::Draw(ESContext *esContext) {

    UserData *userData = (UserData *)esContext->userData;
    
    // Set the viewport
    glViewport ( 0, 0, esContext->width, esContext->height );
    
    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    // Use the program object
    glUseProgram ( userData->programObject );
    
    // Load the vertex position
    glVertexAttribPointer ( 0, 3, GL_FLOAT,
                           GL_FALSE, 3 * sizeof ( GLfloat ), userData->vertices );
    glEnableVertexAttribArray ( 0 );
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), userData->colors);
    glEnableVertexAttribArray ( 1 );
    
//    // Set the vertex color to red
//    glVertexAttrib4f ( 1, 1.0f, 0.0f, 0.0f, 1.0f );
    
    // Load the MVP matrix
    glUniformMatrix4fv ( userData->mvpLoc, 1, GL_FALSE, ( GLfloat * ) &userData->mvpMatrix.m[0][0] );
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, userData->texId);
    
    //启动混合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    //启动深度测试
    glEnable(GL_DEPTH_TEST);
    
    // Draw the cube
    glDrawElements ( GL_TRIANGLES, userData->numIndices, GL_UNSIGNED_INT, userData->indices );
}

void DEMO5::ShutDown(ESContext *esContext) {
    
    UserData *userData = (UserData *)esContext->userData;
    
    glDeleteTextures(1, &userData->texId);
    glDeleteProgram(userData->programObject);
}

int DEMO5::esMain(ESContext *esContext) {
    
    if (!Init(esContext)) {
        return FALSE;
    }
    
    esRegisterUpdateFunc(esContext, Update);
    
    esRegisterDrawFunc(esContext, Draw);
    
    esRegisterShutdownFunc(esContext, ShutDown);
    
    return TRUE;
}

/** 数据类型1 */
int demo5_data1(GLfloat **vertices, GLuint **indices, GLfloat **colors) {
    
    int numVertices = 24;
    int numIndices = 36;
    
    GLfloat cubeVerts[] =
    {
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
    };

    if (vertices != NULL) {
        *vertices = (GLfloat *)malloc(sizeof(GLfloat) * 3 * numVertices);
        memcpy(*vertices, cubeVerts, sizeof(cubeVerts));
    }

    GLfloat cubeTex[] =
    {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };
    if (colors != NULL) {
        *colors = (GLfloat *)malloc(sizeof(GLfloat) * 3 * numVertices);
        memcpy(*colors, cubeTex, sizeof(cubeTex));
    }
    
    GLuint cubeIndices[] =
    {
        0, 2, 1,
        0, 3, 2,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 15, 14,
        12, 14, 13,
        16, 17, 18,
        16, 18, 19,
        20, 23, 22,
        20, 22, 21
    };
    if (indices != NULL) {
        *indices = (GLuint *)malloc(sizeof(GLuint) * numIndices);
        memcpy(*indices, cubeIndices, sizeof(cubeIndices));
    }
    return numIndices;
}





