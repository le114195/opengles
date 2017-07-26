//
//  framebuffer.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef framebuffer_hpp
#define framebuffer_hpp

#include "new_opengles_base.hpp"

class FRAMEBUFFER_DEMO2:public NEW_OPENGLES_BASE {

public:
    
    void Init();
    
    void render();
    
    void setupTexture();
    
public:
    GLint textureId;
    
};


#endif /* framebuffer_hpp */
