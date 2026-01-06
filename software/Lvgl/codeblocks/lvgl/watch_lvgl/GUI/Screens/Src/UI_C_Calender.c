#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../Include/UI_C_Calender.h"
#include "../../../Func/Include/FuncHWDataManage.h"

/***********************************Page definition****************************************************************** */
page_t Menu_Calender = { Menu_CalendarPage_screen_init, Menu_CalendarPage_screen_deinit, &Menu_CalendarPage };

/***********************************lv_obj_t and num****************************************************************** */
lv_obj_t * Menu_CalendarPage;
lv_obj_t* Component_Calendar;

/***********************************event****************************************************************** */

void Calendar_Return_Menu(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) //左滑回上一页
    {
        Return_Pre_Page();
    }
}


/***********************************page design****************************************************************** */
void Menu_CalendarPage_screen_init(void)
{
    HW_DateTimeTypeDef DateTime;
    HWInterface.RealTimeClock.GetTimeDate(&DateTime);

    Menu_CalendarPage = lv_obj_create(NULL);
    lv_obj_clear_flag(Menu_CalendarPage, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(Menu_CalendarPage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    Component_Calendar = lv_calendar_create(Menu_CalendarPage);
    lv_obj_set_width(Component_Calendar, 240);
    lv_obj_set_height(Component_Calendar, 280);
    lv_obj_set_align(Component_Calendar, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(Component_Calendar, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_color(Component_Calendar, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(Component_Calendar, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_border_width(Component_Calendar, 5, LV_PART_MAIN);

    //设置显示今天的日期
    lv_calendar_set_today_date(Component_Calendar, 2000 + DateTime.Year, DateTime.Month, DateTime.Date);
    lv_calendar_set_showed_date(Component_Calendar, 2000+DateTime.Year, DateTime.Month);


    //在lv_calendar_header_dropdown_create所处源文件处去修改year_list，目前该版本只支持到2023，需要去修改
    //lv_calendar_header_dropdown_create(Component_Calendar); //下拉选择时间
    lv_calendar_header_arrow_create(Component_Calendar); //左/右箭头跳转上/下月
    
    lv_obj_add_event_cb(Menu_CalendarPage, Calendar_Return_Menu, LV_EVENT_GESTURE, NULL);
}


void Menu_CalendarPage_screen_deinit(void)
{
    //NULL
}