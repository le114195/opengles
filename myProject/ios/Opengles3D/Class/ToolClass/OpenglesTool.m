//
//  OpenglesTool.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "OpenglesTool.h"

@implementation OpenglesTool


+ (GLubyte *)getBuffer:(UIImage *)image {
    
    // 1获取图片的CGImageRef
    CGImageRef rfImage = image.CGImage;
    if (!rfImage) {
        exit(1);
    }
    // 2 读取图片的大小
    size_t width = CGImageGetWidth(rfImage);
    size_t height = CGImageGetHeight(rfImage);
    
    GLubyte * spriteData = (GLubyte *) calloc(width * height * 4, sizeof(GLubyte)); //rgba共4个byte
    
    CGContextRef spriteContext = CGBitmapContextCreate(spriteData, width, height, 8, width*4,
                                                       CGImageGetColorSpace(rfImage), kCGImageAlphaPremultipliedLast);
    // 3在CGContextRef上绘图
    CGContextDrawImage(spriteContext, CGRectMake(0, 0, width, height), rfImage);
    
    CGContextRelease(spriteContext);
    
    return spriteData;
}


+ (const char *)readFileData:(NSString *)fileName
{
    NSString *vFilepath = [[NSBundle mainBundle] pathForResource:fileName ofType:nil];
    NSData *vData = [NSData dataWithContentsOfFile:vFilepath];
    NSString *vStr = [[NSString alloc] initWithData:vData encoding:NSUTF8StringEncoding];
    
    return [vStr UTF8String];
}

@end
