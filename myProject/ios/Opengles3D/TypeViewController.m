//
//  TypeViewController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/15.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "TypeViewController.h"

@interface TypeViewController ()<UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, assign) NSInteger     type;

@property (nonatomic, strong) NSArray    *dataArray;

@property (nonatomic, strong) NSArray    *nameArray;

@end

@implementation TypeViewController


+ (instancetype)type:(NSInteger)type
{
    TypeViewController *typeVC = [[TypeViewController alloc] init];
    typeVC.type = type;
    return typeVC;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.automaticallyAdjustsScrollViewInsets = NO;
    
    if (self.type == 0) {//demo
        self.dataArray = @[@"ViewController", @"Demo2ViewController", @"Demo3ViewController", @"Demo4ViewController", @"Demo5ViewController", @"GPUImageController", @"FrameBufferController", @"DoubleSampleController", @"MultipleSampleController", @"RealTimeController", @"ParticleSystemController"];
        
        self.nameArray = @[@"混合测试", @"3D测试", @"3D测试", @"3D测试", @"3D测试", @"gpu滤镜", @"framebuffer测试", @"双重渲染", @"多重渲染", @"实时渲染", @"粒子效果"];
        
    }else if (self.type == 1) {//算法
        self.dataArray = @[@"EdgeDetectionController", @"SobelEdgeController", @"OneInputController", @"BlendViewController", @"GaussianBlurController"];
        self.nameArray = @[@"边缘检测算法", @"sobel边缘检测算法", @"算法集合", @"混合算法", @"高斯模糊"];
        
    }else if (self.type == 2) {//滤镜
        self.dataArray = @[@"Filter1Controller", @"Filter2Controller", @"ColorShakeController"];
        self.nameArray = @[@"灵魂出窍滤镜", @"移形换影滤镜", @"色层偏移"];
        
    }else {
        self.dataArray = @[];
        self.nameArray = @[];
    }
    
    
    [self tableviewConfigure];
    
    
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void)tableviewConfigure {
    
    UITableView *tableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 64, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height - 64) style:UITableViewStylePlain];
    
    [self.view addSubview:tableView];
    
    tableView.delegate = self;
    tableView.dataSource = self;
    
    [tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"UITableViewCell"];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.dataArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"UITableViewCell" forIndexPath:indexPath];
    
    cell.textLabel.text = [NSString stringWithFormat:@"%@: %@", self.nameArray[indexPath.row], self.dataArray[indexPath.row]];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *className = self.dataArray[indexPath.row];
    
    UIViewController *vc = [[NSClassFromString(className) alloc] init];
    [self.navigationController pushViewController:vc animated:true];
    
}




@end
