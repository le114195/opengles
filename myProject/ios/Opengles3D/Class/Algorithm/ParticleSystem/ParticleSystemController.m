//
//  ParticleSystemController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/7.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "ParticleSystemController.h"
#import "ParticleSystemView.h"

@interface ParticleSystemController ()
{
    CADisplayLink *displayLink;
    
    NSTimer *timer;
    
}

@property (nonatomic, strong) ParticleSystemView *particView;

@end

@implementation ParticleSystemController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.particView = [[ParticleSystemView alloc] initWithFrame:CGRectMake(0, 64, self.view.bounds.size.width, self.view.bounds.size.width)];
    
    [self.view addSubview:self.particView];
    
    [self startMainLoop];
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) startMainLoop
{
    // Director::setAnimationInterval() is called, we should invalidate it first
    [timer invalidate];
    
    __weak __typeof(self)weakSelf = self;
    timer = [NSTimer timerWithTimeInterval:1.0 / 30 repeats:YES block:^(NSTimer * _Nonnull timer) {
        [weakSelf doCaller];
    }];
    [[NSRunLoop mainRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
}


- (void)stopTimer
{
    if (timer != nil) {
        [timer invalidate];
        timer = nil;
    }
}

-(void) doCaller
{
    [self.particView needRend:timer.timeInterval];
}

- (void)dealloc
{
    [self stopTimer];
}

@end
