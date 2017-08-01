//
//  MultipleSampleController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/27.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "MultipleSampleController.h"
#import "MultipleSampleView.h"

@interface MultipleSampleController ()



@end

@implementation MultipleSampleController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    // Do any additional setup after loading the view.
    MultipleSampleView *filterView = [[MultipleSampleView alloc] initWithFrame:self.view.bounds];
    
    [self.view addSubview:filterView];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
