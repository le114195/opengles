//
//  Demo5ViewController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/17.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "Demo5ViewController.h"
#include "3d_demo5.hpp"
#import "OpenglesTool.h"

@interface Demo5ViewController ()

@end

@implementation Demo5ViewController

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
    
    UIImage *image = [UIImage imageNamed:@"12345.png"];
    
    _esContext.userData = malloc(sizeof(DEMO5::UserData));
    
    DEMO5::UserData *userData = (DEMO5::UserData *)_esContext.userData;
    
    userData->buffer = (char *)[OpenglesTool getBuffer:image];
    userData->buffer_width = image.size.width;
    userData->buffer_height = image.size.height;
    
    DEMO5 demo;
    demo.esMain(&_esContext);
}


@end
