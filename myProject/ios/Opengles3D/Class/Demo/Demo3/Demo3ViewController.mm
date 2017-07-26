//
//  Demo3ViewController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "Demo3ViewController.h"
#include "3d_demo3.hpp"

@interface Demo3ViewController ()

@end

@implementation Demo3ViewController

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
    
    _esContext.userData = malloc(sizeof(DEMO3::UserData));
    
    DEMO3 demo1;
    demo1.esMain(&_esContext);
}


@end
