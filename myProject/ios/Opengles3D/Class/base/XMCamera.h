//
//  XMCamera.h
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/31.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface XMCamera : NSObject

@property (nonatomic, copy) void(^VideoDataBlock)(unsigned char *buffer, size_t width, size_t height);


- (void)startCaptureSession;

- (void)stopCaptureSession;

@end
