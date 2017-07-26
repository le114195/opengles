//
//  UIViewController+Safe.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "UIViewController+Safe.h"
#import <objc/runtime.h>

@implementation UIViewController (Safe)

+ (void)load
{
    SEL unSafeSel = @selector(viewDidLoad);
    SEL safeSel = @selector(safeViewDidLoad);

    Class class = NSClassFromString(@"UIViewController");
 
    Method unSafeMethod = class_getInstanceMethod(class, unSafeSel);
    Method safeMethod = class_getInstanceMethod(class, safeSel);
    
    method_exchangeImplementations(unSafeMethod, safeMethod);
}


- (void)safeViewDidLoad {
    
    NSLog(@"dddd");
    
    [self safeViewDidLoad];
    
}


@end
