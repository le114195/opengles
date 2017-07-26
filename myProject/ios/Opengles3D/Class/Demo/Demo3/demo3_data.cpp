//
//  demo3_data.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/14.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "demo3_data.hpp"


int demo3_data1 (GLfloat **vertices, GLuint **indices) {
    
    int numVertices = 21;
    int numIndices = 20 * 2 + 20 * 2;
    
    //    GLfloat cubeVerts[] = {
    //        -0.5f,  0.5f,   0.0f,
    //        0.5f,   0.5f,   0.0f,
    //        0.5f,   -0.5f,  0.0f,
    //        -0.5f,  -0.5f,  0.0f,
    //        0.0f,   0.0f,   0.5f,
    //    };
    
    GLfloat cubeVerts[numVertices * 3];
    
    int i = 0;
    for (i = 0; i < numVertices - 1; i++) {
        float angle = 1.0 * (360 / (numVertices - 1)) * i / 180 * 3.14;
        cubeVerts[i * 3] = cos(angle) * 0.5;
        cubeVerts[i * 3 + 1] = sin(angle) * 0.5;
        cubeVerts[i * 3 + 2] = 0.0;
    }
    cubeVerts[i * 3] = 0.0;
    cubeVerts[i * 3 + 1] = 0.0;
    cubeVerts[i * 3 + 2] = 0.5;
    
    if (vertices != NULL) {
        *vertices = (GLfloat *)malloc(sizeof(GLfloat) * 3 * numVertices);
        memcpy(*vertices, cubeVerts, sizeof(cubeVerts));
    }
    
    //    GLuint cubIndexs[] = {
    //        4,  0,
    //        4,  1,
    //        4,  2,
    //        4,  3,
    //        0,  1,
    //        1,  2,
    //        2,  3,
    //        3,  0,
    //        0,  2,
    //        1,  3,
    //    };
    
    GLuint cubIndexs[numIndices];
    
    for (int j = 0; j < 20; j++) {
        cubIndexs[j * 2 + 0] = numVertices - 1;
        cubIndexs[j * 2 + 1] = j;
    }
    
    for (int j = 0; j < 20; j++) {
        cubIndexs[40 + j * 2 + 0] = j;
        
        if (j < 19) {
            cubIndexs[40 + j * 2 + 1] = j + 1;
        }else {
            cubIndexs[40 + j * 2 + 1] = 0;
        }
        
    }
    
    
    if (indices != NULL) {
        *indices = (GLuint *)malloc(sizeof(GLuint) * numIndices);
        memcpy(*indices, cubIndexs, sizeof(cubIndexs));
    }
    
    return numIndices;
}

