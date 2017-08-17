//
//  SignalRender.cpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/15.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#include "SignalRender.hpp"
#include <math.h>

void SignalRender::setupFrameBuffer2()
{
    
    motionTextureId = createTexture2D(GL_RGBA, s_width, s_height, NULL);
    glGenFramebuffers(1, &motionFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, motionFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, motionTextureId, 0);
    
    noseTextureId = createTexture2D(GL_RGBA, s_width, s_height, NULL);
    glGenFramebuffers(1, &noseFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, noseFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, noseTextureId, 0);

    lineTextureId = createTexture2D(GL_RGBA, s_width, s_height, NULL);
    glGenFramebuffers(1, &lineFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, lineFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, lineTextureId, 0);
    
    
    signalTextureId = createTexture2D(GL_RGBA, s_width, s_height, NULL);
    glGenFramebuffers(1, &signalFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, signalFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, signalTextureId, 0);
    
    
    offsetTextureId = createTexture2D(GL_RGBA, s_width, s_height, NULL);
    glGenFramebuffers(1, &offsetFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, offsetFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, offsetTextureId, 0);
    
}

void SignalRender::Init()
{
    alphaProgram = gl_esLoadProgram(alphaVShader, alphaFShader);
    
    programObject = gl_esLoadProgram(vShader, fShader);
    
    motionProgram = gl_esLoadProgram(motionVShader, motionFShader);
    
    lineProgram = gl_esLoadProgram(lineVShader, lineFShader);
    
    offsetProgram = gl_esLoadProgram(offsetVShader, offsetFShader);
    
    signalProgram = gl_esLoadProgram(signalVShader, signalFShader);
    
    //随机噪点
    noseProgram = gl_esLoadProgram(randNoseVShader, randNoseFShader);
    
    inputTexture2 = 0;
}


void SignalRender::setTexture(unsigned char *buffer, int width, int height, GLenum format)
{
    if (textureId == 0 || textureW != width || textureH != height) {
        textureId = createTexture2D(format, width, height, buffer);
        textureW = width;
        textureH = height;
    }else {
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, buffer);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void SignalRender::rend(double duration)
{
    static float time = 0;
    time += duration;
    
    if (time < 0) {
        currentProgram = programObject;
        currentFramebuffer = frameBuffer;
        currentTextureId = textureId;
        render(time);
        
    }else {
    
        currentProgram = motionProgram;
        currentFramebuffer = motionFramebuffer;
        currentTextureId = textureId;
        render(time);
        
        currentProgram = noseProgram;
        currentFramebuffer = noseFramebuffer;
        currentTextureId = motionTextureId;
        inputTexture2 = blendTextureId;
        render(time);
        
        currentProgram = signalProgram;
        currentFramebuffer = signalFramebuffer;
        currentTextureId = noseTextureId;
        render(time);
        
        currentProgram = offsetProgram;
        currentFramebuffer = offsetFramebuffer;
//        currentFramebuffer = frameBuffer;
        currentTextureId = signalTextureId;
        render(time);

        currentProgram = programObject;
        currentFramebuffer = frameBuffer;
        currentTextureId = offsetTextureId;
        render(time);
        
        currentProgram = programObject;
        currentTextureId = lineBlendTexture;
        lineRender(1.0);
        
        
        int cirCount = time / 1400;
        float cirTime = time - cirCount * 1400;
        float alpha = 0.0;
        
        if (cirTime < 120) {
            alpha = cirTime / 120.0 * 1.0;
        }else if (cirTime > 120 && cirTime < 680) {
            alpha = 1.0;
        }else if (cirTime > 680 && cirTime < 800) {
            alpha = 1.0 - (cirTime - 680.0) / 120.0;
        }else {
            alpha = 0.0;
        }
        currentProgram = alphaProgram;
        currentTextureId = edgeTexture;
        lineRender(alpha);
        
        
        if (cirTime < 280) {
            alpha = 0.0;
        }else if (cirTime > 280 && cirTime < 400) {
            alpha = (cirTime - 280) / 120.0 * 0.5 + 0.3;
        }else if (cirTime > 400 && cirTime < 520) {
            alpha = 0.8 - (cirTime - 400) / 120.0 * 0.5;
        }else {
            alpha = 0.0;
        }
        currentProgram = alphaProgram;
        currentTextureId = noseBlendTextureId;
        lineRender(alpha);
    }

}


void SignalRender::lineRender(float alpha)
{
    static GLfloat vVertices[] = {
        -1.0f,  1.0f, 0.0f, // Position 0
        0.0f,  0.0f,        // TexCoord 0
        -1.0f, -1.0f, 0.0f, // Position 1
        0.0f,  1.0f,        // TexCoord 1
        1.0f, -1.0f, 0.0f,  // Position 2
        1.0f,  1.0f,        // TexCoord 2
        1.0f,  1.0f, 0.0f,  // Position 3
        1.0f,  0.0f,        // TexCoord 3
    };
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glUseProgram(currentProgram);
    
    glViewport(0, 0, s_width, s_height);
    
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, currentTextureId);
    
    glUniform1f(glGetUniformLocation(currentProgram, "alpha_t"), alpha);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}


