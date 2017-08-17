//
//  SignalRender.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/15.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef SignalRender_hpp
#define SignalRender_hpp

#include "new_opengles_base.hpp"


class SignalRender:public NEW_OPENGLES_BASE
{
    
private:
    
    void update(double time);
    
    void dataConfigure();
    
public:
    
    void lineRender(float alpha);
    
    void noseRender(double time);
    
    void rend(double duration);
    
    void setupFrameBuffer2();
    
    void Init();
    
    void render(double time);
    
    void setTexture(unsigned char *buffer, int width, int height, GLenum format);
    
public:
    
    GLuint currentProgram;
    GLuint currentFramebuffer;
    GLuint currentTextureId;
    GLuint inputTexture2;
    
    
    GLuint textureId;
    int textureW = 0;
    int textureH = 0;
    
    GLuint blendTextureId;
    int blendW = 0;
    int blendH = 0;
    
    
    //随机噪声
    GLuint noseProgram;
    GLuint noseFramebuffer;
    GLuint noseTextureId;
    const char *randNoseVShader;
    const char *randNoseFShader;
    
    //运动模糊
    GLuint motionProgram;
    GLuint motionFramebuffer;
    GLuint motionTextureId;
    const char *motionVShader;
    const char *motionFShader;
    
    //信号干扰
    GLuint signalProgram;
    GLuint signalFramebuffer;
    GLuint signalTextureId;
    const char *signalVShader;
    const char *signalFShader;
    
    //上下移动
    GLuint offsetProgram;
    GLuint offsetFramebuffer;
    GLuint offsetTextureId;
    const char *offsetVShader;
    const char *offsetFShader;
    
    
    //线条
    GLuint lineProgram;
    GLuint lineFramebuffer;
    GLuint lineTextureId;
    GLuint lineBlendTexture;
    const char *lineVShader;
    const char *lineFShader;
    
    //alpha_blend
    GLuint alphaProgram;
    const char *alphaVShader;
    const char *alphaFShader;
    
    GLuint edgeTexture;
    GLuint noseBlendTextureId;
    
};

#endif /* SignalRender_hpp */
