//
//  AppDelegate.m
//  LED Calibration
//
//  Created by Hanoi on 16/2/16.
//  Copyright (c) 2016年 Tony. All rights reserved.
//

#import "AppDelegate.h"
#import "AlgorithmOB3N.h"

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    //设置部分textfield只读模式
    _Title.editable = false;
    _LeftROITitle.editable = false;
    _RightROITitle.editable = false;
    _SNTextfield.editable = false;
    _TestTimeTextField.editable = false;
    
    
    Namearray = [NSMutableArray arrayWithObjects:@"Best PWM",@"Final Brightness",@"Uniformity",nil];
   [tableView reloadData];
}

//关闭应用程序
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}

- (void)applicationWillTerminate:(NSNotification *)aNotification
{
    // Insert code here to tear down your application
    
}


//------------------------protocol----------------------------------

//返回表格的行数
- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{
    return [Namearray count];
}
//用了下面那个函数来显示数据就用不上这个，但是协议必须要实现，所以这里返回nil
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    return nil;
}
//显示数据
- (void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    NSString *data = [Namearray objectAtIndex:row];
    NSString *identifier = [tableColumn identifier];
    if ([identifier isEqualToString:@"name"])
    {
        NSTextFieldCell *textCell = cell;
        [textCell setTitle: data];
    }

}
/*****************************************
 点击开始按钮
 *****************************************/
- (IBAction)StartToCalibrate:(id)sender
{
    
}
@end
