//
//  real_time_render.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/27.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef real_time_render_hpp
#define real_time_render_hpp

#include "new_opengles_base.hpp"


class REALTIMERENDER:public NEW_OPENGLES_BASE
{
public:
    
    void Init();
    
    void render();
    
    void setTexture(unsigned char *buffer, int width, int height, GLenum format);

public:
    
    GLuint textureId;
    
    
};


#endif /* real_time_render_hpp */
