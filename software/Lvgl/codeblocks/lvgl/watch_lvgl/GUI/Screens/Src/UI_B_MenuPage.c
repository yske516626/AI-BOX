/*
板块:
    icon customize：图标定义
    lv_obj_t and num：对象和对应存储数值定义
    Page definition：页面定义结构体
    event callback：回调函数
    page design：页面设置（init）
可以通过搜索跳转
*/

#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../Include/UI_A_HomePage.h"
#include "../Include/UI_B_MenuPage.h"
#include "../Include/UI_C_Calender.h"
#include "../Include/UI_D_HearRatePage.h"
#include "../include/UI_E_SPO2page.h"
#include "../include/UI_F_Calculatorpage.h"
#include "../include/UI_G_TimerPage.h"
#include "../include/UI_H_CompassPage.h"
#include "../include/UI_I_nfcPage.h"
#include "../include/UI_J_EnvPage.h"
#include "../include/UI_K_GamePage.h"
#include "../include/UI_M_MottionPage.h"
#include "../include/UI_N_SettingPage.h"
#include "../Include/UI_Q_AiPage.h"
#include "../../../Func/Include/FuncHWDataManage.h"



/***********************************icon customize****************************************************************** */
#define LV_SYMBOL_Game "\xEE\x98\x80"
#define LV_SYMBOL_Mottion "\xEE\xA0\x87"
#define LV_SYMBOL_Card "\xEE\x98\xA7"
#define LV_SYMBOL_Set "\xEE\x99\x83"
#define LV_SYMBOL_Env "\xEE\x98\xA3" //环境
#define LV_SYMBOL_Clu "\xEE\xAE\xA0"  //计算器
#define LV_SYMBOL_Calender "\xEE\x98\x82" //日历
#define LV_SYMBOL_HR "\xEE\xA2\x9A" //心率
#define LV_SYMBOL_Timer "\xEE\x98\x9B"  //计时器
#define LV_SYMBOL_Cp "\xEE\x98\xB7"  //指南针
#define LV_SYMBOL_SPO2 "\xEE\x98\xAD"
#define LV_SYMBOL_MenuAI  "\xEE\x9E\xBB"

#define Row_High 60
#define Row_wide 200

/***********************************lv_obj_t and num****************************************************************** */
//////////////////////////////////////////////////////////////////////////
//主界面对象容器
lv_obj_t* ui_MenuPage;


//////////////////////////////////////////////////////////////////////////
//日历列
lv_obj_t* Menu_Calendar_Row; //建立在ui_MenuPage上的显示对象 -- 日历
lv_obj_t* Menu_Calendar_IconContain;//日历图标容器
lv_obj_t* Menu_Calendar_IconLabel;  //日历图标
lv_obj_t* Menu_Calendar_TextLabel; //日历文本


//心率列
lv_obj_t* Menu_HeartRate_Row; //心率列容器
lv_obj_t* Menu_HeartRate_IconContain;//心率图标容器
lv_obj_t* Menu_HeartRate_IconLabel; //心率图标
lv_obj_t* Menu_HeartRate_TextLabel; //文本

//心氧列
lv_obj_t* Menu_SpO2_Row; //心氧列容器
lv_obj_t* Menu_SpO2_IconContain;
lv_obj_t* Menu_SpO2_IconLabel; //心氧图标
lv_obj_t* Menu_SpO2_TextLabel; //文本

//计算器
lv_obj_t* Menu_Calculator_Row;
lv_obj_t* Menu_Calculator_IconContain;
lv_obj_t* Menu_Calculator_IconLabel;
lv_obj_t* Menu_Calculator_TextLabel;

//计时器
lv_obj_t* Menu_Timer_Row;
lv_obj_t* Menu_Timer_IconContain;
lv_obj_t* Menu_Timer_IconLabel;
lv_obj_t* Menu_Timer_TextLabel;

//指南针
lv_obj_t* Menu_Compass_Row;
lv_obj_t* Menu_Compass_IconContain;
lv_obj_t* Menu_Compass_IconLabel;
lv_obj_t* Menu_Compass_TextLabel;

