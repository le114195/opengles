//
//  filter_blur.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/24.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "filter_blur.hpp"
#include <string>
#include <math.h>
#include <iostream>

void vertexShaderStr(std::string &vertexStr, float sigma);
void fragmentShaderStr(std::string &fragmentStr, float sigma);

int FILTER_BLUR::Init ( ESContext *esContext ) {
    
    UserData *userData = (UserData *)esContext->userData;
    
//    std::string vShaderStr;
//    
//    vertexShaderStr(vShaderStr, 20);
//    
//    printf("%s\n", vShaderStr.c_str());
//    
//    std::string fShaderStr;
//    fragmentShaderStr(fShaderStr, 20);
//    
//    printf("%s\n", fShaderStr.c_str());
    
    
    userData->programObject = xl_esLoadProgram(userData->vShader, userData->fShader);
    
    userData->textureId = LoadTexture(userData->platformData, (char *)userData->buffer, userData->buffer_width, userData->buffer_height);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    userData->fstep = 0.009;
    
    
    int r = 22;
    int count = 8 * r + 1;
    userData->weightCount = count;
    userData->weight = (float *)malloc(sizeof(float) * (r + 1));
    
    
    for (int i = 0; i <= r; i++) {
        userData->weight[i] = 1.0 / sqrt(2 * M_PI) * exp(-i * i * 0.5 / (1.2 * 1.2));
        printf("%f\n", userData->weight[i]);
        
//        userData->weight[i] = (r - i) * (r - i) + 20;
    }
    
    float total = 0;
    for (int i = 0; i <= r; i++) {
        if (i == 0) {
            total += userData->weight[i];
        }else {
            total += userData->weight[i] * 8;
        }
    }
    
    for (int i = 0; i <= r; i++) {
        userData->weight[i] = userData->weight[i] / total;
    }
    
    
    userData->weightLoc = glGetUniformLocation(userData->programObject, "weight");
    
    return TRUE;
}

void FILTER_BLUR::draw_img(ESContext *esContext, void *buffer, int width, int height) {
    
//    UserData *userData = (UserData *)esContext->userData;
//    
//    GLfloat vVertices[] = {
//        -1.0f,  1.0f, 0.0f,  // Position 0
//        0.0f,  1.0f,        // TexCoord 0
//        -1.0f, -1.0f, 0.0f,  // Position 1
//        0.0f,  0.0f,        // TexCoord 1
//        1.0f, -1.0f, 0.0f,  // Position 2
//        1.0f,  0.0f,        // TexCoord 2
//        1.0f,  1.0f, 0.0f,  // Position 3
//        1.0f,  1.0f,         // TexCoord 3
//    };
//    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
//    
//    glViewport(0, 0, esContext->width, esContext->height);
//    
//    // Clear the color buffer
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glClear ( GL_COLOR_BUFFER_BIT );
//    
//    glUseProgram(userData->programObject);
//    
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
//    
//    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//    
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, userData->textureId);
//
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//    
//    
//    //参数
//    GLint wOffsetLoc = glGetUniformLocation(userData->programObject, "texelWidthOffset");
////    float texelWidthOffset = 1.0 / userData->buffer_width;
//    float texelWidthOffset = 0;
//    glUniform1f(wOffsetLoc, texelWidthOffset);
//    
//    GLint hOffsetLoc = glGetUniformLocation(userData->programObject, "texelHeightOffset");
//    float texelHeightOffset = 1.0 / userData->buffer_height;
////    float texelHeightOffset = 0;
//    glUniform1f(hOffsetLoc, texelHeightOffset);
//    
//    glUniform1fv(userData->weightLoc, userData->weightCount, &userData->weight[0]);
//    
//    //    //启动混合：透明通道
//    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    //    glEnable(GL_BLEND);
//    
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
//    
////    glBindFramebuffer(<#GLenum target#>, <#GLuint framebuffer#>)
//    
////    glFramebufferTexture2D(<#GLenum target#>, <#GLenum attachment#>, <#GLenum textarget#>, <#GLuint texture#>, <#GLint level#>)
    
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
}


