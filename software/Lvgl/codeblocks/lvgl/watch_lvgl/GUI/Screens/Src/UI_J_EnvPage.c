#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../include/UI_J_EnvPage.h"
#include "../../../Func/Include/FuncHWDataManage.h" 

/***********************************icon/img customize****************************************************************** */
#define LV_SYMBOL_Celsius   "\xEE\xBB\x82"
#define LV_SYMBOL_HUMI "\xEE\x98\x9C" 
#define LV_SYMBOL_TEM "\xEE\x98\x82"

/***********************************Page definition****************************************************************** */
page_t Menu_Env = { Menu_EnvPage_screen_init,Menu_EnvPage_screen_deinit,&Menu_EnvPage };


/***********************************obj****************************************************************** */

lv_obj_t* Menu_EnvPage;

lv_obj_t* EnvPage_TemLabel; //数值显示
lv_obj_t* EnvPage_TemUnitLabel; //温度单位显示
lv_obj_t* EnvPage_TemBar; //温度条
lv_obj_t* EnvPage_TemIcon; //图标

lv_obj_t* EnvPage_HumiLabel;  //湿度数值显示
lv_obj_t* EnvPage_HumiUnitLabel; //单位
lv_obj_t* EnvPage_HumiBar; //温度条
lv_obj_t* EnvPage_THumiIcon; //图标

lv_timer_t* Menu_EnvPage_Timer;

/***********************************event****************************************************************** */
void EnvPage_timer_cb(lv_timer_t * timer)
{
    uint8_t value_strbuf[6];

    lv_bar_set_value(EnvPage_TemBar, HWInterface.AHT21.temperature, LV_ANIM_OFF);
    lv_bar_set_value(EnvPage_HumiBar, HWInterface.AHT21.humidity, LV_ANIM_OFF);
    sprintf(value_strbuf,"%d", HWInterface.AHT21.temperature);
    lv_label_set_text(EnvPage_TemLabel, value_strbuf);
    sprintf(value_strbuf,"%d", HWInterface.AHT21.humidity);
    lv_label_set_text(EnvPage_HumiLabel, value_strbuf);
}

void EnvPage_Return_Menu(lv_event_t* e)
{
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) //左滑回上一页
    {
        Return_Pre_Page();
    }
}



/***********************************page design****************************************************************** */



