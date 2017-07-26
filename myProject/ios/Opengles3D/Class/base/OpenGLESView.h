//
//  OpenGLESView.h
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface OpenGLESView : UIView
{
    CAEAGLLayer     *_eaglLayer;
    EAGLContext     *_context;
}


@end
