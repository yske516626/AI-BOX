#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../include/UI_N_SettingPage.h"
#include "../include/UI_O_SetFunAchPage.h"
#include "../include/UI_P_SetDatePage.h"
#include "../../../Func/Include/FuncHWDataManage.h" 



/***********************************icon/img customize****************************************************************** */
#define LV_SYMBOL_Bright "\xEE\x98\x80" 
#define LV_SYMBOL_Hibernate "\xEE\x99\xB5" 
#define LV_SYMBOL_Date "\xEE\x98\x87" 
#define LV_SYMBOL_Wrist "\xEE\x98\xB7"



/***********************************Page definition****************************************************************** */
page_t Menu_Setting = { Menu_SettingPage_screen_init,Menu_SettingPage_screen_deinit,&Menu_SettingPage };




/***********************************obj****************************************************************** */
lv_obj_t* Menu_SettingPage;

//亮屏时间
lv_obj_t* Set_BrightScreen_Row; 
lv_obj_t* Set_BrightScreen_IconContain;//图标容器
lv_obj_t* Set_BrightScreen_IconLabel;  //图标
lv_obj_t* Set_BrightScreen_TextLabel; //文本


//息屏：息屏几秒后，硬件停止工作
lv_obj_t* Set_Hibernate_Row; 
lv_obj_t* Set_Hibernate_IconContain;//图标容器
lv_obj_t* Set_Hibernate_IconLabel; //图标
lv_obj_t* Set_Hibernate_TextLabel; //文本

//日期设置
lv_obj_t* Set_Date_Row; 
lv_obj_t* Set_Date_IconContain;
lv_obj_t* Set_Date_IconLabel; //图标
lv_obj_t* Set_Date_TextLabel; //文本

//翻腕亮屏
lv_obj_t* Set_Wrist_Row;
lv_obj_t* Set_Wrist_IconContain;
lv_obj_t* Set_Wrist_IconLabel;
lv_obj_t* Set_Wrist_TextLabel;
lv_obj_t* Set_Wrist_SwitchBtn; 



/***********************************event****************************************************************** */
void ReturnMenu_event_cb(lv_event_t* e)
{
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        Return_Pre_Page();
    }
}

void OpenBriPage_event_cb(lv_event_t* e)
{
    Load_New_Page(&Setting_Bright);
    
}

void OpenHibPage_event_cb(lv_event_t* e)
{
    
    Load_New_Page(&Setting_Hibernate);
}

void OpenDatePage_event_cb(lv_event_t* e)
{
    Load_New_Page(&Page_DateTimeSet);
}

