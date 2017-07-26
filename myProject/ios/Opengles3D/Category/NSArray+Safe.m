//
//  NSArray+Safe.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/13.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "NSArray+Safe.h"
#import <objc/runtime.h>

@implementation NSArray (Safe)

+ (void)load
{
    SEL safeSel = @selector(safeObjectAtIndex:);
    SEL unSafeSel = @selector(objectAtIndex:);
    
    Class class = NSClassFromString(@"__NSArrayI");
    
    Method safeMethod = class_getInstanceMethod(class, safeSel);
    Method unSafeMethod = class_getInstanceMethod(class, unSafeSel);
    
    method_exchangeImplementations(unSafeMethod, safeMethod);
}




- (id)safeObjectAtIndex:(NSUInteger)index {
    // 数组越界也不会崩，但是开发的时候并不知道数组越界
    
    if (index > (self.count - 1)) { // 数组越界
        NSAssert(NO, @"数组越界了"); // 只有开发的时候才会造成程序崩了
        return nil;
    }else { // 没有越界
        return [self safeObjectAtIndex:index];
    }
    
    
}


@end
