//
//  new_opengles_base.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef new_opengles_base_hpp
#define new_opengles_base_hpp

#include "GLUtil.h"
#include <stdlib.h>


class NEW_OPENGLES_BASE {
    
    
public:
    
    void setupFrameAndRenderBuffer();
    
    void destoryRenderAndFrameBuffer();
    
public:
    
    const char *vShader;
    const char *fShader;
    
    GLuint programObject;
    
    GLuint colorRenderBuffer;
    GLuint frameBuffer;
    
    int s_width;
    int s_height;
    
};

#endif /* new_opengles_base_hpp */
