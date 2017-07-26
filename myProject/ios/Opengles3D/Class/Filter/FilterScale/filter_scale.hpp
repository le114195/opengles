//
//  filter_scale.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef filter_scale_hpp
#define filter_scale_hpp

#include "OpenglesBase.hpp"


class FILTER_SCALE:public opengles_base {
    
public:
    
    int esMain(ESContext *esContext);
    
private:
    int Init ( ESContext *esContext );
    
    static void Update ( ESContext *esContext, float deltaTime );
    
    static void Draw ( ESContext *esContext );
    
    static void ShutDown ( ESContext *esContext );
    
public:
    
    struct UserData{
        
        /// Put platform specific data here
        void       *platformData;
        
        // Handle to a program object
        GLuint programObject;
        
        // Sampler locations
        GLint baseMapLoc;
        
        GLint alphaLoc;
        
        GLint offsetLoc;
        
        GLint mvpLoc;
        
        GLint vMvpLoc;
        
        // Texture handle
        GLuint tex1Id;
        
        char *buffer1;
        int buffer1_width;
        int buffer1_height;
        
        
        GLfloat angle;
        
        ESMatrix    mvpMatrix;
        ESMatrix    vMvpMatrix;
        
        float offset;
        int scaleStatus;
        
    };
};


#endif /* filter_scale_hpp */