//卡包
lv_obj_t* Menu_nfcCard_Row;
lv_obj_t* Menu_nfcCard_IconContain;
lv_obj_t* Menu_nfcCard_IconLabel;
lv_obj_t* Menu_nfcCard_TextLabel;

//环境：温湿度
lv_obj_t* Menu_Environment_Row;
lv_obj_t* Menu_Environment_IconContain;
lv_obj_t* Menu_Environment_IconLabel;
lv_obj_t* Menu_Environment_TextLabel;


//游戏
lv_obj_t* Menu_Game_Row;
lv_obj_t* Menu_Game_IconContain;
lv_obj_t* Menu_Game_IconLabel;
lv_obj_t* Menu_Game_TextLabel;

//运动
lv_obj_t* Menu_Motion_Row;
lv_obj_t* Menu_Motion_IconContain;
lv_obj_t* Menu_Motion_IconLabel;
lv_obj_t* Menu_Motion_TextLabel;

//设置
lv_obj_t* Menu_Setting_Row;
lv_obj_t* Menu_Setting_IconContain;
lv_obj_t* Menu_Setting_IconLabel;
lv_obj_t* Menu_Setting_TextLabel;

//ai
lv_obj_t* Menu_AI_Row;
lv_obj_t* Menu_AI_IconContain;
lv_obj_t* Menu_AI_IconLabel;
lv_obj_t* Menu_AI_TextLabel;
uint8_t Menu_AI_command;

int16_t ui_MenuScrollY;

/***********************************Page definition****************************************************************** */
page_t Page_Menu = {ui_MenuPage_screen_init, ui_MenuPage_screen_deinit, &ui_MenuPage};



/***********************************event callback****************************************************************** */
void ui_event_MenuPage(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_GESTURE)
    {
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)  //左滑
        {
            Return_Pre_Page(); //返回上一页
            //Load_New_Page(&Page_Home);

        }
    }
    if (event_code == LV_EVENT_SCROLL_END)
    {
        ui_MenuScrollY = lv_obj_get_scroll_y(ui_MenuPage);
    }
}


void ui_event_MenuCalendarRow(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Load_New_Page(&Menu_Calender);
    }
}

void ui_event_MenuHeartRateRow(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Load_New_Page(&Menu_HeatRate);
    }
}

void ui_event_MenuSpO2Row(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Load_New_Page(&Menu_SPO2);
    }

}

void ui_event_MenuCalculatorRow(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Load_New_Page(&Menu_Calculator);
    }
}

void ui_event_MenuTimerRow(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Load_New_Page(&Menu_Timer);
    }
}

void ui_event_MenuCompassRow(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Load_New_Page(&Menu_Compass);
    }
}

void ui_event_MenuNfcCard_Row(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        //Load_New_Page(&Menu_NFC);
        Menu_nfcPage_screen_init();
    }
}

void ui_event_MenuEnvRow(lv_event_t* e)
{

    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Load_New_Page(&Menu_Env);
    }
}

void ui_event_MenuGameRow(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Load_New_Page(&Menu_Game);
    }
}

void ui_event_MenuMotionRow(lv_event_t* e)
{
    Menu_MottionPage_screen_init();
}

void ui_event_MenuSetRow(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Load_New_Page(&Menu_Setting);
    }
}

void ui_event_MenuAI(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
	{
		Load_New_Page(&Menu_AI);

    }
}

