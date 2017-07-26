//
//  DoubleSampleController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/26.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "DoubleSampleController.h"
#import "DoubleSampleView.h"

@interface DoubleSampleController ()

@end

@implementation DoubleSampleController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view = [[DoubleSampleView alloc] initWithFrame:self.view.bounds];
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
