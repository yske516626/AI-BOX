#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../include/UI_E_SPO2page.h"
#include "../../../Func/Include/FuncHWDataManage.h"


/***********************************icon/img customize****************************************************************** */
LV_FONT_DECLARE(ui_icon_MenuBloodOxygen80);
#define LV_SYMBOL_MenuSpo2Icon "\xEE\x99\xBF" 




/***********************************Page definition****************************************************************** */
page_t Menu_SPO2 = {Menu_SPO2Page_screen_init, Menu_SPO2Page_screen_deinit, &Menu_SPO2Page};



/***********************************obj****************************************************************** */

lv_obj_t* Menu_SPO2Page;
lv_obj_t* SPO2page_icon_SPO2; 
lv_obj_t* SPO2page_SPO2Num_Label;  //值
lv_obj_t* SPO2page_NumUnit_Label; //单位
lv_obj_t* SPO2page_Measuring_Label;  //提示

lv_timer_t * Menu_SPO2PageTimer; //更新值


/***********************************event****************************************************************** */

void SPO2Page_timer_cb(lv_event_cb_t* e)
{
    uint8_t value_strbuf[6];
    sprintf(value_strbuf, "%d", HWInterface.HR_meter.SPO2);
    lv_label_set_text(SPO2page_SPO2Num_Label, value_strbuf);
}

void SPO2_Return_Menu(lv_event_cb_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) //左滑回上一页
    {
        Return_Pre_Page();
    }
}


/***********************************page design****************************************************************** */
void Menu_SPO2Page_screen_init(void)
{
    uint8_t value_strbuf[5];

    Menu_SPO2Page = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(Menu_SPO2Page, lv_color_hex(0xf8fcf8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_SPO2Page, LV_OBJ_FLAG_SCROLLABLE);
    

    ///////////////////////////图标显示/////////////////////////////////
    SPO2page_icon_SPO2 = lv_label_create(Menu_SPO2Page);
    lv_obj_set_width(SPO2page_icon_SPO2, LV_SIZE_CONTENT);   
    lv_obj_set_height(SPO2page_icon_SPO2, LV_SIZE_CONTENT);
    lv_obj_align(SPO2page_icon_SPO2, LV_ALIGN_CENTER, 0, -80);
    //lv_obj_set_align(SPO2page_icon_SPO2, LV_ALIGN_CENTER);
    lv_label_set_text(SPO2page_icon_SPO2, LV_SYMBOL_MenuSpo2Icon);
    //lv_obj_set_style_text_color(SPO2page_icon_SPO2, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(SPO2page_icon_SPO2, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(SPO2page_icon_SPO2, &ui_icon_MenuBloodOxygen80, LV_PART_MAIN | LV_STATE_DEFAULT);

    
    ////////////////////////////心率值标签/////////////////////////////////
    SPO2page_SPO2Num_Label = lv_label_create(Menu_SPO2Page);
    lv_obj_set_width(SPO2page_SPO2Num_Label, LV_SIZE_CONTENT);   
    lv_obj_set_height(SPO2page_SPO2Num_Label, LV_SIZE_CONTENT);
    lv_obj_set_y(SPO2page_SPO2Num_Label, 20);
    lv_obj_set_align(SPO2page_SPO2Num_Label, LV_ALIGN_CENTER);
    sprintf(value_strbuf, "%d", HWInterface.HR_meter.SPO2);
    lv_label_set_text(SPO2page_SPO2Num_Label, value_strbuf);
    lv_obj_set_style_text_color(SPO2page_SPO2Num_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(SPO2page_SPO2Num_Label, &ui_font_Cuyuan80, LV_PART_MAIN | LV_STATE_DEFAULT);


    ////////////////////////////单位标签/////////////////////////////////
    SPO2page_NumUnit_Label = lv_label_create(Menu_SPO2Page);
    lv_obj_set_width(SPO2page_NumUnit_Label, LV_SIZE_CONTENT);   
    lv_obj_set_height(SPO2page_NumUnit_Label, LV_SIZE_CONTENT);    
    lv_obj_set_x(SPO2page_NumUnit_Label, 90);
    lv_obj_set_y(SPO2page_NumUnit_Label, 40);
    lv_obj_set_align(SPO2page_NumUnit_Label, LV_ALIGN_CENTER);
    lv_label_set_text(SPO2page_NumUnit_Label, "%");
    lv_obj_set_style_text_color(SPO2page_NumUnit_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(SPO2page_NumUnit_Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(SPO2page_NumUnit_Label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);


    ////////////////////////////提示标签/////////////////////////////////
    SPO2page_Measuring_Label = lv_label_create(Menu_SPO2Page);
    lv_obj_set_width(SPO2page_Measuring_Label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(SPO2page_Measuring_Label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(SPO2page_Measuring_Label, 0);
    lv_obj_set_y(SPO2page_Measuring_Label, 100);
    lv_obj_set_align(SPO2page_Measuring_Label, LV_ALIGN_CENTER);
    lv_label_set_text(SPO2page_Measuring_Label, "Update every 10 seconds");
    lv_obj_set_style_text_color(SPO2page_Measuring_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(SPO2page_Measuring_Label, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(SPO2page_Measuring_Label, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);


    Menu_SPO2PageTimer = lv_timer_create(SPO2Page_timer_cb, 50,  NULL);
    lv_obj_add_event_cb(Menu_SPO2Page, SPO2_Return_Menu, LV_EVENT_GESTURE, NULL);


}

void Menu_SPO2Page_screen_deinit(void)
{
    lv_timer_del(Menu_SPO2PageTimer);

}