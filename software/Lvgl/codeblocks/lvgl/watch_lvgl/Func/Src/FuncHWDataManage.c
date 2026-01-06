#include "../Include/FuncHWDataManage.h"





//********************************************************************************
//                      RTC:Interface
void HW_GeT_TimeData(HW_DateTimeTypeDef* nowdatetime)
{
    #if HW_USE_RTC
		if (nowdatetime != NULL)
		{
            RTC_DateTypeDef nowdate;
            RTC_TimeTypeDef nowtime;
			HAL_RTC_GetTime(&hrtc, &nowtime, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, &nowdate, RTC_FORMAT_BIN);
            nowdatetime->Year = nowdate.Year;
            nowdatetime->Month = nowdate.Month;
            nowdatetime->Date = nowdate.Date;
			nowdatetime->WeekDay = weekday_cluculate(nowdatetime->Year, nowdatetime->Month, nowdatetime->Date, 20);
            nowdatetime->Hours = nowtime.Hours;
            nowdatetime->Minutes = nowtime.Minutes;
            nowdatetime->Seconds = nowtime.Seconds;
		}
	#else
		nowdatetime->Year = 25;
		nowdatetime->Month = 4;
		nowdatetime->Date = 9;
		nowdatetime->WeekDay = 3;
		nowdatetime->Hours =16;
		nowdatetime->Minutes = 00;
		nowdatetime->Seconds = 00;
	#endif
}


/**
 * @brief  设置日期
 * @note   
 * @param  year: 
 * @param  month: 
 * @param  date: 
 * @retval None
 */
void HW_Set_Date(uint8_t year, uint8_t month, uint8_t date)
{
	#if HW_USE_RTC
		RTC_SetDate(year, month, date);
	#endif
}

/**
 * @brief  设置具体时间：小时、分钟、秒
 * @note   
 * @param  hours: 
 * @param  minutes: 
 * @param  seconds: 
 * @retval None
 */
void HW_Set_Time(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	#if HW_USE_RTC
		RTC_SetTime(hours, minutes, seconds);
	#endif
}
/**
 * @brief  计算周几
 * @note   
 * @param  setyear: 
 * @param  setmonth: 
 * @param  setday: 
 * @param  century: 
 * @retval 
 */
uint8_t HW_Calculate_WeekDay(uint8_t setyear, uint8_t setmonth, uint8_t setday, uint8_t century)
{
    int w;
	if (setmonth == 1 || setmonth == 2)
	{setyear--, setmonth += 12;}
	w = setyear + setyear / 4 + century / 4  + 26*(setmonth + 1)/10 + setday - 1 - 2 * century;
	while(w<0)
		w+=7;
	w%=7;
	w=(w==0)?7:w;
	return w;
}


//********************************************************************************
//                      LCD:Interface
/**
 * @brief  设置屏幕亮度
 * @note   
 * @param  light: 0-100
 * @retval None
 */
void HW_LCD_Set_Light(uint8_t light)
{
#if HW_USE_LCD
    LCD_Set_Light(light);
#endif
 }
 


//********************************************************************************
//                       MPU6050:Interface
/**
 * @brief  mpu6050_dmp初始化
 * @note   
 * @retval 0:正常；其它：错误
 */
uint8_t HW_MPU6050_Init(void)
 {
#if HW_USE_IMU
    return mpu_dmp_init();
#endif
 }

/**
 * @brief  翻腕亮屏使能
 * @note   
 * @retval None
 */
void HW_MPU6050_Wrist_Enable(void)
{
#if HW_USE_IMU
    HWInterface.Motion.wrist_is_enabled = 1;
#endif
}

/**
 * @brief  翻腕亮屏禁用
 * @note   
 * @retval None
 */
void HW_MPU6050_Wrist_Disable(void)
{
#if HW_USE_IMU
    HWInterface.Motion.wrist_is_enabled = 0;
#endif
 }

/**
 * @brief  得到步数
 * @note   
 * @retval 
 */
 uint32_t HW_MPU6050_Get_Steps(void)
 {
     #if HW_USE_IMU
         unsigned long STEPS = 0;
         if(!HWInterface.Motion.ConnectionError)
             dmp_get_pedometer_step_count(&STEPS);
         return (uint32_t)STEPS;
     #endif
         return 0;
 }
 
/**
 * @brief  设置步数
 * @note   
 * @param  count: 
 * @retval 
 */
 int HW_MPU6050_Set_Steps(unsigned long count)
 {
     #if HW_USE_IMU
         if(!HWInterface.Motion.ConnectionError)
             return dmp_set_pedometer_step_count(count);
     #endif
         return -1;
 }



//********************************************************************************
//                       AHT21:Interface
 uint8_t HW_AHT21_Init(void)
 {
#if HW_USE_AHT21
     return AHT21_Init();
#endif  
 }

/**
 * @brief  计算温湿度，存储在自身结构体中
 * @note   
 * @retval ERROR or SUCCESS
 */
unsigned char HW_AHT21_Get_Humi_Temp(void)
{
    float humi;
    float temp;
#if HW_USE_AHT21
	//temp and humi messure
    if (!HWInterface.AHT21.ConnectionError)
    {
        AHT21_Read(&humi, &temp);
        HWInterface.AHT21.temperature = (uint8_t)temp;
        HWInterface.AHT21.humidity = (uint8_t)humi;
        return SUCCESS;
    }
    return ERROR;
#endif
}



//********************************************************************************
//                       SPL06:Interface
uint8_t HW_Barometer_Init(void)
{
	#if HW_USE_Pressure
		return SPL_init();
	#endif

	return -1;
}

/**
 * @brief  计算海拔
 * @note   存储在自身结构体中：HWInterface.Barometer.altitude
 * @retval  
 */
