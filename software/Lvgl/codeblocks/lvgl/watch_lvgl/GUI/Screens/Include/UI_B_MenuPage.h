#ifndef _B_MENUPAGE_H
#define _B_MENUPAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../ui.h"
extern page_t Page_Menu;

extern lv_obj_t* ui_MenuPage;

//日历列
extern lv_obj_t* Menu_Calendar_Row; //建立在ui_MenuPage上的显示对象 -- 日历
extern lv_obj_t* Menu_Calendar_IconContain;//日历图标容器
extern lv_obj_t* Menu_Calendar_IconLabel;  //日历图标
extern lv_obj_t* Menu_Calendar_TextLabel; //日历文本


//心率列
extern lv_obj_t* Menu_HeartRate_Row; //心率列容器
extern lv_obj_t* Menu_HeartRate_IconContain;//心率图标容器
extern lv_obj_t* Menu_HeartRate_IconLabel; //心率图标
extern lv_obj_t* Menu_HeartRate_TextLabel; //文本

//血氧列
extern lv_obj_t* Menu_SpO2_Row; //心氧列容器
extern lv_obj_t* Menu_SpO2_IconContain;
extern lv_obj_t* Menu_SpO2_IconLabel; //心氧图标
extern lv_obj_t* Menu_SpO2_TextLabel; //文本

//计算器
extern lv_obj_t* Menu_Calculator_Row;
extern lv_obj_t* Menu_Calculator_IconContain;
extern lv_obj_t* Menu_Calculator_IconLabel;
extern lv_obj_t* Menu_Calculator_TextLabel; 

//计时器
extern lv_obj_t* Menu_Timer_Row;
extern lv_obj_t* Menu_Timer_IconContain;
extern lv_obj_t* Menu_Timer_IconLabel;
extern lv_obj_t* Menu_Timer_TextLabel;

//指南针
extern lv_obj_t* Menu_Compass_Row;
extern lv_obj_t* Menu_Compass_IconContain;
extern lv_obj_t* Menu_Compass_IconLabel;
extern lv_obj_t* Menu_Compass_TextLabel;

//卡包
extern lv_obj_t* Menu_nfcCard_Row;
extern lv_obj_t* Menu_nfcCard_IconContain;
extern lv_obj_t* Menu_nfcCard_IconLabel;
extern lv_obj_t* Menu_nfcCard_TextLabel;


//环境：温湿度
extern lv_obj_t* Menu_Environment_Row;
extern lv_obj_t* Menu_Environment_IconContain;
extern lv_obj_t* Menu_Environment_IconLabel;
extern lv_obj_t* Menu_Environment_TextLabel;


//游戏
extern lv_obj_t* Menu_Game_Row;
extern lv_obj_t* Menu_Game_IconContain;
extern lv_obj_t* Menu_Game_IconLabel;
extern lv_obj_t* Menu_Game_TextLabel;

//运动
extern lv_obj_t* Menu_Motion_Row;
extern lv_obj_t* Menu_Motion_IconContain;
extern lv_obj_t* Menu_Motion_IconLabel;
extern lv_obj_t* Menu_Motion_TextLabel;

//设置
extern lv_obj_t* Menu_Setting_Row;
extern lv_obj_t* Menu_Setting_IconContain;
extern lv_obj_t* Menu_Setting_IconLabel;
extern lv_obj_t* Menu_Setting_TextLabel;

extern int16_t ui_MenuScrollY;

void ui_MenuPage_screen_init(void);
void ui_MenuPage_screen_deinit(void);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif