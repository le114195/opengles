//
//  double_sample.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef double_sample_hpp
#define double_sample_hpp

#include "new_opengles_base.hpp"

class DOUBLE_SAMPLE_DEMO:public NEW_OPENGLES_BASE
{
public:
    
    void Init();
    
    void render();
    
    void setupFrameBuffer2();
    
public:
    
    GLuint textureId1;
    GLuint textureId2;
    
    GLuint program2;
    const char* fShader2;
    
    GLuint framebuffer1;
    
};


#endif /* double_sample_hpp */
