//
//  BlendView.h
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/15.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "OpenGLESView.h"

@interface BlendView : OpenGLESView

- (void)needRend:(unsigned char *)buffer width:(int)width height:(int)height;

@end
