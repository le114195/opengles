//
//  3d_demo2.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "3d_demo2.hpp"
#include <stdlib.h>
#include <string.h>

int DEMO2::Init(ESContext *esContext)
{
    UserData *userData = (UserData *)esContext->userData;
    
    const char vShaderStr[] =
    "#version 300 es                             \n"
    "uniform mat4 u_mvpMatrix;                   \n"
    "layout(location = 0) in vec4 a_position;    \n"
    "layout(location = 1) in vec4 a_color;       \n"
    "out vec4 v_color;                           \n"
    "void main()                                 \n"
    "{                                           \n"
    "   v_color = a_color;                       \n"
    "   gl_Position = u_mvpMatrix * a_position;  \n"
    "}                                           \n";
    
    const char fShaderStr[] =
    "#version 300 es                                \n"
    "precision mediump float;                       \n"
    "in vec4 v_color;                               \n"
    "layout(location = 0) out vec4 outColor;        \n"
    "void main()                                    \n"
    "{                                              \n"
    "  outColor = v_color;                          \n"
    "}                                              \n";

    userData->programObject = xl_esLoadProgram(vShaderStr, fShaderStr);
    
    userData->mvpLoc = glGetUniformLocation(userData->programObject, "u_mvpMatrix");
    
    userData->angle = 10.0f;
    
    // Generate the vertex data
//    userData->numIndices = esGenCube ( 1.0, &userData->vertices, NULL, NULL, &userData->indices );
    
    userData->numIndices = esGenBuffer(&userData->vertices, &userData->indices);
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    return TRUE;
}


void DEMO2::Draw(ESContext *esContext)
{
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
    
    // Set the vertex color to red
    glVertexAttrib4f ( 1, 1.0f, 0.0f, 0.0f, 1.0f );
    
    // Load the MVP matrix
    glUniformMatrix4fv ( userData->mvpLoc, 1, GL_FALSE, ( GLfloat * ) &userData->mvpMatrix.m[0][0] );
    
    // Draw the cube
    glDrawElements ( GL_TRIANGLES, userData->numIndices, GL_UNSIGNED_INT, userData->indices );
}


void DEMO2::Update ( ESContext *esContext, float deltaTime )
{
    DEMO2::UserData *userData = (DEMO2::UserData *)esContext->userData;
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


void DEMO2::ShutDown(ESContext *esContext)
{
    UserData *userData = (UserData *)esContext->userData;
    
    // Delete program object
    glDeleteProgram ( userData->programObject );
    
}


int DEMO2::esMain(ESContext *esContext) {
    if ( !Init ( esContext ) )
    {
        return GL_FALSE;
    }
    
    esRegisterUpdateFunc(esContext, Update);
    esRegisterShutdownFunc ( esContext, ShutDown );
    esRegisterDrawFunc ( esContext, Draw );
    
    return GL_TRUE;
}



int DEMO2::esGenBuffer (GLfloat **vertices, GLuint **indices) {
    
    int numVertices = 5;
    int numIndices = 18;
    
    GLfloat cubeVerts[] = {
        -0.5f,  0.5f,   0.0f,
        0.5f,   0.5f,   0.0f,
        0.5f,   -0.5f,  0.0f,
        -0.5f,  -0.5f,  0.0f,
        0.0f,   0.0f,   1.0f
    };
    
    if (vertices != NULL) {
        *vertices = (GLfloat *)malloc(sizeof(GLfloat) * 3 * numVertices);
        memcpy(*vertices, cubeVerts, sizeof(cubeVerts));
    }
    
    GLuint cubIndexs[] = {
        0, 1, 2,
        2, 3, 0,
        4, 0, 1,
        4, 1, 2,
        4, 2, 3,
        4, 3, 0
    };
    if (indices != NULL) {
        *indices = (GLuint *)malloc(sizeof(GLuint) * numIndices);
        memcpy(*indices, cubIndexs, sizeof(cubIndexs));
    }
    
    return numIndices;
}



