//
//  filter_demo2.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef filter_demo2_hpp
#define filter_demo2_hpp

#include "OpenglesBase.hpp"


class FILTER_DEMO2:public opengles_base {
    
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
        
        GLint fstepLoc;
        
        // Texture handle
        GLuint tex1Id;
        
        char *buffer1;
        int buffer1_width;
        int buffer1_height;
        
        float offset;
        float alpha;
        float fstep;
        
    };
};


#endif /* filter_demo2_hpp */
