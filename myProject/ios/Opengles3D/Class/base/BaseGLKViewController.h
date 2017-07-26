//
//  BaseGLKViewController.h
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import <GLKit/GLKit.h>
#import "esUtil.h"


@interface BaseGLKViewController : GLKViewController
{
    
    ESContext _esContext;
}

@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

- (void)setupGL;

@end
