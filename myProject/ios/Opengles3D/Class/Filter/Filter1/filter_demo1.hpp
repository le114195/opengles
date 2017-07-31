//
//  filter_demo1.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef filter_demo1_hpp
#define filter_demo1_hpp

#include "OpenglesBase.hpp"


class FILTER_DEMO1:public opengles_base {
    
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
        
        const char* vShader;
        const char* fShader;
        
        
        // Texture handle
        GLuint tex1Id;
        
        char *buffer1;
        int buffer1_width;
        int buffer1_height;
        
        float scale;
        GLint scaleLoc;
        
        GLint alphaLoc;
        float alpha;

    };
};



#endif /* filter_demo1_hpp */
