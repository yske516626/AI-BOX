#ifndef _A_HOMEPAGE_H
#define _A_HOMEPAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../ui.h"

extern page_t Page_Home;
extern page_t Page_power;

//////////////////////////////////////////////////////////////////////////
//home page definition
extern lv_obj_t* ui_HomePage;
extern lv_obj_t* ui_PowerPage;

//Temperature_design:
extern lv_obj_t* Home_Temp_Contain;  //主：温度设计容纳
extern lv_style_t style_Temp;

extern lv_obj_t* Day_Or_Night;  //次1：白天 or 夜晚容纳
extern lv_style_t style_Day_Or_Night; //次1样式
extern lv_obj_t* DayNight_Label;  //次1-1：白天 or 夜晚标签图标显示

extern lv_obj_t* Tem_Num_Label;  // 次2：温度数值显示
extern lv_obj_t* Celsius_Label; // 次2：摄氏度图标显示

extern uint8_t ui_TempValue; //温度数值

//////////////////////////////////////////////////////////////////////////
//Time definition
extern lv_obj_t* Home_Time_Contain;  //主：时间设计容纳
extern lv_style_t style_Time;

extern lv_obj_t* ui_TimeHourLabel;   //小时标签
extern lv_obj_t * ui_TimeColonLabel;  //小时和分钟中间间隔符号
extern lv_obj_t * ui_TimeMinuteLabel; //分钟标签

extern lv_timer_t* ui_HomePageTimer;  //用于更新时间值

//Time definition num：
extern uint8_t ui_TimeHourValue;
extern uint8_t ui_TimeMinuteValue;
extern const char * ui_Days[7];
extern uint8_t ui_DateMonthValue;
extern uint8_t ui_DateDayValue;
extern uint8_t ui_DataWeekdayValue;


////////////////////////////////////////////////////////////ee//////////////
//Date definition
extern lv_obj_t* Home_Date_Contain;
extern lv_style_t style_Date;

extern lv_obj_t* Date_icon_Label;
extern lv_obj_t* Date_Num_Label;



//////////////////////////////////////////////////////////////////////////
//Heart Rate Definition
extern lv_obj_t* Home_HeartRate_Contain;
extern lv_style_t style_HeartRate;

extern lv_obj_t* HeartRate_icon_Label; //心型图标
extern lv_obj_t* HeartRate_Num_Label;  //心率显示

extern uint8_t ui_HeartRate_Num;  //心率值存储

//////////////////////////////////////////////////////////////////////////
//步数设计
extern lv_obj_t* Home_Foots_Contain;
extern lv_style_t style_Foots;

extern lv_obj_t* Home_Foots_icon_Contain; //建立在Home_Foots_Contain上
extern lv_style_t style_Foots_icon_Contain;

extern lv_obj_t* Foots_icon_Label; //步数图标标签
extern lv_obj_t* Foots_Num_Label;  //步数显示

extern uint32_t Foots_Num;  //步数值记录

//////////////////////////////////////////////////////////////////////////
//上滑控制中心页设计
extern lv_obj_t* Home_Setting_Contain;

extern lv_obj_t* Setting_NFCButton; 
extern lv_obj_t* NFCIcon;

extern lv_obj_t* Setting_BLEButton;
extern lv_obj_t* BLEIcon;

extern lv_obj_t* Setting_ShutdownButton;
extern lv_obj_t* ShutdownIcon;

extern lv_obj_t* Setting_SetButton;
extern lv_obj_t* SetIcon;

extern lv_obj_t* Setting_LightSlider;
extern lv_obj_t* LightIcon;

extern lv_obj_t* PowerLabel;

/***********************************variables definition****************************************************************** */

extern uint8_t ui_HomePage_NFCButton_EN; //nfc启动标志。0：不启用nfc
extern uint8_t ui_HomePage_BLEButton_EN;  //蓝牙启动标志



void ui_HomePage_screen_init(void);
void ui_HomePage_screen_deinit(void);
void ui_PowerPage_screen_init(void);
void ui_PowerPage_screen_deinit(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