void SignalRender::render(double time)
{
    static GLfloat vVertices[] = {
        -1.0f,  1.0f, 0.0f, // Position 0
        0.0f,  0.0f,        // TexCoord 0
        0.0f,  0.0f,
        -1.0f, -1.0f, 0.0f, // Position 1
        0.0f,  1.0f,        // TexCoord 1
        0.0f,  1.0f,
        1.0f, -1.0f, 0.0f,  // Position 2
        1.0f,  1.0f,        // TexCoord 2
        1.0f,  1.0f,
        1.0f,  1.0f, 0.0f,  // Position 3
        1.0f,  0.0f,        // TexCoord 3
        1.0f,  0.0f,
    };
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    
    glBindFramebuffer(GL_FRAMEBUFFER, currentFramebuffer);
    glUseProgram(currentProgram);
    
    glViewport(0, 0, s_width, s_height);
    
    // Clear the color buffer
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear ( GL_COLOR_BUFFER_BIT );
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), &vVertices[3]);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), &vVertices[5]);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, currentTextureId);
    glUniform1i(glGetUniformLocation(currentProgram, "inputImageTexture"), 0);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, inputTexture2);
    glUniform1i(glGetUniformLocation(currentProgram, "inputImageTexture2"), 1);
    
    update(time);
    
    //启动混合：透明通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}


