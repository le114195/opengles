//
//  BlendRend.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/15.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef BlendRend_hpp
#define BlendRend_hpp


#include "new_opengles_base.hpp"


class BlendRend:public NEW_OPENGLES_BASE
{
    
private:
    
    
    
public:
    
    void Init();
    
    void render(double duration);
    
    void thread_func();
    
    void setTexture(unsigned char *buffer, int width, int height, GLenum format);
    
public:
    
    GLuint textureId;
    int textureWidth = 0;
    int textureHeight = 0;
    
    GLuint blendTextureId;
    int blendW = 0;
    int blendH = 0;
    
    unsigned char *outBuffer;
    
    //正常混合
    const char *normalVShader;
    const char *normalFShader;
    
    //随机噪声
    const char *randNoseVShader;
    const char *randNoseFShader;
    
};

#endif /* BlendRend_hpp */
