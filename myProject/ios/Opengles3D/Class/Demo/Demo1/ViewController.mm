//
//  ViewController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "ViewController.h"
#include "3d_demo1.hpp"
#import "OpenglesTool.h"

@interface ViewController ()


@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    memset( &_esContext, 0, sizeof( _esContext ) );
    
    _esContext.userData = malloc(sizeof(DEMO1::UserData));
    
    DEMO1::UserData *userData = (DEMO1::UserData *)_esContext.userData;
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    userData->buffer1 = [OpenglesTool getBuffer:image];
    userData->buffer1_width = image.size.width;
    userData->buffer1_height = image.size.height;
    
    UIImage *image2 = [UIImage imageNamed:@"IMG_1072.PNG"];
    userData->buffer2 = (char *)[OpenglesTool getBuffer:image2];
    userData->buffer2_width = image2.size.width;
    userData->buffer2_height = image2.size.height;
    
    DEMO1 demo1;
    demo1.esMain(&_esContext);
}



@end
