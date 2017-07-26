//
//  demo4_data.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/14.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "demo4_data.hpp"


/** 数据类型1 */
int demo4_data1(GLfloat **vertices, GLuint **indices) {
    
    int numVertices = 40;
    int numIndices = 20 * 2 + 20 * 2 + 20 * 2;
    
    GLfloat cubeVerts[numVertices * 3];
    
    int i = 0;
    for (i = 0; i < numVertices; i++) {
        float angle = 1.0 * (360 / (numVertices / 2)) * i / 180 * 3.14;
        
        if (i < numVertices / 2) {
            cubeVerts[i * 3] = cos(angle) * 0.5;
            cubeVerts[i * 3 + 1] = sin(angle) * 0.5;
            cubeVerts[i * 3 + 2] = -0.5f;
        }else {
            cubeVerts[i * 3] = cos(angle) * 0.5;
            cubeVerts[i * 3 + 1] = sin(angle) * 0.5;
            cubeVerts[i * 3 + 2] = 0.5f;
        }
    }
    if (vertices != NULL) {
        *vertices = (GLfloat *)malloc(sizeof(GLfloat) * 3 * numVertices);
        memcpy(*vertices, cubeVerts, sizeof(cubeVerts));
    }
    GLuint cubIndexs[numIndices];
    for (int j = 0; j < 20; j++) {
        cubIndexs[j * 2 + 0] = j;
        cubIndexs[j * 2 + 1] = j + 20;
    }
    for (int j = 0; j < 20; j++) {
        if (j < 19) {
            cubIndexs[40 + j * 2] = j;
            cubIndexs[40 + j * 2 + 1] = j + 1;
        }else {
            cubIndexs[40 + j * 2] = j;
            cubIndexs[40 + j * 2 + 1] = 0;
        }
    }
    for (int j = 0; j < 20; j++) {
        if (j < 19) {
            cubIndexs[80 + j * 2] = j + 20;
            cubIndexs[80 + j * 2 + 1] = j + 1 + 20;
        }else {
            cubIndexs[80 + j * 2] = j + 20;
            cubIndexs[80 + j * 2 + 1] = 20;
        }
    }
    if (indices != NULL) {
        *indices = (GLuint *)malloc(sizeof(GLuint) * numIndices);
        memcpy(*indices, cubIndexs, sizeof(cubIndexs));
    }
    return numIndices;
}

/** 数据类型2 */
int demo4_data2(GLfloat **vertices, GLuint **indices)
{
    return 0;
}

