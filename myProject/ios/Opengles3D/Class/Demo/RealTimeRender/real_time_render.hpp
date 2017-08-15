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
    
private:
    
    void setupSignalP();
    
    
public:
    
    void Init();
    
    void render();
    
    void thread_func();
    
    void setTexture(unsigned char *buffer, int width, int height, GLenum format);

public:
    
    GLuint textureId;
    int textureWidth = 0;
    int textureHeight = 0;
    
    unsigned char *outBuffer;
    
};


#endif /* real_time_render_hpp */
