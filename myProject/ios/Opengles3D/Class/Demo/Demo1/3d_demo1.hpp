//
//  3d_demo1.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef _d_demo1_hpp
#define _d_demo1_hpp

#include "esUtil.h"


class DEMO1 {
    
public:
    
    int esMain(ESContext *esContext);
    
private:
    
    GLuint LoadTexture2 ( void *ioContext, char *buffer, int width, int height );
    
    int Init ( ESContext *esContext );
    
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
        GLint lightMapLoc;
        
        // Texture handle
        GLuint baseMapTexId;
        GLuint lightMapTexId;
        
        GLuint img2TexId;
        
        unsigned char *buffer1;
        int buffer1_width;
        int buffer1_height;
        
        char *buffer2;
        int buffer2_width;
        int buffer2_height;
    };
};


#endif /* _d_demo1_hpp */
