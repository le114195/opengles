//
//  FrameBufferController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "FrameBufferController.h"
#import "FrameBufferView.h"


@interface FrameBufferController ()

@end

@implementation FrameBufferController
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.view = [[FrameBufferView alloc] initWithFrame:self.view.bounds];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


@end
