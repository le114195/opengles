//
//  multiple_sample.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/27.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef multiple_sample_hpp
#define multiple_sample_hpp

#include "new_opengles_base.hpp"

class MULTIPLE_SAMPLE:public NEW_OPENGLES_BASE
{
public:
    
    void Init();
    
    void render();
    
    void setupFrameBuffer2();
    
public:
    
    GLuint textureId1;
    GLuint textureId2;
    GLuint textureId3;
    
    GLuint program2;
    GLuint program3;
    
    const char* fShader2;
    const char *fShader3;
    
    GLuint framebuffer1;
    GLuint framebuffer2;
    
};


#endif /* multiple_sample_hpp */