void FILTER_BLUR::Draw ( ESContext *esContext ) {
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
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
//    glReadBuffer(GL_BACK);
    
    //参数
    GLint wOffsetLoc = glGetUniformLocation(userData->programObject, "texelWidthOffset");
    float texelWidthOffset = 1.0 / userData->buffer_width;
    glUniform1f(wOffsetLoc, texelWidthOffset);
    
    GLint hOffsetLoc = glGetUniformLocation(userData->programObject, "texelHeightOffset");
    float texelHeightOffset = 1.0 / userData->buffer_height;
    glUniform1f(hOffsetLoc, texelHeightOffset);
    
    glUniform1fv(userData->weightLoc, userData->weightCount, &userData->weight[0]);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}



///
// Cleanup
//
void FILTER_BLUR::ShutDown ( ESContext *esContext )
{
    UserData *userData = (UserData *)esContext->userData;
    
    // Delete texture object
    glDeleteTextures ( 1, &userData->textureId );
    
    // Delete program object
    glDeleteProgram ( userData->programObject );
}

int FILTER_BLUR::esMain(ESContext *esContext) {
    if ( !Init ( esContext ) )
    {
        return GL_FALSE;
    }
    
    esRegisterDrawFunc ( esContext, Draw );
    esRegisterShutdownFunc ( esContext, ShutDown );
    
    return GL_TRUE;
}

void vertexShaderStr(std::string &vertexStr, float sigma)
{
    if (sigma <= 1) {
        vertexStr.append("attribute vec4 a_position;\n"
                         "attribute vec2 a_texCoord;\n"
                         "varying vec2 v_texCoord;\n"
                         "void main()\n"
        "{\n"
            "gl_Position = a_position;\n"
            "v_texCoord = a_texCoord;\n"
                         "}\n");
        return;
    }
    
    float minimumWeightToFindEdgeOfSamplingArea = 1.0/256.0;
    int blurRadius = floor(sqrt(-2.0 * pow(sigma, 2.0) * log(minimumWeightToFindEdgeOfSamplingArea * sqrt(2.0 * M_PI * pow(sigma, 2.0))) ));
    
    // First, generate the normal Gaussian weights for a given sigma
    float *standardGaussianWeights = (float *)malloc(sizeof(float) * (blurRadius + 1));
    
    float sumOfWeights = 0.0;
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = (1.0 / sqrt(2.0 * M_PI * pow(sigma, 2.0))) * exp(-pow(currentGaussianWeightIndex, 2.0) / (2.0 * pow(sigma, 2.0)));
        
        if (currentGaussianWeightIndex == 0)
        {
            sumOfWeights += standardGaussianWeights[currentGaussianWeightIndex];
        }
        else
        {
            sumOfWeights += 2.0 * standardGaussianWeights[currentGaussianWeightIndex];
        }
    }
    
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = standardGaussianWeights[currentGaussianWeightIndex] / sumOfWeights;
    }
    
    // From these weights we calculate the offsets to read interpolated values from
    int numberOfOptimizedOffsets;
    if (blurRadius / 2 + (blurRadius % 2) < 7) {
        numberOfOptimizedOffsets = blurRadius / 2 + (blurRadius % 2);
    }else {
        numberOfOptimizedOffsets = 7;
    }
    
    float *optimizedGaussianOffsets = (float*)calloc(numberOfOptimizedOffsets, sizeof(GLfloat));
    
    for (int currentOptimizedOffset = 0; currentOptimizedOffset < numberOfOptimizedOffsets; currentOptimizedOffset++)
    {
        GLfloat firstWeight = standardGaussianWeights[currentOptimizedOffset*2 + 1];
        GLfloat secondWeight = standardGaussianWeights[currentOptimizedOffset*2 + 2];
        
        GLfloat optimizedWeight = firstWeight + secondWeight;
        
        optimizedGaussianOffsets[currentOptimizedOffset] = (firstWeight * (currentOptimizedOffset*2 + 1) + secondWeight * (currentOptimizedOffset*2 + 2)) / optimizedWeight;
    }
    
    char temp[1024];
    
    sprintf(temp, "\
            attribute vec4 a_position;\n\
            attribute vec4 inputTextureCoordinate;\n\
            \n\
            uniform float texelWidthOffset;\n\
            uniform float texelHeightOffset;\n\
            \n\
            varying vec2 blurCoordinates[%lu];\n\
            \n\
            void main()\n\
            {\n\
            gl_Position = a_position;\n\
            \n\
            vec2 singleStepOffsetX = vec2(texelWidthOffset, 0);\n\
            vec2 singleStepOffsetY = vec2(0, texelHeightOffset);\n", (unsigned long)(1 + (numberOfOptimizedOffsets * 4)));
    
    vertexStr.append(temp);
    memset(temp, 0, sizeof(temp));
    
    sprintf(temp, "blurCoordinates[0] = inputTextureCoordinate.xy;\n");
    vertexStr.append(temp);
    memset(temp, 0, sizeof(temp));

    for (int currentOptimizedOffset = 0; currentOptimizedOffset < numberOfOptimizedOffsets; currentOptimizedOffset++)
    {
        sprintf(temp, "\
                blurCoordinates[%lu] = inputTextureCoordinate.xy + singleStepOffsetX * %f;\n\
                blurCoordinates[%lu] = inputTextureCoordinate.xy - singleStepOffsetX * %f;\n\
                blurCoordinates[%lu] = inputTextureCoordinate.xy + singleStepOffsetY * %f;\n\
                blurCoordinates[%lu] = inputTextureCoordinate.xy - singleStepOffsetY * %f;\n", (unsigned long)((currentOptimizedOffset * 4) + 1), optimizedGaussianOffsets[currentOptimizedOffset], (unsigned long)((currentOptimizedOffset * 4) + 2), optimizedGaussianOffsets[currentOptimizedOffset], (unsigned long)((currentOptimizedOffset * 4) + 3), optimizedGaussianOffsets[currentOptimizedOffset], (unsigned long)((currentOptimizedOffset * 4) + 4), optimizedGaussianOffsets[currentOptimizedOffset]);
        vertexStr.append(temp);
        
        memset(temp, 0, sizeof(temp));
    }
    
    // Footer
    vertexStr.append("}\n");
    
    free(optimizedGaussianOffsets);
    free(standardGaussianWeights);
}