void OpenWrist_event_cb(lv_event_t* e)
{
    if(lv_obj_has_state(Set_Wrist_SwitchBtn,LV_STATE_CHECKED))
    {
         //open
         //HWInterface.Motion.WristEnable();
    }
    else
    {
         //close
         //HWInterface.Motion.WristDisable();
    }
}
/***********************************page design****************************************************************** */
void Menu_SettingPage_screen_init(void)
{
    Menu_SettingPage = lv_obj_create(NULL);

    //********************日历***********************
    Set_BrightScreen_Row = lv_obj_create(Menu_SettingPage);
    lv_obj_set_width(Set_BrightScreen_Row, 230);
    lv_obj_set_height(Set_BrightScreen_Row, 60);
    lv_obj_set_y(Set_BrightScreen_Row, 10);
    lv_obj_set_align(Set_BrightScreen_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Set_BrightScreen_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Set_BrightScreen_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Set_BrightScreen_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Set_BrightScreen_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Set_BrightScreen_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Set_BrightScreen_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Set_BrightScreen_IconContain = lv_obj_create(Set_BrightScreen_Row);  //用于容纳图标
    lv_obj_set_width(Set_BrightScreen_IconContain, 50);
    lv_obj_set_height(Set_BrightScreen_IconContain, 50);
    lv_obj_set_align(Set_BrightScreen_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Set_BrightScreen_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Set_BrightScreen_IconContain, lv_color_hex(0xFF8080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Set_BrightScreen_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Set_BrightScreen_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Set_BrightScreen_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Set_BrightScreen_IconLabel = lv_label_create(Set_BrightScreen_IconContain); //图标标签
    lv_obj_set_width(Set_BrightScreen_IconLabel, LV_SIZE_CONTENT);  
    lv_obj_set_height(Set_BrightScreen_IconLabel, LV_SIZE_CONTENT);  
    lv_obj_set_align(Set_BrightScreen_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Set_BrightScreen_IconLabel, LV_SYMBOL_Bright);
    lv_obj_set_style_text_font(Set_BrightScreen_IconLabel, &ui_icon_SettingPage30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Set_BrightScreen_TextLabel = lv_label_create(Set_BrightScreen_Row); //文本显示：日历
    lv_obj_set_width(Set_BrightScreen_TextLabel, LV_SIZE_CONTENT);   
    lv_obj_set_height(Set_BrightScreen_TextLabel, LV_SIZE_CONTENT);    
    lv_obj_set_x(Set_BrightScreen_TextLabel, 80);
    lv_obj_set_y(Set_BrightScreen_TextLabel, 0);
    lv_obj_set_align(Set_BrightScreen_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Set_BrightScreen_TextLabel, "亮屏时间");
    lv_obj_set_style_text_font(Set_BrightScreen_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);


    //********************心率***********************
    Set_Hibernate_Row = lv_obj_create(Menu_SettingPage);
    lv_obj_set_width(Set_Hibernate_Row, 230);
    lv_obj_set_height(Set_Hibernate_Row, 60);
    lv_obj_set_y(Set_Hibernate_Row, 80);
    lv_obj_set_align(Set_Hibernate_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Set_Hibernate_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Set_Hibernate_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Set_Hibernate_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Set_Hibernate_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Set_Hibernate_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Set_Hibernate_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Set_Hibernate_IconContain = lv_obj_create(Set_Hibernate_Row);  //用于容纳图标
    lv_obj_set_width(Set_Hibernate_IconContain, 50);
    lv_obj_set_height(Set_Hibernate_IconContain, 50);
    lv_obj_set_align(Set_Hibernate_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Set_Hibernate_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Set_Hibernate_IconContain, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Set_Hibernate_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Set_Hibernate_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Set_Hibernate_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Set_Hibernate_IconLabel = lv_label_create(Set_Hibernate_IconContain); //图标标签
    lv_obj_set_width(Set_Hibernate_IconLabel, LV_SIZE_CONTENT); 
    lv_obj_set_height(Set_Hibernate_IconLabel, LV_SIZE_CONTENT);  
    lv_obj_set_align(Set_Hibernate_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Set_Hibernate_IconLabel, LV_SYMBOL_Hibernate);
    lv_obj_set_style_text_color(Set_Hibernate_IconLabel, lv_color_hex(0xFF3030), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Set_Hibernate_IconLabel, &ui_icon_SettingPage30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Set_Hibernate_TextLabel = lv_label_create(Set_Hibernate_Row); //文本显示
    lv_obj_set_width(Set_Hibernate_TextLabel, LV_SIZE_CONTENT);   
    lv_obj_set_height(Set_Hibernate_TextLabel, LV_SIZE_CONTENT);    
    lv_obj_set_x(Set_Hibernate_TextLabel, 80);
    lv_obj_set_y(Set_Hibernate_TextLabel, 0);
    lv_obj_set_align(Set_Hibernate_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Set_Hibernate_TextLabel, "熄屏时间");
    lv_obj_set_style_text_font(Set_Hibernate_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //********************血氧***********************
    Set_Date_Row = lv_obj_create(Menu_SettingPage);
    lv_obj_set_width(Set_Date_Row, 230);
    lv_obj_set_height(Set_Date_Row, 60);
    lv_obj_set_y(Set_Date_Row, 150);
    lv_obj_set_align(Set_Date_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Set_Date_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Set_Date_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Set_Date_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Set_Date_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Set_Date_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Set_Date_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Set_Date_IconContain = lv_obj_create(Set_Date_Row);  //用于容纳图标
    lv_obj_set_width(Set_Date_IconContain, 50);
    lv_obj_set_height(Set_Date_IconContain, 50);
    lv_obj_set_align(Set_Date_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Set_Date_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Set_Date_IconContain, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Set_Date_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Set_Date_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Set_Date_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Set_Date_IconLabel = lv_label_create(Set_Date_IconContain); //图标标签
    lv_obj_set_width(Set_Date_IconLabel, LV_SIZE_CONTENT); 
    lv_obj_set_height(Set_Date_IconLabel, LV_SIZE_CONTENT);  
    lv_obj_set_align(Set_Date_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Set_Date_IconLabel, LV_SYMBOL_Date); //图标
    lv_obj_set_style_text_color(Set_Date_IconLabel, lv_color_hex(0xFF3030), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Set_Date_IconLabel, &ui_icon_SettingPage30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Set_Date_TextLabel = lv_label_create(Set_Date_Row); //文本显示
    lv_obj_set_width(Set_Date_TextLabel, LV_SIZE_CONTENT);   
    lv_obj_set_height(Set_Date_TextLabel, LV_SIZE_CONTENT);    
    lv_obj_set_x(Set_Date_TextLabel, 80);
    lv_obj_set_y(Set_Date_TextLabel, 0);
    lv_obj_set_align(Set_Date_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Set_Date_TextLabel, "日期");
    lv_obj_set_style_text_font(Set_Date_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //********************计算器***********************
    Set_Wrist_Row = lv_obj_create(Menu_SettingPage);
    lv_obj_set_width(Set_Wrist_Row, 230);
    lv_obj_set_height(Set_Wrist_Row, 60);
    lv_obj_set_y(Set_Wrist_Row, 220);
    lv_obj_set_align(Set_Wrist_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Set_Wrist_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Set_Wrist_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Set_Wrist_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Set_Wrist_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Set_Wrist_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Set_Wrist_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Set_Wrist_IconContain = lv_obj_create(Set_Wrist_Row);  //用于容纳图标
    lv_obj_set_width(Set_Wrist_IconContain, 50);
    lv_obj_set_height(Set_Wrist_IconContain, 50);
    lv_obj_set_align(Set_Wrist_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Set_Wrist_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Set_Wrist_IconContain, lv_color_hex(0x8B8682), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Set_Wrist_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Set_Wrist_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Set_Wrist_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Set_Wrist_IconLabel = lv_label_create(Set_Wrist_IconContain); //图标标签
    lv_obj_set_width(Set_Wrist_IconLabel, LV_SIZE_CONTENT); 
    lv_obj_set_height(Set_Wrist_IconLabel, LV_SIZE_CONTENT);  
    lv_obj_set_align(Set_Wrist_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Set_Wrist_IconLabel, LV_SYMBOL_Wrist); //图标
    lv_obj_set_style_text_color(Set_Wrist_IconLabel, lv_color_hex(0xFFFAFA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Set_Wrist_IconLabel, &ui_icon_SettingPage30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Set_Wrist_TextLabel = lv_label_create(Set_Wrist_Row); //文本显示
    lv_obj_set_width(Set_Wrist_TextLabel, LV_SIZE_CONTENT);   
    lv_obj_set_height(Set_Wrist_TextLabel, LV_SIZE_CONTENT);    
    lv_obj_set_x(Set_Wrist_TextLabel, 80);
    lv_obj_set_y(Set_Wrist_TextLabel, 0);
    lv_obj_set_align(Set_Wrist_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Set_Wrist_TextLabel, "翻腕亮屏");
    lv_obj_set_style_text_font(Set_Wrist_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Set_Wrist_SwitchBtn = lv_switch_create(Set_Wrist_Row);
    lv_obj_set_width(Set_Wrist_SwitchBtn, 55);
    lv_obj_set_height(Set_Wrist_SwitchBtn, 25);
    lv_obj_set_align(Set_Wrist_SwitchBtn, LV_ALIGN_RIGHT_MID);
	if(HWInterface.Motion.wrist_is_enabled)
    {
        lv_obj_add_state(Set_Wrist_SwitchBtn, LV_STATE_CHECKED);
    }

    lv_obj_add_event_cb(Menu_SettingPage, ReturnMenu_event_cb, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(Set_BrightScreen_Row, OpenBriPage_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Set_Hibernate_Row, OpenHibPage_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Set_Date_Row, OpenDatePage_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Set_Wrist_SwitchBtn, OpenWrist_event_cb, LV_EVENT_VALUE_CHANGED, NULL);




}

void Menu_SettingPage_screen_deinit(void)
{

}