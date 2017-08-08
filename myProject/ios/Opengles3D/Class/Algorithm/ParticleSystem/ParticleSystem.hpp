//
//  ParticleSystem.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/7.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include "new_opengles_base.hpp"

#define NUM_PARTICLES   1000
#define PARTICLE_SIZE   6

class ParticleSystem:public NEW_OPENGLES_BASE
{
public:
    
    void Init();
    
    void render();
    
    void Update (float deltaTime);
    
    void setTexture(unsigned char *buffer, int width, int height, GLenum format);
    
public:
    
    GLfloat lifetime[NUM_PARTICLES];
    GLfloat start[2 * NUM_PARTICLES];
    GLfloat end[2 * NUM_PARTICLES];
    
    GLuint textureId;
    int textureWidth = 0;
    int textureHeight = 0;
    
    unsigned char *outBuffer;
    
    float time = 1.0f;
    
    GLint timeLoc;
    
    GLint colorLoc;
    
    GLint centerPositionLoc;
    
    GLint samplerLoc;
};


#endif /* ParticleSystem_hpp */
