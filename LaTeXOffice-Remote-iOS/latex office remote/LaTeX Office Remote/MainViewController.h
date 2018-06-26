//
//  ViewController.h
//  LaTeX Office Remote
//
//  Created by Iván Martínez Mateu on 5/8/15.
//  Copyright (c) 2015 Segoware. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GCDAsyncSocket.h"
#import "RemoteViewController.h"
@interface MainViewController : UIViewController <GCDAsyncSocketDelegate>
{
    GCDAsyncSocket* socket;

}

@property (weak, nonatomic) IBOutlet UITextField *addressField;
@property (weak, nonatomic) IBOutlet UITextField *pinCodeField;

@end


