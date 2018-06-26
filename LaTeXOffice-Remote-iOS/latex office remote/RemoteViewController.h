//
//  RemoteViewController.h
//  LaTeX Office Remote
//
//  Created by Iván Martínez Mateu on 6/8/15.
//  Copyright (c) 2015 Segoware. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GCDAsyncSocket.h"

@interface RemoteViewController : UIViewController <GCDAsyncSocketDelegate, UIGestureRecognizerDelegate>
{
    GCDAsyncSocket* socket;
    NSString* serverAddress;
    NSString* pinCode;
}

-(void) setServerAddress:(NSString*) address;
-(NSString*) getServerAddress;
-(void) setPin:(NSString*) code;
-(NSString*) getPin;
@property (weak, nonatomic) IBOutlet UIImageView *imageView;

@end

