//
//  gaussian_blur.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef gaussian_blur_hpp
#define gaussian_blur_hpp

#include "new_opengles_base.hpp"

class GAUSSIAN_BLUR_DEMO:public NEW_OPENGLES_BASE
{
    
public:
    
    void Init();
    
    void render();
    
    void setupFrameBuffer2();
    
public:
    
    GLuint textureId1;
    GLuint textureId2;
    
    GLint widthLoc;
    GLint heightLoc;
    
    GLuint framebuffer1;
};


#endif /* gaussian_blur_hpp */
