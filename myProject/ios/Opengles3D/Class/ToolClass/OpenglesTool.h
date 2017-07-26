//
//  OpenglesTool.h
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface OpenglesTool : NSObject

+ (GLubyte *)getBuffer:(UIImage *)image;

+ (const char *)readFileData:(NSString *)fileName;

@end
