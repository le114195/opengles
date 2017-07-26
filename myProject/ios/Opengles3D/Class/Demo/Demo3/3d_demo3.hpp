//
//  3d_demo3.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef _d_demo3_hpp
#define _d_demo3_hpp

#include "OpenglesBase.hpp"

class DEMO3:public opengles_base {

    
private:
    
    int Init ( ESContext *esContext );
    
    static void Update ( ESContext *esContext, float deltaTime );
    
    static void Draw ( ESContext *esContext );
    
    static void ShutDown ( ESContext *esContext );
    
    int esGenBuffer (GLfloat **vertices, GLuint **indices);
    
public:
    
    int esMain(ESContext *esContext);
    
    struct UserData {
        /// Put platform specific data here
        void       *platformData;
        
        // Handle to a program object
        GLuint programObject;
        
        ESMatrix    mvpMatrix;
        
        // Uniform locations
        GLint       mvpLoc;
        
        GLfloat angle;
        
        // Vertex daata
        GLfloat  *vertices;
        GLuint   *indices;
        int       numIndices;
    };
    
};

#endif /* _d_demo3_hpp */
