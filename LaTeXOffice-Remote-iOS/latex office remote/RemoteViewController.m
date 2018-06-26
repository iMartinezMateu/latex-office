//
//  RemoteViewController.m
//  LaTeX Office Remote
//
//  Created by Iván Martínez Mateu on 6/8/15.
//  Copyright (c) 2015 Segoware. All rights reserved.
//

#import "RemoteViewController.h"
#define TAG_WRITE_AUTH_PIN  1
#define TAG_HELLO 100
#define TAG_REQUEST_AUTH_PIN 101
#define TAG_RESPONSE_AUTH_PIN 102
#define TAG_REQUEST_NEXT_SLIDE 103
#define TAG_RESPONSE_NEXT_SLIDE 104
#define TAG_REQUEST_PREVIOUS_SLIDE 105
#define TAG_RESPONSE_PREVIOUS_SLIDE 106
#define TAG_REQUEST_MINIMIZE 107
#define TAG_RESPONSE_MINIMIZE 108
#define TAG_REQUEST_MAXIMIZE 109
#define TAG_RESPONSE_MAXIMIZE 110
#define TAG_RESPONSE_IMAGE 111

#define REFRESH_CHECKS 2 //Number of refresh iterations to check if the page/slide image has been received correctly.

@implementation RemoteViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(imageTap)];
    [tap setNumberOfTouchesRequired:1];
    [tap setNumberOfTapsRequired:1];
    [self.imageView addGestureRecognizer:tap];
    
    self->socket = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];
    
    NSError *err = nil;
    if (![self->socket connectToHost:serverAddress onPort:17215 error:&err]) // Asynchronous!
    {
        // If there was an error, it's likely something like "already connected" or "no delegate set"
        NSLog(@"I goofed: %@", err);
    }

    
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)imageTap
{
    [socket writeData:[[NSString stringWithFormat:@"NEXT_SLIDE"] dataUsingEncoding:NSUTF8StringEncoding] withTimeout:-1 tag:TAG_REQUEST_NEXT_SLIDE];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) setServerAddress:(NSString *)address
{
    serverAddress = address;
}

-(NSString*) getServerAddress
{
    return serverAddress;
}

-(void) setPin:(NSString *)code
{
    pinCode = code;
}

-(NSString*) getPin
{
    return pinCode;
}

- (void)socket:(GCDAsyncSocket *)sender didConnectToHost:(NSString *)host port:(UInt16)port
{
    [socket readDataWithTimeout:-1 tag:TAG_HELLO];
    [socket readDataWithTimeout:-1 tag:TAG_REQUEST_AUTH_PIN];
    [socket writeData:[[NSString stringWithFormat:@"AUTH_PIN %@",pinCode] dataUsingEncoding:NSUTF8StringEncoding] withTimeout:-1 tag:TAG_WRITE_AUTH_PIN];
    
    
    
}

- (void)socket:(GCDAsyncSocket *)sock didWriteDataWithTag:(long)tag
{
    if (tag == TAG_WRITE_AUTH_PIN)
    {
        NSLog(@"Pin code sent!");
        [socket readDataWithTimeout:-1 tag:TAG_RESPONSE_AUTH_PIN];
      
            [socket readDataToLength:615000 withTimeout:-1 tag:TAG_RESPONSE_IMAGE];
        [socket readDataWithTimeout:-1 tag:TAG_RESPONSE_IMAGE];


        
    }
    else if (tag == TAG_REQUEST_NEXT_SLIDE)
    {
        NSLog(@"Next Slide Petition sent!");
        [socket readDataWithTimeout:-1 tag:TAG_RESPONSE_NEXT_SLIDE];
    }
    else if (tag == TAG_REQUEST_PREVIOUS_SLIDE)
    {
        NSLog(@"Previous Slide Petition sent!");
        [socket readDataWithTimeout:-1 tag:TAG_RESPONSE_PREVIOUS_SLIDE];
    }
    else if (tag == TAG_REQUEST_MINIMIZE)
    {
        NSLog(@"Minimize Slide Petition sent!");
        [socket readDataWithTimeout:-1 tag:TAG_RESPONSE_MINIMIZE];
    }
    else if (tag == TAG_REQUEST_MAXIMIZE)
    {
        NSLog(@"Maximize Slide Petition sent!");
        [socket readDataWithTimeout:-1 tag:TAG_RESPONSE_MAXIMIZE];
    }
    
}

- (void)socket:(GCDAsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{
    
    NSString* serverOutput = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    NSLog(@"%@",serverOutput);

   if (tag == TAG_RESPONSE_NEXT_SLIDE)
   {
    
       [socket readDataWithTimeout:-1 tag:TAG_RESPONSE_IMAGE];

    

   }
    
   else if (tag == TAG_RESPONSE_PREVIOUS_SLIDE)
   {
     
       [socket readDataWithTimeout:-1 tag:TAG_RESPONSE_IMAGE];

    

   }

    else if (tag== TAG_RESPONSE_IMAGE)
    {
  
        NSMutableData* imageBuffer =  [[NSMutableData alloc] init];
        dispatch_async(dispatch_get_main_queue(), ^{
            @autoreleasepool {
                
                NSLog(@"Thread Data Length is %lu", (unsigned long)[data length]);
             
                
                [imageBuffer appendData:[data subdataWithRange:NSMakeRange(0, [data length])]];
                NSLog(@"Total Data Length is %lu", (unsigned long)[imageBuffer length]);
                self.imageView.image = [UIImage imageWithData: imageBuffer];

            }
        });
    }
    
}
    
- (IBAction)onSegmentedControlClicked:(UISegmentedControl*)sender {
    NSInteger selectedSegment = sender.selectedSegmentIndex;
    
    if (selectedSegment == 1) {
             [socket writeData:[[NSString stringWithFormat:@"NEXT_SLIDE"] dataUsingEncoding:NSUTF8StringEncoding] withTimeout:-1 tag:TAG_REQUEST_NEXT_SLIDE];
    }
    else  if (selectedSegment == 0) {
        [socket writeData:[[NSString stringWithFormat:@"PREVIOUS_SLIDE"] dataUsingEncoding:NSUTF8StringEncoding] withTimeout:-1 tag:TAG_REQUEST_PREVIOUS_SLIDE];

    }
}

- (IBAction)onSegmentedZoomClicked:(UISegmentedControl*)sender {
    NSInteger selectedSegment = sender.selectedSegmentIndex;
    
    if (selectedSegment == 1) {
        [socket writeData:[[NSString stringWithFormat:@"MAXIMIZE"] dataUsingEncoding:NSUTF8StringEncoding] withTimeout:-1 tag:TAG_REQUEST_MAXIMIZE];
    }
    else  if (selectedSegment == 0) {
        [socket writeData:[[NSString stringWithFormat:@"MINIMIZE"] dataUsingEncoding:NSUTF8StringEncoding] withTimeout:-1 tag:TAG_REQUEST_MINIMIZE];
        
    }
}


@end
