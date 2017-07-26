//
//  Demo4ViewController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/14.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "Demo4ViewController.h"
#include "3d_demo4.hpp"

@interface Demo4ViewController ()

@end

@implementation Demo4ViewController

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
    
    _esContext.userData = malloc(sizeof(DEMO4::UserData));
    
    DEMO4 demo;
    demo.esMain(&_esContext);
}



@end
