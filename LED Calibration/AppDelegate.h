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
}

@property (strong) IBOutlet NSTextField *Title;
@property (strong) IBOutlet NSTextField *LeftROITitle;
@property (strong) IBOutlet NSTextField *RightROITitle;

@property (strong) IBOutlet NSImageView *LeftImageROI;
@property (strong) IBOutlet NSImageView *RightImageROI;
@property (strong) IBOutlet NSTextField *ResultLabel;

- (IBAction)StartToCalibrate:(id)sender;
@end

