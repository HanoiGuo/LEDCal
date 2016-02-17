//
//  AlgorithmOB3N.h
//  LED Calibration
//
//  Created by Hanoi on 16/2/17.
//  Copyright (c) 2016年 Tony. All rights reserved.
//

#ifndef LED_Calibration_AlgorithmOB3N_h
#define LED_Calibration_AlgorithmOB3N_h
#include <string>
#include <stdio.h>
#include <fstream>
#include <cv.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

#define PATH_LEN                256
#define SPEC_CONFGI_FILE        "/LedStationOB3N/SpecConfig.txt"

typedef struct _SPECCONFIG
{
    //Right LED
    int iBestPWMRightLow;
    int iBestPWMRightHigh;
    double dRightFinialBrightnessLow;
    double dRightFinialBrightnessHigh;
    double dRightUniformityLow;
    double dRightUniformityHigh;
    
    //Left LED
    int iBestPWMLeftLow;
    int iBestPWMLeftHigh;
    double dLeftFinialBrightnessLow;
    double dLeftFinialBrightnessLowHigh;
    double dLeftUniformityLow;
    double dLeftUniformityHigh;
}SpecConfig;


/********************************************************
 全局变量
 ********************************************************/


/********************************************************
 读取规格值的上下限，并在界面显示
 ********************************************************/
bool ReadSpecConfigFile(SpecConfig &referenceSpecConfig);






bool ReadSpecConfigFile(SpecConfig &referenceSpecConfig)
{
    char filePath[PATH_LEN] = {0};
    strcpy(filePath, SPEC_CONFGI_FILE);
    fstream readFile(filePath,ios::in);
    if(readFile.is_open())
    {
        
    }
    else
    {
        return false;
    }
    readFile.close();
    return true;
}
#endif