void SignalRender::update(double time) {
    
    int cirCount = time / 1400;
    float cirTime = time - cirCount * 1400;
    
    float s_height = 1080.0;

    //运动模糊参数
    float _blurSize = 0.0;
    float _blurAngle = 180.0;
    
    //随机噪声参数
    float random = (rand() % 3000) / 1000.0;
    glUniform1f(glGetUniformLocation(noseProgram, "random"), random);
    
    //位置偏移参数
    float offset = 0;
    
    if (cirTime > 0 && cirTime < 200) {
        offset = 260.0 / s_height * cirTime / 200.0;
        _blurSize = 260.0 / 200.0;
    } if (cirTime > 200 && cirTime < 400) {
        offset = 260.0 / s_height - 430.0 / s_height * (cirTime - 200) / 200.0;
        _blurSize = 430.0 / 200.0;
    }else if (cirTime > 400 && cirTime < 600) {
        offset = (260.0 - 430.0) / s_height + 240.0 / s_height * (cirTime - 400) / 200.0;
        _blurSize = 240.0 / 200.0;
    }else if (cirTime > 600 && cirTime < 800) {
        offset = (260.0 - 430.0 + 240) / s_height - 70.0 / s_height * (cirTime - 600) / 200.0;
        _blurSize = 70.0 / 200.0;
    }
    
    _blurSize *= 2;
    float para[2] = {0.0, 0.0};
    float aspectRatio = 1.0;
    aspectRatio = (1.0 * s_width / s_height);
    para[0] = _blurSize * sin(_blurAngle * M_PI / 180.0) * aspectRatio / s_height;
    para[1] = _blurSize * cos(_blurAngle * M_PI / 180.0) / s_height;
    glUniform2fv(glGetUniformLocation(motionProgram, "directionalTexelStep"), 1, para);
    
    glUniform1f(glGetUniformLocation(offsetProgram, "offsetY"), offset);
    
    //信号干扰参数
    float location[3] = {0.0, 0.0, 0.0};
    float width[3] = {0.0, 0.0, 0.0};
    float offset_step[3] = {0.0, 0.0, 0.0};
    
//    float location1[3] = {750.0 / 1080.0, 1060.0 / 1080.0, 0.0};
//    float width1[3] = {220.0 / 1080.0, 220.0/1080.0, 0.0};
//    float offset_step1[3] = {30.0/1080.0, -30.0/1080.0, 0.0};
//
//    float location2[3] = {580.0 / 1080.0, 860.0 / 1080.0, 0.0};
//    float width2[3] = {60.0 / 1080.0, 220.0/1080.0, 0.0};
//    float offset_step2[3] = {40.0/1080.0, 40.0/1080.0, 0.0};
//    
//    float location3[3] = {280.0 / 1080.0, 750.0 / 1080.0, 1060.0 / 1080.0};
//    float width3[3] = {220.0 / 1080.0, 60.0/1080.0, 220.0/1080.0};
//    float offset_step3[3] = {40.0/1080.0, 40.0/1080.0, 40.0/1080.0};
//    
//    float location4[3] = {320.0 / 1080.0, 1020.0 / 1080.0, 0.0};
//    float width4[3] = {500.0 / 1080.0, 40.0/1080.0, 0.0};
//    float offset_step4[3] = {40.0/1080.0, 40.0/1080.0, 0.0};
//    if (time > 0 && time < 80) {
//        location[0] = 1000.0 / s_height;
//        width[0] = 280.0 / s_height;
//        offset_step[0] = time / 80.0 * 30.0 / s_height;
//    }else if (time > 80 && time < 120) {
//        location[0] = 1000.0 / s_height;
//        width[0] = 280.0 / s_height;
//        offset_step[0] = 30.0 / s_height;
//    }else {
//        switch (count) {
//            case 0:
//                for (int i = 0; i < 3; i++) {
//                    location[i] = location1[i];
//                    width[i] = width1[i];
//                    offset_step[i] = offset_step1[i];
//                }
//                break;
//            case 1:
//                for (int i = 0; i < 3; i++) {
//                    location[i] = location2[i];
//                    width[i] = width2[i];
//                    offset_step[i] = offset_step2[i];
//                }
//                break;
//            case 2:
//                for (int i = 0; i < 3; i++) {
//                    location[i] = location3[i];
//                    width[i] = width3[i];
//                    offset_step[i] = offset_step3[i];
//                }
//                break;
//            case 3:
//                for (int i = 0; i < 3; i++) {
//                    location[i] = location4[i];
//                    width[i] = width4[i];
//                    offset_step[i] = offset_step4[i];
//                }
//                break;
//            default:
//                break;
//        }
//    }

    
    int cirCount2 = time / 300;
    float cirTime2 = time - cirCount2 * 300;
    
    if (cirTime2 > 0 && cirTime2 < 80) {
        location[0] = 1000.0 / s_height;
        width[0] = 280.0 / s_height;
        offset_step[0] = cirTime2 / 80.0 * 30.0 / s_height;
    }else if (cirTime2 > 80 && cirTime2 < 120) {
        location[0] = 1000.0 / s_height;
        width[0] = 280.0 / s_height;
        offset_step[0] = 30.0 / s_height;
    }else if (cirTime2 > 120 && cirTime2 < 160) {
        location[0] = 750.0 / s_height;
        width[0] = 220.0 / s_height;
        offset_step[0] = 30.0 / s_height;
        
        location[1] = 1060.0 / s_height;
        width[1] = 220.0 / s_height;
        offset_step[1] = -30.0 / s_height;
    }else if (cirTime2 > 160 && cirTime2 < 200) {
        location[0] = 580.0 / s_height;
        width[0] = 60.0 / s_height;
        offset_step[0] = 40.0 / s_height;
        
        location[1] = 860.0 / s_height;
        width[1] = 220.0 / s_height;
        offset_step[1] = 40.0 / s_height;
    }else if (cirTime2 > 200 && cirTime2 < 240) {
        location[0] = 280.0 / s_height;
        width[0] =220.0 / s_height;
        offset_step[0] = 40.0 / s_height;
        
        location[1] = 750.0 / s_height;
        width[1] = 60.0 / s_height;
        offset_step[1] = 40.0 / s_height;
        
        location[1] = 1060.0 / s_height;
        width[1] = 220.0 / s_height;
        offset_step[1] = 40.0 / s_height;
    }else if (cirTime2 > 240 && cirTime2 < 300) {
        location[0] = 320.0 / s_height;
        width[0] =500.0 / s_height;
        offset_step[0] = 40.0 / s_height;
        
        location[1] = 1020.0 / s_height;
        width[1] = 40.0 / s_height;
        offset_step[1] = 40.0 / s_height;
    }
    
    
    glUniform1fv(glGetUniformLocation(signalProgram, "location"), 3, location);
    glUniform1fv(glGetUniformLocation(signalProgram, "width"), 3, width);
    glUniform1fv(glGetUniformLocation(signalProgram, "step_offset"), 3, offset_step);
    
}