void scroll_event_cb(lv_event_t* e)
{
    lv_obj_t * cont = lv_event_get_target(e);

    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for(i = 0; i < child_cnt; i++) {
        lv_obj_t * child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if(diff_y >= r) {
            x = r;
        } else {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0);

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}



/***********************************page design****************************************************************** */



void ui_MenuPage_screen_init(void)
{


    ui_MenuPage = lv_obj_create(NULL);
    lv_obj_set_size(ui_MenuPage, 240, 280);
    lv_obj_set_style_bg_color(ui_MenuPage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_t* p = lv_obj_create(ui_MenuPage);
    lv_obj_set_size(p, 240, 260);
    lv_obj_center(p);
    lv_obj_set_style_bg_color(p, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_flex_flow(p, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(p, scroll_event_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_set_style_radius(p, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(p, true, 0);
    lv_obj_set_scroll_dir(p, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(p, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(p, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_opa(p, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明


    //********************日历***********************
    Menu_Calendar_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_Calendar_Row, Row_wide);
    lv_obj_set_height(Menu_Calendar_Row, Row_High);
    lv_obj_set_y(Menu_Calendar_Row, 10);
    lv_obj_set_align(Menu_Calendar_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_Calendar_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_Calendar_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_Calendar_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_Calendar_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_Calendar_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_Calendar_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_Calendar_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Calendar_IconContain = lv_obj_create(Menu_Calendar_Row);  //用于容纳图标
    lv_obj_set_width(Menu_Calendar_IconContain, 50);
    lv_obj_set_height(Menu_Calendar_IconContain, 50);
    lv_obj_set_align(Menu_Calendar_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_Calendar_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_Calendar_IconContain, lv_color_hex(0xFF8080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_Calendar_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_Calendar_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_Calendar_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_Calendar_IconLabel = lv_label_create(Menu_Calendar_IconContain); //图标标签
    lv_obj_set_width(Menu_Calendar_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Calendar_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_Calendar_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_Calendar_IconLabel, LV_SYMBOL_Calender);
    lv_obj_set_style_text_font(Menu_Calendar_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Calendar_TextLabel = lv_label_create(Menu_Calendar_Row); //文本显示：日历
    lv_obj_set_width(Menu_Calendar_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Calendar_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_Calendar_TextLabel, 80);
    lv_obj_set_y(Menu_Calendar_TextLabel, 0);
    lv_obj_set_align(Menu_Calendar_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_Calendar_TextLabel, "日历");
    lv_obj_set_style_text_font(Menu_Calendar_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);


    //********************心率***********************
    Menu_HeartRate_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_HeartRate_Row, Row_wide);
    lv_obj_set_height(Menu_HeartRate_Row, Row_High);
    lv_obj_set_y(Menu_HeartRate_Row, 80);
    lv_obj_set_align(Menu_HeartRate_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_HeartRate_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_HeartRate_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_HeartRate_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_HeartRate_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_HeartRate_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_HeartRate_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_HeartRate_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_HeartRate_IconContain = lv_obj_create(Menu_HeartRate_Row);  //用于容纳图标
    lv_obj_set_width(Menu_HeartRate_IconContain, 50);
    lv_obj_set_height(Menu_HeartRate_IconContain, 50);
    lv_obj_set_align(Menu_HeartRate_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_HeartRate_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_HeartRate_IconContain, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_HeartRate_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_HeartRate_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_HeartRate_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_HeartRate_IconLabel = lv_label_create(Menu_HeartRate_IconContain); //图标标签
    lv_obj_set_width(Menu_HeartRate_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_HeartRate_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_HeartRate_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_HeartRate_IconLabel, LV_SYMBOL_HR);
    lv_obj_set_style_text_color(Menu_HeartRate_IconLabel, lv_color_hex(0xFF3030), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_HeartRate_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_HeartRate_TextLabel = lv_label_create(Menu_HeartRate_Row); //文本显示
    lv_obj_set_width(Menu_HeartRate_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_HeartRate_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_HeartRate_TextLabel, 80);
    lv_obj_set_y(Menu_HeartRate_TextLabel, 0);
    lv_obj_set_align(Menu_HeartRate_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_HeartRate_TextLabel, "心率");
    lv_obj_set_style_text_font(Menu_HeartRate_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //********************血氧***********************
    Menu_SpO2_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_SpO2_Row, Row_wide);
    lv_obj_set_height(Menu_SpO2_Row, Row_High);
    lv_obj_set_y(Menu_SpO2_Row, 150);
    lv_obj_set_align(Menu_SpO2_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_SpO2_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_SpO2_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_SpO2_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_SpO2_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_SpO2_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_SpO2_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_SpO2_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_SpO2_IconContain = lv_obj_create(Menu_SpO2_Row);  //用于容纳图标
    lv_obj_set_width(Menu_SpO2_IconContain, 50);
    lv_obj_set_height(Menu_SpO2_IconContain, 50);
    lv_obj_set_align(Menu_SpO2_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_SpO2_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_SpO2_IconContain, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_SpO2_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_SpO2_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_SpO2_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_SpO2_IconLabel = lv_label_create(Menu_SpO2_IconContain); //图标标签
    lv_obj_set_width(Menu_SpO2_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_SpO2_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_SpO2_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_SpO2_IconLabel, LV_SYMBOL_SPO2); //图标
    lv_obj_set_style_text_color(Menu_SpO2_IconLabel, lv_color_hex(0xFF3030), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_SpO2_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_SpO2_TextLabel = lv_label_create(Menu_SpO2_Row); //文本显示
    lv_obj_set_width(Menu_SpO2_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_SpO2_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_SpO2_TextLabel, 80);
    lv_obj_set_y(Menu_SpO2_TextLabel, 0);
    lv_obj_set_align(Menu_SpO2_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_SpO2_TextLabel, "血氧");
    lv_obj_set_style_text_font(Menu_SpO2_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //********************计算器***********************
    Menu_Calculator_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_Calculator_Row, Row_wide);
    lv_obj_set_height(Menu_Calculator_Row, Row_High);
    lv_obj_set_y(Menu_Calculator_Row, 220);
    lv_obj_set_align(Menu_Calculator_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_Calculator_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_Calculator_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_Calculator_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_Calculator_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_Calculator_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_Calculator_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_Calculator_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Calculator_IconContain = lv_obj_create(Menu_Calculator_Row);  //用于容纳图标
    lv_obj_set_width(Menu_Calculator_IconContain, 50);
    lv_obj_set_height(Menu_Calculator_IconContain, 50);
    lv_obj_set_align(Menu_Calculator_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_Calculator_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_Calculator_IconContain, lv_color_hex(0x8B8682), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_Calculator_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_Calculator_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_Calculator_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_Calculator_IconLabel = lv_label_create(Menu_Calculator_IconContain); //图标标签
    lv_obj_set_width(Menu_Calculator_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Calculator_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_Calculator_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_Calculator_IconLabel, LV_SYMBOL_Clu); //图标
    lv_obj_set_style_text_color(Menu_Calculator_IconLabel, lv_color_hex(0xFFFAFA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_Calculator_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Calculator_TextLabel = lv_label_create(Menu_Calculator_Row); //文本显示
    lv_obj_set_width(Menu_Calculator_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Calculator_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_Calculator_TextLabel, 80);
    lv_obj_set_y(Menu_Calculator_TextLabel, 0);
    lv_obj_set_align(Menu_Calculator_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_Calculator_TextLabel, "计算器");
    lv_obj_set_style_text_font(Menu_Calculator_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //********************计时器***********************
    Menu_Timer_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_Timer_Row, Row_wide);
    lv_obj_set_height(Menu_Timer_Row, Row_High);
    lv_obj_set_y(Menu_Timer_Row, 290);
    lv_obj_set_align(Menu_Timer_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_Timer_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_Timer_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_Timer_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_Timer_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_Timer_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_Timer_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_Timer_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Timer_IconContain = lv_obj_create(Menu_Timer_Row);  //用于容纳图标
    lv_obj_set_width(Menu_Timer_IconContain, 50);
    lv_obj_set_height(Menu_Timer_IconContain, 50);
    lv_obj_set_align(Menu_Timer_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_Timer_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_Timer_IconContain, lv_color_hex(0xFFA500), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_Timer_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_Timer_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_Timer_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_Timer_IconLabel = lv_label_create(Menu_Timer_IconContain); //图标标签
    lv_obj_set_width(Menu_Timer_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Timer_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_Timer_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_Timer_IconLabel, LV_SYMBOL_Timer); //图标
    lv_obj_set_style_text_color(Menu_Timer_IconLabel, lv_color_hex(0xFFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_Timer_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Timer_TextLabel = lv_label_create(Menu_Timer_Row); //文本显示
    lv_obj_set_width(Menu_Timer_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Timer_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_Timer_TextLabel, 80);
    lv_obj_set_y(Menu_Timer_TextLabel, 0);
    lv_obj_set_align(Menu_Timer_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_Timer_TextLabel, "计时器");
    lv_obj_set_style_text_font(Menu_Timer_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //********************指南针***********************
    Menu_Compass_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_Compass_Row, Row_wide);
    lv_obj_set_height(Menu_Compass_Row, Row_High);
    lv_obj_set_y(Menu_Compass_Row, 360);
    lv_obj_set_align(Menu_Compass_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_Compass_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_Compass_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_Compass_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_Compass_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_Compass_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_Compass_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_Compass_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Compass_IconContain = lv_obj_create(Menu_Compass_Row);  //用于容纳图标
    lv_obj_set_width(Menu_Compass_IconContain, 50);
    lv_obj_set_height(Menu_Compass_IconContain, 50);
    lv_obj_set_align(Menu_Compass_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_Compass_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_Compass_IconContain, lv_color_hex(0x838B8B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_Compass_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_Compass_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_Compass_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_Compass_IconLabel = lv_label_create(Menu_Compass_IconContain); //图标标签
    lv_obj_set_width(Menu_Compass_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Compass_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_Compass_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_Compass_IconLabel, LV_SYMBOL_Cp); //图标
    lv_obj_set_style_text_color(Menu_Compass_IconLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_Compass_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Compass_TextLabel = lv_label_create(Menu_Compass_Row); //文本显示
    lv_obj_set_width(Menu_Compass_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Compass_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_Compass_TextLabel, 80);
    lv_obj_set_y(Menu_Compass_TextLabel, 0);
    lv_obj_set_align(Menu_Compass_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_Compass_TextLabel, "指南针");
    lv_obj_set_style_text_font(Menu_Compass_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //********************卡包***********************
    Menu_nfcCard_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_nfcCard_Row, Row_wide);
    lv_obj_set_height(Menu_nfcCard_Row, Row_High);
    lv_obj_set_y(Menu_nfcCard_Row, 430);
    lv_obj_set_align(Menu_nfcCard_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_nfcCard_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_nfcCard_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_nfcCard_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_nfcCard_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_nfcCard_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_nfcCard_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_nfcCard_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_nfcCard_IconContain = lv_obj_create(Menu_nfcCard_Row);  //用于容纳图标
    lv_obj_set_width(Menu_nfcCard_IconContain, 50);
    lv_obj_set_height(Menu_nfcCard_IconContain, 50);
    lv_obj_set_align(Menu_nfcCard_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_nfcCard_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_nfcCard_IconContain, lv_color_hex(0x436EEE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_nfcCard_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_nfcCard_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_nfcCard_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_nfcCard_IconLabel = lv_label_create(Menu_nfcCard_IconContain); //图标标签
    lv_obj_set_width(Menu_nfcCard_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_nfcCard_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_nfcCard_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_nfcCard_IconLabel, LV_SYMBOL_Card); //图标
    lv_obj_set_style_text_color(Menu_nfcCard_IconLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_nfcCard_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_nfcCard_TextLabel = lv_label_create(Menu_nfcCard_Row); //文本显示
    lv_obj_set_width(Menu_nfcCard_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_nfcCard_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_nfcCard_TextLabel, 80);
    lv_obj_set_y(Menu_nfcCard_TextLabel, 0);
    lv_obj_set_align(Menu_nfcCard_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_nfcCard_TextLabel, "卡包");
    lv_obj_set_style_text_font(Menu_nfcCard_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);


     //********************环境***********************
    Menu_Environment_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_Environment_Row, Row_wide);
    lv_obj_set_height(Menu_Environment_Row, Row_High);
    lv_obj_set_y(Menu_Environment_Row, 500);
    lv_obj_set_align(Menu_Environment_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_Environment_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_Environment_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_Environment_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_Environment_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_Environment_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_Environment_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_Environment_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Environment_IconContain = lv_obj_create(Menu_Environment_Row);  //用于容纳图标
    lv_obj_set_width(Menu_Environment_IconContain, 50);
    lv_obj_set_height(Menu_Environment_IconContain, 50);
    lv_obj_set_align(Menu_Environment_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_Environment_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_Environment_IconContain, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_Environment_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_Environment_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_Environment_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_Environment_IconLabel = lv_label_create(Menu_Environment_IconContain); //图标标签
    lv_obj_set_width(Menu_Environment_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Environment_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_Environment_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_Environment_IconLabel, LV_SYMBOL_Env); //图标
    lv_obj_set_style_text_color(Menu_Environment_IconLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_Environment_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Environment_TextLabel = lv_label_create(Menu_Environment_Row); //文本显示
    lv_obj_set_width(Menu_Environment_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Environment_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_Environment_TextLabel, 80);
    lv_obj_set_y(Menu_Environment_TextLabel, 0);
    lv_obj_set_align(Menu_Environment_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_Environment_TextLabel, "环境");
    lv_obj_set_style_text_font(Menu_Environment_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //******************游戏*************************
    Menu_Game_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_Game_Row, Row_wide);
    lv_obj_set_height(Menu_Game_Row, Row_High);
    lv_obj_set_y(Menu_Game_Row, 570);
    lv_obj_set_align(Menu_Game_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_Game_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_Game_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_Game_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_Game_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_Game_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_Game_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_Game_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Game_IconContain = lv_obj_create(Menu_Game_Row);  //用于容纳图标
    lv_obj_set_width(Menu_Game_IconContain, 50);
    lv_obj_set_height(Menu_Game_IconContain, 50);
    lv_obj_set_align(Menu_Game_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_Game_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_Game_IconContain, lv_color_hex(0xfea803), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_Game_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_Game_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_Game_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_Game_IconLabel = lv_label_create(Menu_Game_IconContain); //图标标签
    lv_obj_set_width(Menu_Game_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Game_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_Game_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_Game_IconLabel, LV_SYMBOL_Game); //图标
    lv_obj_set_style_text_color(Menu_Game_IconLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_Game_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Game_TextLabel = lv_label_create(Menu_Game_Row); //文本显示
    lv_obj_set_width(Menu_Game_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Game_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_Game_TextLabel, 80);
    lv_obj_set_y(Menu_Game_TextLabel, 0);
    lv_obj_set_align(Menu_Game_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_Game_TextLabel, "游戏");
    lv_obj_set_style_text_font(Menu_Game_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //******************运动*************************
    Menu_Motion_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_Motion_Row, Row_wide);
    lv_obj_set_height(Menu_Motion_Row, Row_High);
    lv_obj_set_y(Menu_Motion_Row, 640);
    lv_obj_set_align(Menu_Motion_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_Motion_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_Motion_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_Motion_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_Motion_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_Motion_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_Motion_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_Motion_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Motion_IconContain = lv_obj_create(Menu_Motion_Row);  //用于容纳图标
    lv_obj_set_width(Menu_Motion_IconContain, 50);
    lv_obj_set_height(Menu_Motion_IconContain, 50);
    lv_obj_set_align(Menu_Motion_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_Motion_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_Motion_IconContain, lv_color_hex(0x00FF7F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_Motion_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_Motion_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_Motion_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_Motion_IconLabel = lv_label_create(Menu_Motion_IconContain); //图标标签
    lv_obj_set_width(Menu_Motion_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Motion_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_Motion_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_Motion_IconLabel, LV_SYMBOL_Mottion); //图标
    lv_obj_set_style_text_color(Menu_Motion_IconLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_Motion_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Motion_TextLabel = lv_label_create(Menu_Motion_Row); //文本显示
    lv_obj_set_width(Menu_Motion_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Motion_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_Motion_TextLabel, 80);
    lv_obj_set_y(Menu_Motion_TextLabel, 0);
    lv_obj_set_align(Menu_Motion_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_Motion_TextLabel, "运动");
    lv_obj_set_style_text_font(Menu_Motion_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //******************设置*************************
    Menu_Setting_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_Setting_Row, Row_wide);
    lv_obj_set_height(Menu_Setting_Row, Row_High);
    lv_obj_set_y(Menu_Setting_Row, 710);
    lv_obj_set_align(Menu_Setting_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_Setting_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_Setting_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_Setting_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_Setting_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_Setting_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_Setting_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_Setting_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Setting_IconContain = lv_obj_create(Menu_Setting_Row);  //用于容纳图标
    lv_obj_set_width(Menu_Setting_IconContain, 50);
    lv_obj_set_height(Menu_Setting_IconContain, 50);
    lv_obj_set_align(Menu_Setting_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_Setting_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_Setting_IconContain, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_Setting_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_Setting_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_Setting_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_Setting_IconLabel = lv_label_create(Menu_Setting_IconContain); //图标标签
    lv_obj_set_width(Menu_Setting_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Setting_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_Setting_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_Setting_IconLabel, LV_SYMBOL_Set); //图标
    lv_obj_set_style_text_color(Menu_Setting_IconLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_Setting_IconLabel, &ui_icon_MenuPageHost30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_Setting_TextLabel = lv_label_create(Menu_Setting_Row); //文本显示
    lv_obj_set_width(Menu_Setting_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_Setting_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_Setting_TextLabel, 80);
    lv_obj_set_y(Menu_Setting_TextLabel, 0);
    lv_obj_set_align(Menu_Setting_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_Setting_TextLabel, "设置");
    lv_obj_set_style_text_font(Menu_Setting_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

	//******************AI*************************
	Menu_AI_Row = lv_obj_create(p);
    lv_obj_set_width(Menu_AI_Row, Row_wide);
    lv_obj_set_height(Menu_AI_Row, Row_High);
    lv_obj_set_y(Menu_AI_Row, 780);
    lv_obj_set_align(Menu_AI_Row, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_AI_Row, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_AI_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_AI_Row, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_color(Menu_AI_Row, lv_color_hex(0x4F4F4F), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_AI_Row, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_AI_Row, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明
    lv_obj_set_style_radius(Menu_AI_Row, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_AI_IconContain = lv_obj_create(Menu_AI_Row);  //用于容纳图标
    lv_obj_set_width(Menu_AI_IconContain, 50);
    lv_obj_set_height(Menu_AI_IconContain, 50);
    lv_obj_set_align(Menu_AI_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_AI_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_AI_IconContain, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_AI_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_AI_IconContain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_opa(Menu_AI_IconContain, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    Menu_AI_IconLabel = lv_label_create(Menu_AI_IconContain); //图标标签
    lv_obj_set_width(Menu_AI_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_AI_IconLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(Menu_AI_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_AI_IconLabel, LV_SYMBOL_MenuAI); //图标
    lv_obj_set_style_text_color(Menu_AI_IconLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_AI_IconLabel, &ui_icon_MenuAI30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_AI_TextLabel = lv_label_create(Menu_AI_Row); //文本显示
    lv_obj_set_width(Menu_AI_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(Menu_AI_TextLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(Menu_AI_TextLabel, 80);
    lv_obj_set_y(Menu_AI_TextLabel, 0);
    lv_obj_set_align(Menu_AI_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_AI_TextLabel, "A i");
    lv_obj_set_style_text_font(Menu_AI_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);



	//回滚
	lv_obj_scroll_to(ui_MenuPage,0,ui_MenuScrollY,LV_ANIM_OFF);

    /*Update the buttons position manually for first*/
    lv_event_send(ui_MenuPage, LV_EVENT_SCROLL, NULL);

    /*Be sure the fist button is in the middle*/
    lv_obj_scroll_to_view(lv_obj_get_child(ui_MenuPage, 0), LV_ANIM_OFF);


    //events
	lv_obj_add_event_cb(ui_MenuPage, ui_event_MenuPage, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(Menu_Calendar_Row, ui_event_MenuCalendarRow, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(Menu_HeartRate_Row, ui_event_MenuHeartRateRow, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(Menu_SpO2_Row, ui_event_MenuSpO2Row, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(Menu_Calculator_Row, ui_event_MenuCalculatorRow, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(Menu_Timer_Row, ui_event_MenuTimerRow, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(Menu_Compass_Row, ui_event_MenuCompassRow, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(Menu_Environment_Row, ui_event_MenuEnvRow, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(Menu_Game_Row, ui_event_MenuGameRow, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(Menu_Setting_Row, ui_event_MenuSetRow, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(Menu_AI_Row, ui_event_MenuAI, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(Menu_nfcCard_Row, ui_event_MenuNfcCard_Row, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(Menu_Motion_Row, ui_event_MenuMotionRow, LV_EVENT_CLICKED, NULL);


}

void ui_MenuPage_screen_deinit(void)
{
    uint8_t i = 0;
}