void HW_Barometer_Get_Altitude(void)
{
	#if HW_USE_Pressure
        HWInterface.Barometer.altitude = Altitude_Calculate();
	#endif

}



void HW_Barometer_Sleep(void)
{
#if HW_USE_Pressure
    if (HWInterface.Barometer.is_Sleep == 1)
        SPL_Sleep();
#endif
}

void HW_Barometer_Wakeup(void)
{
#if HW_USE_Pressure
    if (HWInterface.Barometer.is_Sleep == 0)
        SPL_Wakeup();
#endif
}


//********************************************************************************
//                       LSM303:Interface
uint8_t HW_Ecompass_Init(void)
{
	#if HW_USE_Compass
		return LSM303DLH_Init();
	#endif

	return -1;
}

void HW_Ecompass_Sleep(void)
{
#if HW_USE_Compass
    if(HWInterface.Ecompass.is_sleep == 1)
        LSM303DLH_Sleep();
#endif
}

void HW_Ecompass_Wakeup(void)
{
#if HW_USE_Compass
    if(HWInterface.Ecompass.is_sleep == 0)
        LSM303DLH_Wakeup();
#endif
}
/**
 * @brief  计算方位：0-360
 * @note   计算得到的数据会存在HWInterface.Ecompass.direction
 * @retval 
 */
void HW_Ecompass_Calculation_Direction(void)
{
#if HW_USE_Compass
    LSM303_Read_Acceleration(&HWInterface.Ecompass.Ecompass_XYZ.Xa,
        &HWInterface.Ecompass.Ecompass_XYZ.Ya,
        &HWInterface.Ecompass.Ecompass_XYZ.Za);
    
    LSM303_Read_Magnetic(&HWInterface.Ecompass.Ecompass_XYZ.Xm,
        &HWInterface.Ecompass.Ecompass_XYZ.Ym,
        &HWInterface.Ecompass.Ecompass_XYZ.Zm);
    
    HWInterface.Ecompass.direction =
        (int)Azimuth_Calculate(HWInterface.Ecompass.Ecompass_XYZ.Xa,
            HWInterface.Ecompass.Ecompass_XYZ.Ya,
            HWInterface.Ecompass.Ecompass_XYZ.Za,
            HWInterface.Ecompass.Ecompass_XYZ.Xm,
            HWInterface.Ecompass.Ecompass_XYZ.Ym,
        HWInterface.Ecompass.Ecompass_XYZ.Zm);

    if (HWInterface.Ecompass.direction < 0) {  //0-360
        HWInterface.Ecompass.direction += 360;
	}
#endif
        
}
//********************************************************************************
//                       MAX30102(血氧、心率):Interface
void HW_HeartBlood_Init(void)
{
#if HW_USE_HeartRate
    Heart_SpO2_Init();
#endif
}

unsigned char HW_HeartBlood_Sleep(void)
{
#if HW_USE_HeartRate
    return Heart_SpO2_Sleep();
#endif
}


unsigned char HW_HeartBlood_Wakeup(void)
{
#if HW_USE_HeartRate
    return Heart_SpO2_Wakeup();
#endif
}

void HW_HeartBlood_Calculator(void)
{
#if HW_USE_HeartRate
    Heart_SpO2_Get(&HWInterface.HR_meter.HeartRate,&HWInterface.HR_meter.SPO2);
#endif
}

//********************************************************************************
HW_InterfaceTypeDef HWInterface = {
    .RealTimeClock = {
        .GetTimeDate = HW_GeT_TimeData,
        .SetDate = HW_Set_Date,
        .SetTime = HW_Set_Time,
        .CalculateWeekday = HW_Calculate_WeekDay,
    },
    .LCD = {
        .SetLight = HW_LCD_Set_Light,
    },
    .Motion =  //运动状态
    {
        .ConnectionError = 1,
        .Steps = 0,
        .wrist_is_enabled = 0,
        .wrist_state = WRIST_UP,
        .Init = HW_MPU6050_Init,
        .WristEnable = HW_MPU6050_Wrist_Enable,
        .WristDisable = HW_MPU6050_Wrist_Disable,
        .GetSteps = HW_MPU6050_Get_Steps,
        .SetSteps = HW_MPU6050_Set_Steps,
    },
    .AHT21 =  //温湿度
    {
        .ConnectionError = 1,
        .humidity = 0,
        .temperature = 0,
        .Init = HW_AHT21_Init,
        .GetHumiTemp = HW_AHT21_Get_Humi_Temp,
    },
    .Barometer =  //海拔、气压
    {
        .ConnectionError = 1,
        .altitude = 0,
        .is_Sleep = 0,  //默认不休眠
        .Init = HW_Barometer_Init,
        .Altitude_Calculate = HW_Barometer_Get_Altitude,
        .Barometer_Sleep = HW_Barometer_Sleep,
        .Barometer_Wakeup = HW_Barometer_Wakeup,
    },
    .Ecompass = { //指南针
        .ConnectionError = 1,
        .direction = 0,
        .is_sleep = 0,
        .Init = HW_Ecompass_Init,
        .Sleep = HW_Ecompass_Sleep,
        .Wakeup = HW_Ecompass_Wakeup,
        .Calculator_Direction = HW_Ecompass_Calculation_Direction,  //方位计算
    },
    .HR_meter = {
        .ConnectionError = 1,
        .HeartRate = 0,  //心率
        .SPO2 = 0,  //血氧
        .is_sleep = 0,
        .Init = HW_HeartBlood_Init,
        .Sleep = HW_HeartBlood_Sleep,
        .Wakeup = HW_HeartBlood_Wakeup,
        .HBCalculator = HW_HeartBlood_Calculator,  //心率血氧计算
    }
};