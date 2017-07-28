//
//  RealTimeController.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/27.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "RealTimeController.h"
#import "RealTimeView.h"
#import "OpenglesTool.h"
#import <AVFoundation/AVFoundation.h>

@interface RealTimeController ()<AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic, assign) BOOL          isFirst;

@property (nonatomic, strong) RealTimeView  *realView;

@end

@implementation RealTimeController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.isFirst = YES;
    
    self.realView = [[RealTimeView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:_realView];
    
    [self setupCaptureSession];

    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    void *buffer = [OpenglesTool getBuffer:image];
    
    [self.realView needRend:buffer width:(int)image.size.width height:(int)image.size.height];

    
    free(buffer);

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



- (void)setupCaptureSession
{
    NSError *error = nil;
    
    // Create the session
    AVCaptureSession *session = [[AVCaptureSession alloc] init];//负责输入和输出设置之间的数据传递
    [session beginConfiguration];
    
    
    session.sessionPreset = AVCaptureSessionPresetHigh;//设置分辨率
    
    // Find a suitable AVCaptureDevice
    AVCaptureDevice *device = [self cameraWithPosition:AVCaptureDevicePositionFront];
    
    
    // Create a device input with the device and add it to the session.
    AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:device
                                                                        error:&error];
    if ([session canAddInput:input]) {
        [session addInput:input];
    }
    
    // Create a VideoDataOutput and add it to the session
    AVCaptureVideoDataOutput *output = [[AVCaptureVideoDataOutput alloc] init];//创建一个视频数据输出流
    output.alwaysDiscardsLateVideoFrames = YES;
    
    // Specify the pixel format
    output.videoSettings = [NSDictionary dictionaryWithObjectsAndKeys:
                            [NSNumber numberWithInt:kCVPixelFormatType_32BGRA], kCVPixelBufferPixelFormatTypeKey,
                            nil];
    
    if ([session canAddOutput:output]) {
        [session addOutput:output];
    }
    
    dispatch_queue_t queue = dispatch_queue_create("myQueue", NULL);
    [output setSampleBufferDelegate:self queue:queue];
    
    
    AVCaptureVideoPreviewLayer *preLayer = [AVCaptureVideoPreviewLayer layerWithSession: session];//相机拍摄预览图层
    preLayer.frame = self.view.bounds;
    preLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    [self.view.layer addSublayer:preLayer];
    preLayer.hidden = YES;
    
    [session commitConfiguration];
    
    [session startRunning];
}

- (AVCaptureDevice *)cameraWithPosition:(AVCaptureDevicePosition)position{
    NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    for ( AVCaptureDevice *device in devices )
        if ( device.position == position ) return device;
    return nil;
}


- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
    [connection setVideoOrientation:AVCaptureVideoOrientationPortrait];
    [connection setVideoMirrored:YES];
    
    if (self.isFirst) {
        self.isFirst = NO;
        return;
    }
    
    CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress( pixelBuffer, 0);
    
    size_t bufferWidth = CVPixelBufferGetWidth(pixelBuffer);
    size_t bufferHeight = CVPixelBufferGetHeight(pixelBuffer);
    
    unsigned char * pixel = (unsigned char *)CVPixelBufferGetBaseAddress(pixelBuffer);
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);

    
    [self.realView needRend:pixel width:(int)bufferWidth height:(int)bufferHeight];
}




@end
