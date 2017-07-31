//
//  Filter2Controller.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/21.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "Filter2Controller.h"
#import "filter_demo2.hpp"
#import "OpenglesTool.h"
#import <AVFoundation/AVFoundation.h>
#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>


@interface Filter2Controller ()<AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic, assign) CGFloat           time;

@end

@implementation Filter2Controller
{
    CGFloat bufferWidth;
    CGFloat bufferHeight;
    
    unsigned char *buffer;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setupGL];
    
    [self setupCaptureSession];
    
    // Do any additional setup after loading the view.
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
    
    CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress( pixelBuffer, 0);
    
    bufferWidth = CVPixelBufferGetWidth(pixelBuffer);
    bufferHeight = CVPixelBufferGetHeight(pixelBuffer);
    
    unsigned char * pixel = (unsigned char *)CVPixelBufferGetBaseAddress(pixelBuffer);
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
    
    buffer = pixel;
}




- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    memset( &_esContext, 0, sizeof( _esContext ) );
    
    
    _esContext.userData = malloc(sizeof(FILTER_DEMO2::UserData));
    
    FILTER_DEMO2::UserData *userData = (FILTER_DEMO2::UserData *)_esContext.userData;
    
    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
    
    userData->buffer1 = (char *)[OpenglesTool getBuffer:image];
    userData->buffer1_width = image.size.width;
    userData->buffer1_height = image.size.height;
    
    FILTER_DEMO2 demo;
    demo.esMain(&_esContext);
}



- (void)update
{
    if ( _esContext.updateFunc )
    {
        FILTER_DEMO2::UserData *userData = (FILTER_DEMO2::UserData *)_esContext.userData;
        
        userData->buffer1 = (char *)buffer;
        userData->buffer1_width = bufferWidth;
        userData->buffer1_height = bufferHeight;
        
        _esContext.updateFunc( &_esContext, self.timeSinceLastUpdate );
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    _esContext.width = (GLint)view.drawableWidth;
    _esContext.height = (GLint)view.drawableHeight;
    
    if ( _esContext.drawFunc )
    {
        _esContext.drawFunc( &_esContext );
    }
}


@end
