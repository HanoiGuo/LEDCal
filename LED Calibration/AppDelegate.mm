//
//  AppDelegate.m
//  LED Calibration
//
//  Created by Hanoi on 16/2/16.
//  Copyright (c) 2016年 Tony. All rights reserved.
//

#import "AppDelegate.h"
#import "AlgorithmOB3N.h"
#import <pthread.h>

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

NSString *LEDdriverPath;


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
    
    //load spec config data
    if(ReadSpecConfigFile(specData))
    {
        //right led spec
        NSString *RightbestpwmLow = [NSString stringWithFormat:@"%d",specData.iBestPWMRightLow];
        NSString *RightbestpwmHigh = [NSString stringWithFormat:@"%d",specData.iBestPWMRightHigh];
        NSString *RigihtFinialLumLow = [NSString stringWithFormat:@"%.1f",specData.dRightFinialBrightnessLow];
        NSString *RightFinialLumHigh = [NSString stringWithFormat:@"%.1f",specData.dRightFinialBrightnessHigh];
        NSString *RightUniformityLow = [NSString stringWithFormat:@"%.1f",specData.dRightUniformityLow];
        NSString *RightUniformityHigh = [NSString stringWithFormat:@"%.1f",specData.dRightUniformityHigh];
        
        //left led spec
        NSString *LeftbestpwmLow = [NSString stringWithFormat:@"%d",specData.iBestPWMLeftLow];
        NSString *LeftbestpwmHigh = [NSString stringWithFormat:@"%d",specData.iBestPWMLeftHigh];
        NSString *LeftFinialLumLow = [NSString stringWithFormat:@"%.1f",specData.dLeftFinialBrightnessLow];
        NSString *LeftFinialLumHigh = [NSString stringWithFormat:@"%.1f",specData.dLeftFinialBrightnessLowHigh];
        NSString *LeftUniformityLow = [NSString stringWithFormat:@"%.1f",specData.dLeftUniformityLow];
        NSString *LeftUniformityHigh = [NSString stringWithFormat:@"%.1f",specData.dLeftUniformityHigh];
        
        RightSpecLow = [NSMutableArray arrayWithObjects:RightbestpwmLow,RigihtFinialLumLow,RightUniformityLow,nil];
        RightSpecHigh = [NSMutableArray arrayWithObjects:RightbestpwmHigh,RightFinialLumHigh,RightUniformityHigh, nil];
        LeftSpecLow = [NSMutableArray arrayWithObjects:LeftbestpwmLow,LeftFinialLumLow,LeftUniformityLow,nil];
        LeftSpecHigh = [NSMutableArray arrayWithObjects:LeftbestpwmHigh,LeftFinialLumHigh,LeftUniformityHigh, nil];
        RightLEDarray = [NSMutableArray arrayWithObjects:@"nil",@"nil",@"nil",nil];
        LeftLEDarray = [NSMutableArray arrayWithObjects:@"nil",@"nil",@"nil",nil];
    }
    else
    {
        [_ResultLabel setStringValue:@"Load spec config fail(更新规格配置文件失败)\n"];
        _ResultLabel.backgroundColor = [NSColor redColor];
        _StartButton.enabled = false;
    }
    
    if(!ReadConfigSettingFile(GlobalConfigSetting))
    {
        [_ResultLabel setStringValue:@"Load config setting fail(更新配置文件失败)\n"];
        _ResultLabel.backgroundColor = [NSColor redColor];
        _StartButton.enabled = false;
    }
    
    
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
//更新table的数据
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    NSString *identifier = [tableColumn identifier];
    if ([identifier isEqualToString:@"name"])
    {
        return [Namearray objectAtIndex:row];
    }
    else if([identifier isEqualToString:@"RightLow"])
    {
        return [RightSpecLow objectAtIndex:row];
    }
    else if([identifier isEqualToString:@"RightHigh"])
    {
        return [RightSpecLow objectAtIndex:row];
    }
    else if([identifier isEqualToString:@"LeftLow"])
    {
        return [LeftSpecLow objectAtIndex:row];
    }
    else if([identifier isEqualToString:@"LeftHigh"])
    {
        return [LeftSpecHigh objectAtIndex:row];
    }
    else if([identifier isEqualToString:@"RightMeasure"])
    {
        return [RightLEDarray objectAtIndex:row];
    }
    else if([identifier isEqualToString:@"RightMeasure"])
    {
        return [RightLEDarray objectAtIndex:row];
    }
    else if([identifier isEqualToString:@"LeftMeasure"])
    {
        return [LeftLEDarray objectAtIndex:row];
    }
    
    return nil;
}

