#ifndef _E_SPO2PAGE_H
#define _E_SPO2PAGE_H

#ifdef __cplusplus
extern "C" {
#endif

extern lv_obj_t* Menu_SPO2Page;
extern lv_obj_t* SPO2page_icon_SPO2; 
extern lv_obj_t* SPO2page_SPO2Num_Label;  //值
extern lv_obj_t* SPO2page_NumUnit_Label; //单位
extern lv_obj_t* SPO2page_Measuring_Label;  //提示

extern lv_timer_t * Menu_SPO2PageTimer; //更新值

extern page_t Menu_SPO2;

void Menu_SPO2Page_screen_init(void);
void Menu_SPO2Page_screen_deinit(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
