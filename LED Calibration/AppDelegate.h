//
//  AppDelegate.h
//  LED Calibration
//
//  Created by Hanoi on 16/2/16.
//  Copyright (c) 2016年 Tony. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    
    IBOutlet NSTableView *tableView;
    NSMutableArray *Namearray;
    NSMutableArray *RightLEDarray;
    NSMutableArray *LeftLEDarray;
    NSMutableArray *RightSpecLow;
    NSMutableArray *RightSpecHigh;
    NSMutableArray *LeftSpecLow;
    NSMutableArray *LeftSpecHigh;
    
    NSTimer *TestTimeTimer;
    NSTimer *UpdateUITimer;
}

@property (strong) IBOutlet NSTextField *Title;
@property (strong) IBOutlet NSTextField *LeftROITitle;
@property (strong) IBOutlet NSTextField *RightROITitle;

@property (strong) IBOutlet NSImageView *LeftImageROI;
@property (strong) IBOutlet NSImageView *RightImageROI;
@property (strong) IBOutlet NSTextField *ResultLabel;
@property (strong) IBOutlet NSTextField *SNTextfield;
@property (strong) IBOutlet NSTextField *TestTimeTextField;
@property (strong) IBOutlet NSButton *StartButton;



- (IBAction)StartToCalibrate:(id)sender;
@end

