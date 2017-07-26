//
//  GaussianBlurController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "GaussianBlurController.h"
#import "GaussianBlurView.h"

@interface GaussianBlurController ()

@end

@implementation GaussianBlurController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view = [[GaussianBlurView alloc] initWithFrame:self.view.bounds];
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
