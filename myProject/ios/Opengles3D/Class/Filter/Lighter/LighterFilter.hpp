//
//  LighterFilter.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/17.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef LighterFilter_hpp
#define LighterFilter_hpp

#include "new_opengles_base.hpp"


class LighterFilter:public NEW_OPENGLES_BASE
{
    
public:
    
    void updateZoom(double time);
    
    void updateLight(double time);
    
public:
    
    void Init();
    
    void renderZoom(double duration);
    
    void render(double duration);
    
    void setTexture(unsigned char *buffer, int width, int height, GLenum format);
    
    ~LighterFilter();
    
public:
    
    GLuint textureId;
    int textureWidth = 0;
    int textureHeight = 0;
    
    
    GLuint zoomProgram;
    const char *zoomVShader;
    const char *zoomFShader;
    
    
};

#endif /* LighterFilter_hpp */
