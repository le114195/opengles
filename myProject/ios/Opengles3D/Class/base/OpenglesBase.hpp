//
//  OpenglesBase.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef OpenglesBase_hpp
#define OpenglesBase_hpp

#include "esUtil.h"

class opengles_base {
    
public:
    static GLuint LoadTexture ( void *ioContext, char *buffer, int width, int height );
    
    static GLuint createVBO(GLenum target, int usage, int datSize, void *data);
    
};




#endif /* OpenglesBase_hpp */
