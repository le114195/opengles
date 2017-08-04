//
//  OneInputController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/3.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "OneInputController.h"
#import "OneInputView.h"

@interface OneInputController ()

@end

@implementation OneInputController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view = [[OneInputView alloc] initWithFrame:self.view.bounds];
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
