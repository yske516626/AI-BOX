#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../include/UI_K_GamePage.h"
#include "../include/UI_L_2048Page.h"
#include "../../../Func/Include/FuncHWDataManage.h" 



/***********************************icon/img customize****************************************************************** */
#define LV_SYMBOL_2048   "\xEE\xA7\x92"


/***********************************Page definition****************************************************************** */

page_t Menu_Game = {ui_GamePage_screen_init, ui_GamePage_screen_deinit, &Menu_GamePage};




/***********************************obj****************************************************************** */
lv_obj_t* Menu_GamePage;

lv_obj_t*Menu_2048_ROW;
lv_obj_t* Menu_2048_IconContain;
lv_obj_t* Menu_2048_IconLabel;  
lv_obj_t* Menu_2048_TextLabel;

/***********************************event****************************************************************** */
void GamePage_Return_event_cb(lv_event_t* e)
{
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        Return_Pre_Page();
    }
    
}

void GamePage_2048_event_cb(lv_event_t* e)
{
    Load_New_Page(&GamePage_2048);
}

/***********************************page design****************************************************************** */
void ui_GamePage_screen_init(void)
{
    Menu_GamePage = lv_obj_create(NULL);

    //2048
    Menu_2048_ROW = lv_obj_create(Menu_GamePage);
    lv_obj_set_width(Menu_2048_ROW, 240);
    lv_obj_set_height(Menu_2048_ROW, 70);
    lv_obj_set_align(Menu_2048_ROW, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(Menu_2048_ROW, LV_OBJ_FLAG_SCROLLABLE);      //清除滚动状态
    lv_obj_set_style_radius(Menu_2048_ROW, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_2048_ROW, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT); //默认状态
    lv_obj_set_style_bg_opa(Menu_2048_ROW, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_2048_ROW, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_PRESSED); //按下时的状态
    lv_obj_set_style_bg_opa(Menu_2048_ROW, 100, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(Menu_2048_ROW, 0, LV_PART_MAIN | LV_STATE_DEFAULT); //边框设置为透明

    //图标
    lv_obj_t* Menu_2048_IconContain = lv_obj_create(Menu_2048_ROW);  //用于容纳图标
    lv_obj_set_width(Menu_2048_IconContain, 50);
    lv_obj_set_height(Menu_2048_IconContain, 50);
    lv_obj_set_align(Menu_2048_IconContain, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(Menu_2048_IconContain, 25, LV_PART_MAIN | LV_STATE_DEFAULT); //设置成圆的
    lv_obj_set_style_bg_color(Menu_2048_IconContain, lv_color_hex(0xFF8080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_2048_IconContain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_2048_IconContain, LV_OBJ_FLAG_SCROLLABLE);

    Menu_2048_IconLabel = lv_label_create(Menu_2048_IconContain); //图标标签
    lv_obj_set_width(Menu_2048_IconLabel, LV_SIZE_CONTENT);  
    lv_obj_set_height(Menu_2048_IconLabel, LV_SIZE_CONTENT);  
    lv_obj_set_align(Menu_2048_IconLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_2048_IconLabel, LV_SYMBOL_2048);
    lv_obj_set_style_text_font(Menu_2048_IconLabel, &ui_icon_GamePage30, LV_PART_MAIN | LV_STATE_DEFAULT);


    //文本
    Menu_2048_TextLabel = lv_label_create(Menu_2048_ROW); //文本显示：日历
    lv_obj_set_width(Menu_2048_TextLabel, LV_SIZE_CONTENT);   
    lv_obj_set_height(Menu_2048_TextLabel, LV_SIZE_CONTENT);    
    lv_obj_set_x(Menu_2048_TextLabel, 80);
    lv_obj_set_y(Menu_2048_TextLabel, 0);
    lv_obj_set_align(Menu_2048_TextLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(Menu_2048_TextLabel, "2048");
    lv_obj_set_style_text_font(Menu_2048_TextLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(Menu_GamePage, GamePage_Return_event_cb, LV_EVENT_GESTURE, NULL);

    lv_obj_add_event_cb(Menu_2048_ROW, GamePage_2048_event_cb, LV_EVENT_CLICKED, NULL);
    
}


void ui_GamePage_screen_deinit(void)
{

}




