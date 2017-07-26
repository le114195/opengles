//
//  OneTextureController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/22.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "OneTextureController.h"
#include "one_texture.hpp"
#import "OpenglesTool.h"

@interface OneTextureController ()

@end

@implementation OneTextureController

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
    _esContext.userData = malloc(sizeof(FILTER_ONE_TEXTURE::UserData));
    
    FILTER_ONE_TEXTURE::UserData *userData = (FILTER_ONE_TEXTURE::UserData *)_esContext.userData;
    
    userData->vShader = [OpenglesTool readFileData:@"one_texture_shader4.vs"];
    userData->fShader = [OpenglesTool readFileData:@"one_texture_shader4.frag"];
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    userData->buffer = [OpenglesTool getBuffer:image];
    userData->buffer_width = image.size.width;
    userData->buffer_height = image.size.height;
    
    FILTER_ONE_TEXTURE demo;
    demo.esMain(&_esContext);
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
