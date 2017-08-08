//
//  dynamic_shader.h
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/8.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef dynamic_shader_h
#define dynamic_shader_h

#include <stdio.h>
#include <string>

void gaussianVertexShaderStr(std::string &vertexStr, float sigma);

void gaussianFragmentShaderStr(std::string &fragmentStr, float sigma);

#endif /* dynamic_shader_h */
