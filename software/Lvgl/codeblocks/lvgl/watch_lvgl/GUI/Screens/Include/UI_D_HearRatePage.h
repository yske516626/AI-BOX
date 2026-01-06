#ifndef _D_HRPAGE_H
#define _D_HRPAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

extern page_t Menu_HeatRate;

extern  lv_obj_t* Menu_HeatRatePage;
extern  lv_obj_t* img_heart;
extern  lv_obj_t* HRpage_HRNum_Label;  //心率值
extern  lv_obj_t* HRpage_NumUnit_Label; //单位
extern  lv_obj_t* HRpage_Measuring_Label;  //提示

extern lv_timer_t * Menu_HRPageTimer; //更新心率值

void Menu_HeartRatePage_screen_init(void);
void Menu_HeartRatePage_screen_deinit(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif