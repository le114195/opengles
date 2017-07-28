//
//  RealTimeView.h
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/27.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "OpenGLESView.h"

@interface RealTimeView : OpenGLESView

- (void)needRend:(unsigned char *)buffer width:(int)width height:(int)height;

@end
