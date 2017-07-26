//
//  color_shake.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/24.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef color_shake_hpp
#define color_shake_hpp

#include "OpenglesBase.hpp"


class COLOR_SHAKE:public opengles_base {
    
public:
    
    int esMain(ESContext *esContext);
    
    static void draw_img(ESContext *esContext, void *buffer);
    
private:
    int Init ( ESContext *esContext );
    
    static void Update ( ESContext *esContext, float deltaTime );
    
    static void Draw ( ESContext *esContext );
    
    static void ShutDown ( ESContext *esContext );
    
public:
    
    struct UserData{
        
        /// Put platform specific data here
        void       *platformData;
        
        const char *vShader;
        const char *fShader;
        
        // Handle to a program object
        GLuint programObject;
        
        // Texture handle
        GLuint textureId;
        
        unsigned char *buffer;
        int buffer_width;
        int buffer_height;
        
        GLfloat offset[2];
        GLint offsetLoc;
        
        GLfloat offsetV;
        
        GLfloat texScale;
        GLint texScaleLoc;
        
        
        ESMatrix mvpMatrix;
        
    };
};


#endif /* color_shake_hpp */
