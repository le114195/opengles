//
//  filter_blur.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/24.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef filter_blur_hpp
#define filter_blur_hpp

#include "OpenglesBase.hpp"


class FILTER_BLUR:public opengles_base {
    
public:
    
    int esMain(ESContext *esContext);
    
    static void draw_img(ESContext *esContext, void *buffer, int width, int height);
    
private:
    
    int Init ( ESContext *esContext );
    
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
        
        float blurAngle;
        
        float fstep;
        
        GLint weightLoc;
        float *weight;
        int weightCount;
        
    };
};


#endif /* filter_blur_hpp */
