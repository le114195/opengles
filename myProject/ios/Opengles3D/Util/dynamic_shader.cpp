//
//  dynamic_shader.c
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/8.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "dynamic_shader.hpp"
#include <math.h>
#include "GLUtil.h"
#include <stdlib.h>


void gaussianVertexShaderStr(std::string &vertexStr, float sigma)
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
            vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n", (unsigned long)(1 + (numberOfOptimizedOffsets * 2)));
    
    vertexStr.append(temp);
    memset(temp, 0, sizeof(temp));
    
    sprintf(temp, "blurCoordinates[0] = inputTextureCoordinate.xy;\n");
    vertexStr.append(temp);
    memset(temp, 0, sizeof(temp));
    
    for (int currentOptimizedOffset = 0; currentOptimizedOffset < numberOfOptimizedOffsets; currentOptimizedOffset++)
    {
        sprintf(temp, "\
                blurCoordinates[%lu] = inputTextureCoordinate.xy + singleStepOffset * %f;\n\
                blurCoordinates[%lu] = inputTextureCoordinate.xy - singleStepOffset * %f;\n", (unsigned long)((currentOptimizedOffset * 2) + 1), optimizedGaussianOffsets[currentOptimizedOffset], (unsigned long)((currentOptimizedOffset * 2) + 2), optimizedGaussianOffsets[currentOptimizedOffset]);
        vertexStr.append(temp);
        memset(temp, 0, sizeof(temp));
    }
    
    // Footer
    vertexStr.append("}\n");
    
    free(optimizedGaussianOffsets);
    free(standardGaussianWeights);
}


void gaussianFragmentShaderStr(std::string &fragmentStr, float sigma)
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
            lowp vec4 sum = vec4(0.0);\n", (unsigned long)(1 + (numberOfOptimizedOffsets * 2)));
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
        
        sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[%lu]) * %f;\n", (unsigned long)((currentBlurCoordinateIndex * 2) + 1), optimizedWeight);
        fragmentStr.append(temp);
        memset(temp, 0, sizeof(temp));
        
        sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[%lu]) * %f;\n", (unsigned long)((currentBlurCoordinateIndex * 2) + 2), optimizedWeight);
        fragmentStr.append(temp);
        memset(temp, 0, sizeof(temp));
    }
    
    
    if (trueNumberOfOptimizedOffsets > numberOfOptimizedOffsets)
    {
        sprintf(temp, "highp vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n");
        fragmentStr.append(temp);
        memset(temp, 0, sizeof(temp));
        
        for (int currentOverlowTextureRead = numberOfOptimizedOffsets; currentOverlowTextureRead < trueNumberOfOptimizedOffsets; currentOverlowTextureRead++)
        {
            float firstWeight = standardGaussianWeights[currentOverlowTextureRead * 2 + 1];
            float secondWeight = standardGaussianWeights[currentOverlowTextureRead * 2 + 2];
            
            float optimizedWeight = firstWeight + secondWeight;
            float optimizedOffset = (firstWeight * (currentOverlowTextureRead * 2 + 1) + secondWeight * (currentOverlowTextureRead * 2 + 2)) / optimizedWeight;
            
            sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[0] + singleStepOffset * %f) * %f;\n", optimizedOffset, optimizedWeight);
            fragmentStr.append(temp);
            memset(temp, 0, sizeof(temp));
            
            sprintf(temp, "sum += texture2D(inputImageTexture, blurCoordinates[0] - singleStepOffset * %f) * %f;\n", optimizedOffset, optimizedWeight);
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

