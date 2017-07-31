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
#import "GLTexture.h"
#import "libyuv.h"

@interface RealTimeController ()<AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic, assign) BOOL          isFirst;

@property (nonatomic, strong) RealTimeView  *realView;

@property (nonatomic, strong) AVCaptureSession *captureSession;
@property (nonatomic, strong) AVCaptureDeviceInput *videoInput;
@property (nonatomic, strong) AVCaptureVideoDataOutput *videoOutput;

@end

@implementation RealTimeController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.isFirst = YES;
    
    self.realView = [[RealTimeView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:_realView];
    
    [self setupSession];
    
//    
//    UIImage *image = [UIImage imageNamed:@"sj_20160705_2.JPG"];
//    
//    void *buffer = [OpenglesTool getBuffer:image];
//    
//    [self.realView needRend:buffer width:(int)image.size.width height:(int)image.size.height];
//    
//    
//    free(buffer);
//    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



- (void)setupSession
{
    _captureSession = [[AVCaptureSession alloc] init];
    [_captureSession beginConfiguration];
    
    // 设置换面尺寸
    [_captureSession setSessionPreset:AVCaptureSessionPresetHigh];
    
    // 设置输入设备
    AVCaptureDevice *inputCamera = nil;
    NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    for (AVCaptureDevice *device in devices)
    {
        if ([device position] == AVCaptureDevicePositionBack)
        {
            inputCamera = device;
        }
    }
    
    if (!inputCamera) {
        return;
    }
    
    NSError *error = nil;
    _videoInput = [[AVCaptureDeviceInput alloc] initWithDevice:inputCamera error:&error];
    if ([_captureSession canAddInput:_videoInput])
    {
        [_captureSession addInput:_videoInput];
    }
    
    // 设置输出数据
    _videoOutput = [[AVCaptureVideoDataOutput alloc] init];
    [_videoOutput setAlwaysDiscardsLateVideoFrames:NO];
    
    [_videoOutput setVideoSettings:[NSDictionary dictionaryWithObject:[NSNumber numberWithInt:kCVPixelFormatType_32BGRA] forKey:(id)kCVPixelBufferPixelFormatTypeKey]];
    
    [_videoOutput setSampleBufferDelegate:self queue:dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)];
    
    
    if ([_captureSession canAddOutput:_videoOutput]) {
        [_captureSession addOutput:_videoOutput];
    }
    
//    AVCaptureVideoPreviewLayer *preLayer = [AVCaptureVideoPreviewLayer layerWithSession: _captureSession];//相机拍摄预览图层
//    preLayer.frame = self.view.bounds;
//    preLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
//    [self.view.layer addSublayer:preLayer];

    
    [_captureSession commitConfiguration];
    
    [_captureSession startRunning];
}



// 视频格式为：kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange或kCVPixelFormatType_420YpCbCr8BiPlanarFullRange
- (void)processVideoSampleBufferToRGB1:(CMSampleBufferRef)sampleBuffer
{
    //CFAbsoluteTime startTime = CFAbsoluteTimeGetCurrent();
    CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    //size_t count = CVPixelBufferGetPlaneCount(pixelBuffer);
    //printf("%zud\n", count);
    
    //表示开始操作数据
    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    
    int pixelWidth = (int) CVPixelBufferGetWidth(pixelBuffer);
    int pixelHeight = (int) CVPixelBufferGetHeight(pixelBuffer);
    
    GLTextureRGB *rgb = [[GLTextureRGB alloc] init];
    rgb.width = pixelWidth;
    rgb.height = pixelHeight;
    
    // Y数据
    //size_t y_size = pixelWidth * pixelHeight;
    uint8_t *y_frame = (uint8_t *)CVPixelBufferGetBaseAddressOfPlane(pixelBuffer, 0);
    
    // UV数据
    uint8_t *uv_frame = (uint8_t *)CVPixelBufferGetBaseAddressOfPlane(pixelBuffer, 1);
    //size_t uv_size = y_size/2;
    
    // ARGB = BGRA 大小端问题 转换出来的数据是BGRA
    uint8_t *bgra = (uint8_t *)malloc(pixelHeight * pixelWidth * 4);
    NV12ToARGB(y_frame, pixelWidth, uv_frame, pixelWidth, bgra, pixelWidth * 4, pixelWidth, pixelHeight);
    
    rgb.RGBA = bgra;
    
    // Unlock
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.realView needRend:rgb.RGBA width:rgb.width height:rgb.height];
    });
}



#pragma mark - <AVCaptureVideoDataOutputSampleBufferDelegate>
- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
    
    if (!self.captureSession.isRunning) return;
    
    if (captureOutput == self.videoOutput) {
        [connection setVideoOrientation:AVCaptureVideoOrientationPortrait];
        [connection setVideoMirrored:YES];
        
        if (self.isFirst) {
            self.isFirst = NO;
            return;
        }
        [self processVideoSampleBufferToRGB1:sampleBuffer];
    }
    
    
    

//    CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
//    CVPixelBufferLockBaseAddress( pixelBuffer, 0);
//    
//    int bufferWidth = (int)CVPixelBufferGetWidth(pixelBuffer);
//    int bufferHeight = (int)CVPixelBufferGetHeight(pixelBuffer);
//    
//    unsigned char * pixel = (unsigned char *)CVPixelBufferGetBaseAddress(pixelBuffer);
//    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
//    
//    dispatch_async(dispatch_get_main_queue(), ^{
//        cv::Mat src;
//        src.create(bufferHeight, bufferWidth, CV_8UC4);
//        memcpy(src.data, pixel, bufferWidth * bufferHeight * 4);
//        
//        UIImage *img = MatToUIImage(src);
//        unsigned char *buffer = [OpenglesTool getBuffer:img];
//        [self.realView needRend:buffer width:(int)bufferWidth height:(int)bufferHeight];
//    });
    
    
//    if (!self.captureSession.isRunning) {
//        return;
//    }else if (captureOutput == _videoOutput) {
//        [self processVideoSampleBufferToRGB1:sampleBuffer];
//    }
}



- (void)dealloc
{
    [_captureSession stopRunning];
}


@end