void *ThreadFunction(void *arg)
{
    while(1)
    {
        if(bIsTestFinish)
        {
            sleep(1);
            continue;
        }
        iFunctionReturnValue = LedTruingFunction(GlobalMeasureData,LEDdriverPath.UTF8String);
        bIsTestFinish = true;
    }
    return 0;
}

/*****************************************
 测试时间的timer
 *****************************************/
-(void)UpdateUI
{
    if (!bIsTestFinish)
    {
        return;
    }
    
    NSString *RightBestPWM;
    if(GlobalMeasureData.iRightBestPWM == INVALID_VALUE)
    {
          RightBestPWM = @"NULL";
    }
    else
    {
        RightBestPWM = [NSString stringWithFormat:@"%d",GlobalMeasureData.iRightBestPWM];
    }
   
    NSString *RightFinialBrightness;
    if(GlobalMeasureData.dRightFinialBrightness == INVALID_VALUE)
    {
        RightFinialBrightness = @"NULL";
    }
    else
    {
       RightFinialBrightness = [NSString stringWithFormat:@"%.3f",GlobalMeasureData.dRightFinialBrightness];
    }
    
    NSString *RightUniformity;
    if(GlobalMeasureData.dRightUniformity == INVALID_VALUE)
    {
        RightUniformity = @"NULL";
    }
    else
    {
        RightUniformity = [NSString stringWithFormat:@"%.3f",GlobalMeasureData.dRightUniformity];
    }
    
    NSString *LeftBestPWM;
    if(GlobalMeasureData.iLeftBestPWM == INVALID_VALUE)
    {
        LeftBestPWM = @"NULL";
    }
    else
    {
        LeftBestPWM = [NSString stringWithFormat:@"%d",GlobalMeasureData.iLeftBestPWM];
    }
    
    NSString *LeftFinialBrightness;
    if(GlobalMeasureData.dLeftFinialBrightness == INVALID_VALUE)
    {
        LeftFinialBrightness = @"NULL";
    }
    else
    {
       LeftFinialBrightness = [NSString stringWithFormat:@"%.3f",GlobalMeasureData.dLeftFinialBrightness];
    }
    
    NSString *LeftUniformity;
    if(GlobalMeasureData.dLeftUniformity == INVALID_VALUE)
    {
        LeftUniformity = @"NULL";
    }
    else
    {
        LeftUniformity = [NSString stringWithFormat:@"%.3f",GlobalMeasureData.dLeftUniformity];
    }
    
    RightLEDarray = [NSMutableArray arrayWithObjects:RightBestPWM,RightFinialBrightness,RightUniformity, nil];
    LeftLEDarray = [NSMutableArray arrayWithObjects:LeftBestPWM,LeftFinialBrightness,LeftUniformity,nil];
    [tableView reloadData];
    switch (iFunctionReturnValue)
    {
        case Rrturn_OK:
            _ResultLabel.backgroundColor = [NSColor greenColor];
            [_ResultLabel setStringValue:@"Test ok (测试完毕)"];
            break;
            
        default:
            break;
    }
    _StartButton.enabled = true;
}


/*****************************************
 测试时间的timer
 *****************************************/
-(void)changeTimeAtTimedisplay
{
    if(bIsTestFinish)
    {
        return;
    }
    iTotalTestTime += 1;
    NSString *time = [NSString stringWithFormat:@"%d",iTotalTestTime];
    [_TestTimeTextField setStringValue:time];
}

/*****************************************
 点击开始按钮
 *****************************************/
- (IBAction)StartToCalibrate:(id)sender
{
    _StartButton.enabled = false;
    bIsTestFinish = false;  //没点击一次按钮，测试就从头开始
    iTotalTestTime = 0;
    if(!TestTimeTimer)
    {
        //创建测试时间的timer
        TestTimeTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(changeTimeAtTimedisplay)  userInfo:nil repeats:YES];
        
        UpdateUITimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(UpdateUI) userInfo:nil repeats:YES];
        
        //创建线程
        pthread_t tid;
        pthread_create(&tid, NULL,ThreadFunction,NULL);
    }
}

@end