void Temp_display(uint8_t* strbuf)
{

   
    EnvPage_TemIcon = lv_label_create(Menu_EnvPage);  
    lv_obj_set_x(EnvPage_TemIcon, -50);
    lv_obj_set_y(EnvPage_TemIcon, -95);
    lv_obj_set_align(EnvPage_TemIcon, LV_ALIGN_CENTER);
    lv_label_set_text(EnvPage_TemIcon,LV_SYMBOL_TEM);
    lv_obj_set_style_text_color(EnvPage_TemIcon, lv_color_hex(0xA03232), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(EnvPage_TemIcon, &ui_icon_CompassEnv_Page28, LV_PART_MAIN | LV_STATE_DEFAULT);

    EnvPage_TemBar = lv_bar_create(Menu_EnvPage);
    lv_bar_set_range(EnvPage_TemBar, -10, 50);
    lv_bar_set_value(EnvPage_TemBar, HWInterface.AHT21.temperature, LV_ANIM_OFF);
    lv_obj_set_width(EnvPage_TemBar, 20);
    lv_obj_set_height(EnvPage_TemBar, 150);
    lv_obj_set_x(EnvPage_TemBar, -50);
    lv_obj_set_y(EnvPage_TemBar, 0);
    lv_obj_set_align(EnvPage_TemBar, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(EnvPage_TemBar, lv_color_hex(0xC80000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(EnvPage_TemBar, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(EnvPage_TemBar, lv_color_hex(0xC83232), LV_PART_INDICATOR | LV_STATE_DEFAULT);

    EnvPage_TemLabel = lv_label_create(Menu_EnvPage);  
    lv_obj_set_x(EnvPage_TemLabel, -50);
    lv_obj_set_y(EnvPage_TemLabel, 100);
    lv_obj_set_align(EnvPage_TemLabel, LV_ALIGN_CENTER);
	sprintf(strbuf,"%d",HWInterface.AHT21.temperature);
    lv_label_set_text(EnvPage_TemLabel, strbuf);
    lv_obj_set_style_text_font(EnvPage_TemLabel, &ui_font_Cuyuan30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(EnvPage_TemLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    EnvPage_TemUnitLabel = lv_label_create(Menu_EnvPage);  
    lv_obj_set_x(EnvPage_TemUnitLabel, -20);
    lv_obj_set_y(EnvPage_TemUnitLabel, 100);
    lv_obj_set_align(EnvPage_TemUnitLabel, LV_ALIGN_CENTER);
    lv_label_set_text(EnvPage_TemUnitLabel, LV_SYMBOL_Celsius);
    lv_obj_set_style_text_color(EnvPage_TemUnitLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(EnvPage_TemUnitLabel, &ui_icon_Celsius24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(EnvPage_TemUnitLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    
}


void Humi_Display(uint8_t* strbuf)
{
    
    EnvPage_THumiIcon = lv_label_create(Menu_EnvPage);
    lv_obj_set_width(EnvPage_THumiIcon, LV_SIZE_CONTENT);  
    lv_obj_set_height(EnvPage_THumiIcon, LV_SIZE_CONTENT);   
    lv_obj_set_x(EnvPage_THumiIcon, 50);
    lv_obj_set_y(EnvPage_THumiIcon, -95);
    lv_obj_set_align(EnvPage_THumiIcon, LV_ALIGN_CENTER);
    lv_label_set_text(EnvPage_THumiIcon, LV_SYMBOL_HUMI);
    lv_obj_set_style_text_color(EnvPage_THumiIcon, lv_color_hex(0x1496FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(EnvPage_THumiIcon, &ui_icon_CompassEnv_Page28, LV_PART_MAIN | LV_STATE_DEFAULT);


    EnvPage_HumiBar = lv_bar_create(Menu_EnvPage);
    lv_bar_set_value(EnvPage_HumiBar, HWInterface.AHT21.humidity, LV_ANIM_OFF);
    lv_obj_set_width(EnvPage_HumiBar, 20);
    lv_obj_set_height(EnvPage_HumiBar, 150);
    lv_obj_set_x(EnvPage_HumiBar, 50);
    lv_obj_set_y(EnvPage_HumiBar, 0);
    lv_obj_set_align(EnvPage_HumiBar, LV_ALIGN_CENTER);

    EnvPage_HumiLabel = lv_label_create(Menu_EnvPage);
    lv_obj_set_width(EnvPage_HumiLabel, LV_SIZE_CONTENT);   
    lv_obj_set_height(EnvPage_HumiLabel, LV_SIZE_CONTENT);   
    lv_obj_set_x(EnvPage_HumiLabel, 50);
    lv_obj_set_y(EnvPage_HumiLabel, 100);
    lv_obj_set_align(EnvPage_HumiLabel, LV_ALIGN_CENTER);
	sprintf(strbuf,"%d", HWInterface.AHT21.humidity);
    lv_label_set_text(EnvPage_HumiLabel, strbuf);
    lv_obj_set_style_text_font(EnvPage_HumiLabel, &ui_font_Cuyuan30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(EnvPage_HumiLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);


    EnvPage_HumiUnitLabel = lv_label_create(Menu_EnvPage);
    lv_obj_set_width(EnvPage_HumiUnitLabel, LV_SIZE_CONTENT);   
    lv_obj_set_height(EnvPage_HumiUnitLabel, LV_SIZE_CONTENT);   
    lv_obj_set_x(EnvPage_HumiUnitLabel, 80);
    lv_obj_set_y(EnvPage_HumiUnitLabel, 100);
    lv_obj_set_align(EnvPage_HumiUnitLabel, LV_ALIGN_CENTER);
    lv_label_set_text(EnvPage_HumiUnitLabel, "%");
    lv_obj_set_style_text_color(EnvPage_HumiUnitLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(EnvPage_HumiUnitLabel, &ui_font_Cuyuan30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(EnvPage_HumiUnitLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);


}

void Menu_EnvPage_screen_init(void)
{
    uint8_t strbuf[5];
    Menu_EnvPage = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(Menu_EnvPage, lv_color_hex3(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_EnvPage, LV_OBJ_FLAG_SCROLLABLE);
    Temp_display(strbuf);
    Humi_Display(strbuf);
    
    Menu_EnvPage_Timer = lv_timer_create(EnvPage_timer_cb, 500, NULL);
    lv_obj_add_event_cb(Menu_EnvPage, EnvPage_Return_Menu,LV_EVENT_GESTURE, NULL);

}

void Menu_EnvPage_screen_deinit(void)
{
    lv_timer_del(Menu_EnvPage_Timer);
}