void fragmentShaderStr(std::string &fragmentStr, float sigma)
{
    if (sigma <= 1) {
        fragmentStr.append("precision mediump float;\n"
                           "varying vec2 v_texCoord;\n"
                           "uniform sampler2D s_baseMap;\n"
                           "void main()\n"
                           "{\n"
                           "gl_FragColor = texture2D(s_baseMap, v_texCoord);\n"
                           "}\n");
        return;
    }
    
    float minimumWeightToFindEdgeOfSamplingArea = 1.0/256.0;
    int blurRadius = floor(sqrt(-2.0 * pow(sigma, 2.0) * log(minimumWeightToFindEdgeOfSamplingArea * sqrt(2.0 * M_PI * pow(sigma, 2.0))) ));
    // First, generate the normal Gaussian weights for a given sigma
    float *standardGaussianWeights = (float *)calloc(blurRadius + 1, sizeof(float));
    GLfloat sumOfWeights = 0.0;
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = (1.0 / sqrt(2.0 * M_PI * pow(sigma, 2.0))) * exp(-pow(currentGaussianWeightIndex, 2.0) / (2.0 * pow(sigma, 2.0)));
        
        if (currentGaussianWeightIndex == 0)
        {
            sumOfWeights += standardGaussianWeights[currentGaussianWeightIndex];
        }
        else
        {
            sumOfWeights += 2.0 * standardGaussianWeights[currentGaussianWeightIndex];
        }
    }

    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = standardGaussianWeights[currentGaussianWeightIndex] / sumOfWeights;
    }
    
    // From these weights we calculate the offsets to read interpolated values from
    int numberOfOptimizedOffsets;
    if (blurRadius / 2 + (blurRadius % 2) < 7) {
        numberOfOptimizedOffsets = blurRadius / 2 + (blurRadius % 2);
    }else {
        numberOfOptimizedOffsets = 7;
    }
    int trueNumberOfOptimizedOffsets = blurRadius / 2 + (blurRadius % 2);
    
    
    char temp[1024];
    sprintf(temp, "\
            uniform sampler2D inputImageTexture;\n\
            uniform highp float texelWidthOffset;\n\
            uniform highp float texelHeightOffset;\n\
            \n\
            varying highp vec2 blurCoordinates[%lu];\n\
            \n\
            void main()\n\
            {\n\
            lowp vec4 sum = vec4(0.0);\n", (unsigned long)(1 + (numberOfOptimizedOffsets * 4)));
    fragmentStr.append(temp);
    memset(temp, 0, sizeof(temp));
    
    sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[0]) * %f;\n", standardGaussianWeights[0]);
    fragmentStr.append(temp);
    memset(temp, 0, sizeof(temp));
    
    for (int currentBlurCoordinateIndex = 0; currentBlurCoordinateIndex < numberOfOptimizedOffsets; currentBlurCoordinateIndex++)
    {
        float firstWeight = standardGaussianWeights[currentBlurCoordinateIndex * 2 + 1];
        float secondWeight = standardGaussianWeights[currentBlurCoordinateIndex * 2 + 2];
        float optimizedWeight = firstWeight + secondWeight;

        sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[%lu]) * %f;\n", (unsigned long)((currentBlurCoordinateIndex * 4) + 1), optimizedWeight * 0.5);
        fragmentStr.append(temp);
        memset(temp, 0, sizeof(temp));
        
        sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[%lu]) * %f;\n", (unsigned long)((currentBlurCoordinateIndex * 4) + 2), optimizedWeight * 0.5);
        fragmentStr.append(temp);
        memset(temp, 0, sizeof(temp));
        
        sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[%lu]) * %f;\n", (unsigned long)((currentBlurCoordinateIndex * 4) + 3), optimizedWeight * 0.5);
        fragmentStr.append(temp);
        memset(temp, 0, sizeof(temp));
        
        sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[%lu]) * %f;\n", (unsigned long)((currentBlurCoordinateIndex * 4) + 4), optimizedWeight * 0.5);
        fragmentStr.append(temp);
        memset(temp, 0, sizeof(temp));
    }
    
    
    if (trueNumberOfOptimizedOffsets > numberOfOptimizedOffsets)
    {
        sprintf(temp, "highp vec2 singleStepOffsetX = vec2(texelWidthOffset, 0);\n\
                highp vec2 singleStepOffsetY = vec2(0, texelHeightOffset);\n");
        fragmentStr.append(temp);
        memset(temp, 0, sizeof(temp));
        
        for (int currentOverlowTextureRead = numberOfOptimizedOffsets; currentOverlowTextureRead < trueNumberOfOptimizedOffsets; currentOverlowTextureRead++)
        {
            float firstWeight = standardGaussianWeights[currentOverlowTextureRead * 2 + 1];
            float secondWeight = standardGaussianWeights[currentOverlowTextureRead * 2 + 2];
            
            float optimizedWeight = firstWeight + secondWeight;
            float optimizedOffset = (firstWeight * (currentOverlowTextureRead * 2 + 1) + secondWeight * (currentOverlowTextureRead * 2 + 2)) / optimizedWeight;
            
            sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[0] + singleStepOffsetX * %f) * %f;\n", optimizedOffset, optimizedWeight * 0.5);
            fragmentStr.append(temp);
            memset(temp, 0, sizeof(temp));
            
            sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[0] - singleStepOffsetX * %f) * %f;\n", optimizedOffset, optimizedWeight * 0.5);
            fragmentStr.append(temp);
            memset(temp, 0, sizeof(temp));
            
            sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[0] + singleStepOffsetY * %f) * %f;\n", optimizedOffset, optimizedWeight * 0.5);
            fragmentStr.append(temp);
            memset(temp, 0, sizeof(temp));
            
            sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[0] - singleStepOffsetY * %f) * %f;\n", optimizedOffset, optimizedWeight * 0.5);
            fragmentStr.append(temp);
            memset(temp, 0, sizeof(temp));
        }
    }
    
    sprintf(temp, "\
            gl_FragColor = sum;\n\
            }\n");
    fragmentStr.append(temp);
    memset(temp, 0, sizeof(temp));
    
    free(standardGaussianWeights);
}




