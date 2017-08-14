//
//  one_input.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/3.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef one_input_hpp
#define one_input_hpp

#include "new_opengles_base.hpp"


class OneInput_C:public NEW_OPENGLES_BASE
{
public:
    void setupFrameBuffer2();
    
    void Init();
    
    void render();
    
    void renderToon();
    
    void thread_func();
    
    void setTexture(unsigned char *buffer, int width, int height, GLenum format);
public:
    
    GLuint toonProgram;
    const char *toonVShader;
    const char *toonFSahder;
    
    GLuint textureId;
    GLint textureWLoc;
    GLint textureHLoc;
    
    int textureWidth = 0;
    int textureHeight = 0;
    
    unsigned char *outBuffer;
    
    
    GLuint textureId2;
    GLuint textureId3;
    GLuint textureId4;
    GLuint textureId5;
    
    GLuint program2;
    GLuint program3;
    
    GLuint gProgram;
    const char* g_vShader;
    const char *g_fShader;
    
    GLuint framebuffer2;
    GLuint framebuffer3;
    GLuint framebuffer4;
    GLuint framebuffer5;
    
    //双边模糊
    const char* bvShader;
    const char* bfShader;
    
    
    //梯度
    const char *tonsureVShader;
    const char *tonsureFShader;
    
};

#endif /* one_input_hpp */
