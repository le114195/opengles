//
//  LighterView.h
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/17.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "OpenGLESView.h"

@interface LighterView : OpenGLESView

- (void)needRend:(unsigned char *)buffer width:(int)width height:(int)height;

@end
