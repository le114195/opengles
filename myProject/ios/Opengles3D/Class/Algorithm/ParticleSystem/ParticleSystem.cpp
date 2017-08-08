//
//  ParticleSystem.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/7.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "ParticleSystem.hpp"

void ParticleSystem::Init()
{
    programObject = gl_esLoadProgram(vShader, fShader);
    
    int i = 0;
    for ( i = 0; i < NUM_PARTICLES; i++ ) {
        start[i * 2] = ( ( float ) ( rand() % 10000 ) / 40000.0f ) - 0.125f;
        start[i * 2 + 1] = ( ( float ) ( rand() % 10000 ) / 40000.0f ) - 0.125f;
        
        end[i * 2] = ( ( float ) ( rand() % 10000 ) / 5000.0f ) - 1.0f;
        end[i * 2 + 1] = ( ( float ) ( rand() % 10000 ) / 5000.0f ) - 1.0f;
        
        lifetime[i] = ( ( float ) ( rand() % 10000 ) / 10000.0f );
    }
    
    timeLoc = glGetUniformLocation(programObject, "u_time");
    colorLoc = glGetUniformLocation(programObject, "u_color");
    centerPositionLoc = glGetUniformLocation(programObject, "u_centerPosition");
    samplerLoc = glGetUniformLocation(programObject, "s_texture");
}


void ParticleSystem::setTexture(unsigned char *buffer, int width, int height, GLenum format)
{
    if (textureId == 0 || textureWidth != width || textureHeight != height) {
        textureId = createTexture2D(format, width, height, buffer);
        textureWidth = width;
        textureHeight = height;
    }else {
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, buffer);
    }
}


///
//  Update time-based variables
//
void ParticleSystem::Update (float deltaTime)
{
    time += deltaTime;
    
    if (time >= 1.0f) {
        
        float centerPos[3];
        float color[4];
        
        time = 0.0f;
        
        // Pick a new start location and color
        centerPos[0] = ( ( float ) ( rand() % 10000 ) / 10000.0f ) - 0.5f;
        centerPos[1] = ( ( float ) ( rand() % 10000 ) / 10000.0f ) - 0.5f;
        
        // Pick a new start location and color
        glUniform2fv (centerPositionLoc, 1, &centerPos[0]);
        
        // Random color
        color[0] = ( ( float ) ( rand() % 10000 ) / 20000.0f ) + 0.5f;
        color[1] = ( ( float ) ( rand() % 10000 ) / 20000.0f ) + 0.5f;
        color[2] = ( ( float ) ( rand() % 10000 ) / 20000.0f ) + 0.5f;
        color[3] = 0.5;
        
        glUniform4fv (colorLoc, 1, &color[0]);
    }
    glUniform1f(timeLoc, time);
}

void ParticleSystem::render()
{
    glUseProgram(programObject);//黑白
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    // Load the vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof ( GLfloat ), start);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), end);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(GLfloat), lifetime);
    
    
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    glEnableVertexAttribArray (2);
    
    // Blend particles
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE );
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    // Set the sampler texture unit to 0
    glUniform1i (samplerLoc, 0);
    
    glDrawArrays (GL_POINTS, 0, NUM_PARTICLES);
}


