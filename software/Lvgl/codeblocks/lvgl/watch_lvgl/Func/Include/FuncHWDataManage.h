
#ifndef HWDATAACCESS_H
#define HWDATAACCESS_H

#ifdef __cplusplus
extern "C" {
#endif


#define HW_USE_HARDWARE 0

#if HW_USE_HARDWARE
#define HW_USE_RTC               1
#define HW_USE_LCD               1
#define HW_USE_IMU               1  //Mpu6050
#define HW_USE_AHT21             1
#define HW_USE_Pressure          1  //SPL06
#define HW_USE_Compass           1  //lsm303
#define HW_USE_HeartRate         1  //MAX30102
#endif



#include "stdint.h"
#include <stdbool.h>

#if HW_USE_RTC
#include "rtc.h"
#endif

#if HW_USE_LCD
#include "init.h"
#endif

#if HW_USE_IMU
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#endif

#if HW_USE_AHT21
#include "AHT21.h"
#endif

#if HW_USE_Pressure
#include "SPL06.h"
#endif

#if HW_USE_Compass
#include "LSM303.h"
#endif

#if HW_USE_HeartRate
#include "HR_Heart_SpO2.h"
#endif


//日历
typedef struct
{
    uint8_t WeekDay;    /*!< Specifies the RTC Date WeekDay.
                            This parameter can be a value of @ref RTC_WeekDay_Definitions */

    uint8_t Month;      /*!< Specifies the RTC Date Month (in BCD format).
                            This parameter can be a value of @ref RTC_Month_Date_Definitions */

    uint8_t Date;       /*!< Specifies the RTC Date.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 31 */

    uint8_t Year;       /*!< Specifies the RTC Date Year.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 99 */

    uint8_t Hours;      /*!< Specifies the RTC Time Hour.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 12 if the RTC_HourFormat_12 is selected
                            This parameter must be a number between Min_Data = 0 and Max_Data = 23 if the RTC_HourFormat_24 is selected */

    uint8_t Minutes;    /*!< Specifies the RTC Time Minutes.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 59 */

    uint8_t Seconds;    /*!< Specifies the RTC Time Seconds.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 59 */

} HW_DateTimeTypeDef;

/**
 * @brief  RTC时钟接口包装，用于计算时间和实现日历
 * @note
 * @retval None
 */
typedef struct
{
    void (*GetTimeDate)(HW_DateTimeTypeDef *nowdatetime);
    void (*SetDate)(uint8_t year, uint8_t month, uint8_t date);
    void (*SetTime)(uint8_t hours, uint8_t minutes, uint8_t seconds);
    uint8_t (*CalculateWeekday)(uint8_t setyear, uint8_t setmonth, uint8_t setday, uint8_t century);
} HW_RTC_InterfaceTypeDef;


 /**
  * @brief  LCD接口包装 -- 屏幕亮度设置
  * @note
  * @retval None
  */
 typedef struct
 {
     void (*SetLight)(uint8_t dc);
 } HW_LCD_InterfaceTypeDef;


 /**
   * @brief  腕部状态定义
   */
 #define WRIST_UP 1
 #define WRIST_DOWN 0

/**
 * @brief  MPU6050接口包装 -- 手腕状态：翻腕亮屏、步数
 * @note
 * @retval None
 */
 typedef struct
 {
     uint8_t ConnectionError;
     uint32_t Steps;
     uint8_t wrist_state;
     uint8_t wrist_is_enabled;

     uint8_t (*Init)(void);
     void (*WristEnable)(void);
     void (*WristDisable)(void);
     uint32_t (*GetSteps)(void);
     int (*SetSteps)(unsigned long count);
 } HW_MPU_InterfaceTypeDef;  //IMU


/**
 * @brief  AHT21温湿度接口包装
 * @note
 * @retval None
 */
 typedef struct
 {
    uint8_t ConnectionError;
    uint8_t temperature;  //温度
    uint8_t humidity;  //湿度
    uint8_t(*Init)(void);  //初始化
    unsigned char (*GetHumiTemp)(void);  //获取数据

 } HW_AHT21_InterfaceTypeDef;


 /**
  * @brief  SPL06接口包装 -- 气压、海拔
  * @note
  * @retval None
  */
 typedef struct
 {
   uint8_t ConnectionError;  //出错标识
   uint16_t altitude;  //海拔
   uint8_t is_Sleep; //是否休眠：1，休眠；0，唤醒

   uint8_t (*Init)(void);
   void (*Altitude_Calculate)(void);
   void (*Barometer_Sleep)(void);
   void (*Barometer_Wakeup)(void);
 } HW_Barometer_InterfaceTypeDef;


 /**
  * @brief  LSM303模块类化 -- 指南针
  * @note
  * @retval None
  */
struct XYZ
{
  int16_t Xa, Ya, Za, Xm, Ym, Zm
}; //各轴的加速度和受到的磁力强度

typedef struct
 {
    uint8_t ConnectionError;
    int direction;//计算到的角度
    struct XYZ Ecompass_XYZ; //用于计算方向时用到

    uint8_t is_sleep;

    uint8_t(*Init)(void);
    void (*Sleep)(void);
    void (*Wakeup)(void);
    void (*Calculator_Direction)(void);

 } HW_Ecompass_InterfaceTypeDef;

 /**
   * @brief  HW EM7028 heart rate meter Interface definition
   */
/**
 * @brief  MAX30102模块类化：心率、血氧
 * @note
 * @retval None
 */
 typedef struct
 {
    uint8_t ConnectionError;
    uint8_t HeartRate;
    uint8_t SPO2;

    uint8_t is_sleep;

    void (*Init)(void);
    void (*Sleep)(void);
    void (*Wakeup)(void);
    void (*HBCalculator)(void);
 } HW_HeartBlood_InterfaceTypeDef;

 /**
   * @brief  Hardware Interface structure definition
   */
 typedef struct
 {
     HW_RTC_InterfaceTypeDef RealTimeClock;
     HW_LCD_InterfaceTypeDef LCD; //屏幕
     HW_MPU_InterfaceTypeDef Motion;  //动作：翻腕、步数
     HW_AHT21_InterfaceTypeDef AHT21;  //温度湿度
     HW_Barometer_InterfaceTypeDef Barometer;  //气压、海拔
     HW_Ecompass_InterfaceTypeDef Ecompass; //指南针
     HW_HeartBlood_InterfaceTypeDef HR_meter; //血氧、心率
 } HW_InterfaceTypeDef;



 /***************************
  *  PROTOTYPES
  ***************************/


 /***************************
  *  External Variables
  ***************************/
 extern HW_InterfaceTypeDef HWInterface;



 #ifdef __cplusplus
 } /*extern "C"*/
 #endif





#endif
