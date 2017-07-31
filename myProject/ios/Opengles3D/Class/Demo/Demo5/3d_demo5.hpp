//
//  3d_demo5.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/17.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef _d_demo5_hpp
#define _d_demo5_hpp

#include "OpenglesBase.hpp"

class DEMO5:public opengles_base {

private:
    
    int Init(ESContext *esContext);
    
    static void Update(ESContext *esContext, float deltaTime);
    
    static void Draw(ESContext *esContext);
    
    static void ShutDown(ESContext *esContext);
    
public:
    
    int esMain(ESContext *esContext);
    
    
    struct UserData {
        
        void *platData;
        
        GLuint programObject;
        
        GLuint  texId;
        GLint   imgLoc;
        char *buffer;
        int buffer_width;
        int buffer_height;
        
        GLfloat *vertices;
        GLuint  *indices;
        GLfloat *colors;
        GLuint  numIndices;
        
        GLint   mvpLoc;
        
        GLfloat angle;
        
        ESMatrix    mvpMatrix;
        
    };
};


#endif /* _d_demo5_hpp */
