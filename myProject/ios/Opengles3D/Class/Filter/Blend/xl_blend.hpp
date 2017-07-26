//
//  xl_blend.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef xl_blend_hpp
#define xl_blend_hpp

#include "OpenglesBase.hpp"


class BLEND_XL:public opengles_base {
    
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
        
        const char *vShaderStr;
        const char *fShaderStr;
        
        // Handle to a program object
        GLuint programObject;
        
        // Sampler locations
        GLint tex1Loc;
        GLint tex2Loc;
        
        // Texture handle
        GLuint tex1Id;
        GLuint tex2Id;

        unsigned char *buffer1;
        int buffer1_width;
        int buffer1_height;
        
        char *buffer2;
        int buffer2_width;
        int buffer2_height;
        
        GLint alphaLoc;
        GLfloat alpha;
        
        GLfloat offset;
        GLint offsetLoc;
        
        GLfloat fstep;
        GLint fstepLoc;
    };
};


#endif /* xl_blend_hpp */
