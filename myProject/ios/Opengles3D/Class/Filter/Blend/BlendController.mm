//
//  BlendController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "BlendController.h"
#include "xl_blend.hpp"
#import "OpenglesTool.h"



@interface BlendController ()

@end

@implementation BlendController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    memset( &_esContext, 0, sizeof( _esContext ) );
    _esContext.userData = malloc(sizeof(BLEND_XL::UserData));
    
    BLEND_XL::UserData *userData = (BLEND_XL::UserData *)_esContext.userData;
    
    userData->vShaderStr = [OpenglesTool readFileData:@"xl_blend_shader.vs"];
    userData->fShaderStr = [OpenglesTool readFileData:@"xl_blend_shader.frag"];
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    userData->buffer1 = [OpenglesTool getBuffer:image];
    userData->buffer1_width = image.size.width;
    userData->buffer1_height = image.size.height;
    
    UIImage *image2 = [UIImage imageNamed:@"IMG_1072.PNG"];
    userData->buffer2 = (char *)[OpenglesTool getBuffer:image2];
    userData->buffer2_width = image2.size.width;
    userData->buffer2_height = image2.size.height;
    
    BLEND_XL demo1;
    demo1.esMain(&_esContext);
}



- (void)update
{
    if ( _esContext.updateFunc )
    {
        _esContext.updateFunc( &_esContext, self.timeSinceLastUpdate );
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    _esContext.width = (GLint)view.drawableWidth;
    _esContext.height = (GLint)view.drawableHeight;
    
    if ( _esContext.drawFunc )
    {
        _esContext.drawFunc( &_esContext );
    }
}



@end
