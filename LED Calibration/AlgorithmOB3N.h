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
#include <unistd.h>
using namespace std;
using namespace cv;

#define PATH_LEN                256
#define INVALID_VALUE           -1
#define SPEC_CONFGI_FILE        "/LedStationOB3N/SpecConfig.txt"
#define CONFIG_SETTING          "/LedStationOB3N/ConfigSetting.txt"

//规格结构体
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


//测试结构体
typedef struct _MEASURE_DATA
{
    //Right
    int iRightBestPWM;
    double dRightFinialBrightness;
    double dRightUniformity;
    
    
    //Left
    int iLeftBestPWM;
    double dLeftFinialBrightness;
    double dLeftUniformity;
}MeasureData;


//配置文件的结构体
typedef struct _CONFIG_FILE
{
    //camera
    int camera_exposureTime;
    
    
}ConfigSetting;


typedef enum _RETURN_VALUE
{
    Rrturn_OK = 0,
    
}_ReturnValue;

/*************************************************************************************************************/

/********************************************************
 全局变量
 ********************************************************/
SpecConfig      specData;                        //配置文件的规格
MeasureData     GlobalMeasureData;               //测试值
ConfigSetting   GlobalConfigSetting;             //配置文件
unsigned int    iTotalTestTime = 0;              //总的测试时间
unsigned int    iFunctionReturnValue = 0;        //函数的返回值
static bool     bIsTestFinish = false;           //确认测试函数是不是有跑完全




/*************************************************************************************************************/

/********************************************************
测试值结构提初始化
 ********************************************************/
void    InitialMeasureStruct(MeasureData &m_MeasureData);

/********************************************************
 读取规格值的上下限，并在界面显示
 ********************************************************/
bool    ReadSpecConfigFile(SpecConfig &referenceSpecConfig);


/********************************************************
读取配置文件
 ********************************************************/
bool    ReadConfigSettingFile(ConfigSetting &referenceConfigSetting);


/********************************************************
LED truing 的函数
 m_MeasureData  : 调试值，输出参数
 ledPortAddress : Led的地址
 
 ********************************************************/
int     LedTruingFunction(MeasureData &m_MeasureData, const char *ledDirverAddress);




/*************************************************************************************************************/

/********************************************************
 LED truing 的函数
 m_MeasureData  : 调试值，输出参数
 ledPortAddress : Led的地址
 
 ********************************************************/
int LedTruingFunction(MeasureData &m_MeasureData, const char *ledDirverAddress)
{
    //进行结构体的初始化
    InitialMeasureStruct(m_MeasureData);
    sleep(3);
    m_MeasureData.iLeftBestPWM = 30;
    return Rrturn_OK;
}

/********************************************************
 测试值结构提初始化
 ********************************************************/
void InitialMeasureStruct(MeasureData &m_MeasureData)
{
    //right
    m_MeasureData.iRightBestPWM = INVALID_VALUE;
    m_MeasureData.dRightFinialBrightness = (double)INVALID_VALUE;
    m_MeasureData.dRightUniformity = (double)INVALID_VALUE;
    
    //left
    m_MeasureData.iLeftBestPWM = INVALID_VALUE;
    m_MeasureData.dLeftFinialBrightness = (double)INVALID_VALUE;
    m_MeasureData.dLeftUniformity = (double)INVALID_VALUE;
}


/********************************************************
 读取配置文件
 ********************************************************/
bool ReadConfigSettingFile(ConfigSetting &referenceConfigSetting)
{
    char filePath[PATH_LEN] = {0};
    strcpy(filePath, CONFIG_SETTING);
    fstream readFile(filePath,ios::in);
    if(readFile.is_open())
    {
        int index = 0;
        string temp;
        string key;
        while(getline(readFile,temp))
        {
            index = (int)temp.find("=");
            if(index < 0)
            {
                continue;
            }
            key = temp.substr(0,index);
            
            //camera setting
            if( -1 != key.find("camera_exposureTime"))
            {
                referenceConfigSetting.camera_exposureTime = atoi(temp.substr(index +1).c_str());
            }
        }
    }
    else
    {
        return false;
    }
    readFile.close();
    return true;
}

/********************************************************
 读取规格值的上下限，并在界面显示
 ********************************************************/
bool ReadSpecConfigFile(SpecConfig &referenceSpecConfig)
{
    char filePath[PATH_LEN] = {0};
    strcpy(filePath, SPEC_CONFGI_FILE);
    fstream readFile(filePath,ios::in);
    if(readFile.is_open())
    {
        int index = 0;
        string temp;
        string key;
        while(getline(readFile,temp))
        {
            index = (int)temp.find("=");
            if(index < 0)
            {
                continue;
            }
            key = temp.substr(0,index);
            
            //right led
            if( -1 != key.find("iBestPWMRightLow"))
            {
                referenceSpecConfig.iBestPWMRightLow = atoi(temp.substr(index +1).c_str());
            }
            else if( -1 != key.find("iBestPWMRightHigh"))
            {
                referenceSpecConfig.iBestPWMRightHigh = atof(temp.substr(index +1).c_str());
            }
            else if( -1 != key.find("dRightFinialBrightnessLow"))
            {
                referenceSpecConfig.dRightFinialBrightnessLow = atof(temp.substr(index +1).c_str());
            }
            else if( -1 != key.find("dRightFinialBrightnessHigh"))
            {
                referenceSpecConfig.dRightFinialBrightnessHigh = atof(temp.substr(index +1).c_str());
            }
            else if( -1 != key.find("dRightUniformityLow"))
            {
                referenceSpecConfig.dRightUniformityLow = atof(temp.substr(index +1).c_str());
            }
            else if( -1 != key.find("dRightUniformityHigh"))
            {
                referenceSpecConfig.dRightUniformityHigh = atof(temp.substr(index +1).c_str());
            }
            
            //left led
            else if( -1 != key.find("iBestPWMLeftLow"))
            {
                referenceSpecConfig.iBestPWMLeftLow = atoi(temp.substr(index +1).c_str());
            }
            else if( -1 != key.find("iBestPWMLeftHigh"))
            {
                referenceSpecConfig.iBestPWMLeftHigh = atoi(temp.substr(index +1).c_str());
            }
            else if( -1 != key.find("dLeftFinialBrightnessLow"))
            {
                referenceSpecConfig.dLeftFinialBrightnessLow = atof(temp.substr(index +1).c_str());
            }
            else if( -1 != key.find("dLeftFinialBrightnessLowHigh"))
            {
                referenceSpecConfig.dLeftFinialBrightnessLowHigh = atof(temp.substr(index +1).c_str());
            }
            else if( -1 != key.find("dLeftUniformityLow"))
            {
                referenceSpecConfig.dLeftUniformityLow = atof(temp.substr(index +1).c_str());
            }
            else if( -1 != key.find("dLeftUniformityLow"))
            {
                referenceSpecConfig.dLeftUniformityLow = atof(temp.substr(index +1).c_str());
            }
        }
        
    }
    else
    {
        return false;
    }
    readFile.close();
    return true;
}

#endif
