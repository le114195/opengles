//
//  XMCamera.m
//  Opengles3D
//
//  Created by 勒俊 on 2017/7/31.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#import "XMCamera.h"
#import <AVFoundation/AVFoundation.h>

// 设置显示及视频编码帧率
#define XM_KENCODE_FPS 30

@interface XMCamera()<AVCaptureVideoDataOutputSampleBufferDelegate>

// camera
@property (nonatomic , strong) AVCaptureSession *captureSession;
@property (nonatomic , strong) AVCaptureDevice *videoDevice;
@property (nonatomic , strong) AVCaptureDeviceInput *videoDeviceInput;
@property (nonatomic , strong) AVCaptureVideoDataOutput *videoDataOutput;
@property (nonatomic , strong) AVCaptureConnection *videoConnection;

@property (nonatomic , strong) dispatch_queue_t bufferQueue;

@end

@implementation XMCamera


- (instancetype)init
{
    if ([super init]) {
        self.bufferQueue = dispatch_queue_create("com.sensetime.sensear.buffer", NULL);
        
        [self setupCaptureSession];
    }
    return self;
}


#pragma - mark -
#pragma - mark AVCapture

- (BOOL)setupCaptureSession
{
    self.captureSession = [[AVCaptureSession alloc] init];
    
    // 根据实际需要修改 sessionPreset
    self.captureSession.sessionPreset = AVCaptureSessionPresetiFrame1280x720;
    
    NSArray *devices = [AVCaptureDevice devices];
    for (AVCaptureDevice *device in devices) {
        if ([device hasMediaType:AVMediaTypeVideo]) {
            
            if ([device position] == AVCaptureDevicePositionFront) {
                self.videoDevice = device;
            }
        }
    }
    
    NSError *error = nil;
    
    self.videoDeviceInput = [AVCaptureDeviceInput deviceInputWithDevice:self.videoDevice error:&error];
    
    if (!self.videoDeviceInput || error) {
        return NO;
    }
    
    self.videoDataOutput = [[AVCaptureVideoDataOutput alloc] init];
    
    [self.videoDataOutput setAlwaysDiscardsLateVideoFrames:YES];
    
    [self.videoDataOutput setVideoSettings:[NSDictionary dictionaryWithObject:[NSNumber numberWithInt:kCVPixelFormatType_32BGRA] forKey:(id)kCVPixelBufferPixelFormatTypeKey]];
    
    if (!self.videoDataOutput) {
        
        return NO;
    }
    
    [self.videoDataOutput setSampleBufferDelegate:self queue:self.bufferQueue];
    
    [self.captureSession beginConfiguration];
    
    if ([self.captureSession canAddInput:self.videoDeviceInput]) {
        [self.captureSession addInput:self.videoDeviceInput];
    }
    
    if ([self.captureSession canAddOutput:self.videoDataOutput]) {
        [self.captureSession addOutput:self.videoDataOutput];
    }
    
    CMTime frameDuration = CMTimeMake(1 , XM_KENCODE_FPS);
    
    if ([self.videoDevice lockForConfiguration:&error]) {
        
        self.videoDevice.activeVideoMaxFrameDuration = frameDuration;
        self.videoDevice.activeVideoMinFrameDuration = frameDuration;
        
        [self.videoDevice unlockForConfiguration];
    }
    
    [self.captureSession commitConfiguration];
    
    self.videoConnection = [self.videoDataOutput connectionWithMediaType:AVMediaTypeVideo];
    
    if ([self.videoConnection isVideoOrientationSupported]) {
        
        [self.videoConnection setVideoOrientation:AVCaptureVideoOrientationPortrait];
    }
    
    if ([self.videoConnection isVideoMirroringSupported]) {
        
        [self.videoConnection setVideoMirrored:self.videoDevice.position == AVCaptureDevicePositionFront];
    }
    
    return YES;
}
- (void)startCaptureSession
{
    if (self.captureSession && ![self.captureSession isRunning]) {
        
        [self.captureSession startRunning];
    }
}

- (void)stopCaptureSession
{
    if (self.captureSession && [self.captureSession isRunning]) {
        
        [self.captureSession stopRunning];
    }
}

- (void)destroyCaptureEnv
{
    if (self.captureSession) {
        
        [self stopCaptureSession];
        
        [self.captureSession beginConfiguration];
        
        [self.captureSession removeOutput:self.videoDataOutput];
        [self.captureSession removeInput:self.videoDeviceInput];
        
        [self.captureSession commitConfiguration];
        
        self.captureSession = nil;
    }
}


#pragma mark - <AVCaptureVideoDataOutputSampleBufferDelegate>

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
    
    if (!self.captureSession.isRunning) return;
    
    // video
    if (connection == self.videoConnection) {
        
        CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
        CVPixelBufferLockBaseAddress( pixelBuffer, 0);
        
        int bufferWidth = (int)CVPixelBufferGetWidth(pixelBuffer);
        int bufferHeight = (int)CVPixelBufferGetHeight(pixelBuffer);
        
        unsigned char * pixel = (unsigned char *)CVPixelBufferGetBaseAddress(pixelBuffer);
        
        CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
        dispatch_async(dispatch_get_main_queue(), ^{
            if (_VideoDataBlock) {
                _VideoDataBlock(pixel, bufferWidth, bufferHeight);
            }
        });
    }
    
}


- (void)dealloc
{
    [self destroyCaptureEnv];
}



@end
