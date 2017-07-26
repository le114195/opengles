//
//  edge_detection.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/24.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef edge_detection_hpp
#define edge_detection_hpp

#include "OpenglesBase.hpp"


class EDGE_DETECTION:public opengles_base {
    
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
        
        const char *vShader;
        const char *fShader;
        
        // Handle to a program object
        GLuint programObject;
        
        // Texture handle
        GLuint textureId;
        
        unsigned char *buffer;
        int buffer_width;
        int buffer_height;
    };
};

#endif /* edge_detection_hpp */
