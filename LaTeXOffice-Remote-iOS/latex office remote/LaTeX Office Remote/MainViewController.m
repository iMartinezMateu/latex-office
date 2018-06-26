//
//  ViewController.m
//  LaTeX Office Remote
//
//  Created by Iván Martínez Mateu on 5/8/15.
//  Copyright (c) 2015 Segoware. All rights reserved.
//

#import "MainViewController.h"

#define TAG_WRITE_AUTH_PIN  1
#define TAG_HELLO 100
#define TAG_REQUEST_AUTH_PIN 101
#define TAG_RESPONSE_AUTH_PIN 102

@interface MainViewController ()

@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)onConnectButtonClicked:(id)sender {
    self->socket = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];

    NSLog(@"Connecting to : %@", self.addressField.text);
    NSError *err = nil;
    if (![self->socket connectToHost:self.addressField.text onPort:17215 error:&err]) // Asynchronous!
    {
        // If there was an error, it's likely something like "already connected" or "no delegate set"
        NSLog(@"I goofed: %@", err);
    }
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [[self view] endEditing:YES];
}

- (void)socket:(GCDAsyncSocket *)sender didConnectToHost:(NSString *)host port:(UInt16)port
{
    [socket readDataWithTimeout: -1 tag:TAG_HELLO];
    [socket readDataWithTimeout: -1 tag:TAG_REQUEST_AUTH_PIN];
    [socket writeData:[[NSString stringWithFormat:@"AUTH_PIN %@",self.pinCodeField.text] dataUsingEncoding:NSUTF8StringEncoding] withTimeout:-1 tag:TAG_WRITE_AUTH_PIN];
    
    

}

- (void)socket:(GCDAsyncSocket *)sock didWriteDataWithTag:(long)tag
{
    if (tag == TAG_WRITE_AUTH_PIN)
    {
        NSLog(@"Pin code sent!");
        [socket readDataToLength:1000 withTimeout:-1 tag:TAG_RESPONSE_AUTH_PIN];
        
    }

}

- (void)socket:(GCDAsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{

    NSString* serverOutput = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];

    NSString* serverOutputTrimmed = [serverOutput stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];

  
    
    if (tag == TAG_RESPONSE_AUTH_PIN)
    {


        
        if ([serverOutputTrimmed containsString:@"BAD_PIN"] )
        {


            UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"LaTeX Office Remote"
                                                                           message:@"Pin code does not match!"
                                                                    preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *accion = [UIAlertAction actionWithTitle:@"Close"
                                                             style:UIAlertActionStyleDefault
                                                           handler:^(UIAlertAction *action) {
                                                               [alert dismissViewControllerAnimated:YES completion:nil];
                                                           }];
            [alert addAction:accion];
            
            [self presentViewController:alert animated:YES completion:nil];
            
        }
        else
        {
            RemoteViewController *vc = (RemoteViewController *)[self.storyboard instantiateViewControllerWithIdentifier:@"Remote"];
            [vc setServerAddress:self.addressField.text];
            [vc setPin:self.pinCodeField.text];
            [self.navigationController pushViewController:vc animated:YES];

        }

    }

    

    

}
- (IBAction)onAboutButtonClicked:(id)sender {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"LaTeX Office Remote"
                                                                   message:@"Remote Control Server and Client created by Iván Martínez Mateu <imm@ivanmartinezmateu.com> in order to show how a Qt/C++ desktop app can establish a communication with a mobile device (iOS) using a client app developed with Objective C. Read the guide and the articles included with this software to learn to use it properly. "
                                                            preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *accion = [UIAlertAction actionWithTitle:@"Close"
                                                     style:UIAlertActionStyleDefault
                                                   handler:^(UIAlertAction *action) {
                                                       [alert dismissViewControllerAnimated:YES completion:nil];
                                                   }];
    [alert addAction:accion];
    
    [self presentViewController:alert animated:YES completion:nil];

}

@end
