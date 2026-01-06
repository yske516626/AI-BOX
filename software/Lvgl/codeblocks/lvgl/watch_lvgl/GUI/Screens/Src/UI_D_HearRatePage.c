#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../include/UI_D_HearRatePage.h"
#include "../../../Func/Include/FuncHWDataManage.h"


/***********************************icon/img customize****************************************************************** */
LV_IMG_DECLARE(ui_img_HeartRate);


/***********************************Page definition****************************************************************** */
page_t Menu_HeatRate = { Menu_HeartRatePage_screen_init,Menu_HeartRatePage_screen_deinit,&Menu_HeatRatePage };

/***********************************obj****************************************************************** */
lv_obj_t* Menu_HeatRatePage;
lv_obj_t* img_heart;
lv_obj_t* HRpage_HRNum_Label;  //心率值
lv_obj_t* HRpage_NumUnit_Label; //单位
lv_obj_t* HRpage_Measuring_Label;  //提示

lv_timer_t * Menu_HRPageTimer; //更新心率值


/***********************************event****************************************************************** */
void HRPage_timer_cb(lv_event_cb_t* e)
{
    uint8_t value_strbuf[6];
    sprintf(value_strbuf, "%d", HWInterface.HR_meter.HeartRate);
    lv_label_set_text(HRpage_HRNum_Label, value_strbuf);
}

void HeartRate_Return_Menu(lv_event_cb_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) //左滑回上一页
    {
        Return_Pre_Page();
    }
}


/***********************************page design****************************************************************** */
void Menu_HeartRatePage_screen_init(void)
{
    uint8_t value_strbuf[5];

    Menu_HeatRatePage = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(Menu_HeatRatePage, lv_color_hex(0xf8fcf8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Menu_HeatRatePage, LV_OBJ_FLAG_SCROLLABLE);
    

    ////////////////////////////心跳动画/////////////////////////////////
    //加载图片
    img_heart = lv_img_create(Menu_HeatRatePage);
    lv_img_set_src(img_heart, &ui_img_HeartRate);  // 设置图像源
    //lv_obj_set_y(img_heart, -50);
    lv_obj_align(img_heart, LV_ALIGN_CENTER,0,-80);

    // //设置动画，动画不建议全局，直接放在函数内，函数结束就会释放
    lv_anim_t anim_img_HeartRate;
    lv_anim_init(&anim_img_HeartRate);
    lv_anim_set_var(&anim_img_HeartRate, img_heart); //将动画应用到图片上
    lv_anim_set_exec_cb(&anim_img_HeartRate, (lv_anim_exec_xcb_t)lv_img_set_zoom); //设置动画效果：缩放效果
    lv_anim_set_time(&anim_img_HeartRate,500); //动画持续时间：1s放大
    lv_anim_set_values(&anim_img_HeartRate, 150, 200); 
    lv_anim_set_repeat_count(&anim_img_HeartRate, LV_ANIM_REPEAT_INFINITE); //无限重复
    lv_anim_set_playback_delay(&anim_img_HeartRate, 500); //延迟回放：停止0.5ms
    lv_anim_set_playback_time(&anim_img_HeartRate, 500); //回放时间：1s缩小

    lv_anim_set_path_cb(&anim_img_HeartRate, lv_anim_path_ease_out); //在动画中设置路径
    lv_anim_start(&anim_img_HeartRate);//动画开始

    ////////////////////////////心率值标签/////////////////////////////////
    HRpage_HRNum_Label = lv_label_create(Menu_HeatRatePage);
    lv_obj_set_width(HRpage_HRNum_Label, LV_SIZE_CONTENT);   
    lv_obj_set_height(HRpage_HRNum_Label, LV_SIZE_CONTENT);
    lv_obj_set_y(HRpage_HRNum_Label, 20);
    lv_obj_set_align(HRpage_HRNum_Label, LV_ALIGN_CENTER);
    sprintf(value_strbuf, "%d", HWInterface.HR_meter.HeartRate);
    lv_label_set_text(HRpage_HRNum_Label, value_strbuf);
    lv_obj_set_style_text_color(HRpage_HRNum_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(HRpage_HRNum_Label, &ui_font_Cuyuan80, LV_PART_MAIN | LV_STATE_DEFAULT);


    ////////////////////////////单位标签/////////////////////////////////
    HRpage_NumUnit_Label = lv_label_create(Menu_HeatRatePage);
    lv_obj_set_width(HRpage_NumUnit_Label, LV_SIZE_CONTENT);   
    lv_obj_set_height(HRpage_NumUnit_Label, LV_SIZE_CONTENT);    
    lv_obj_set_x(HRpage_NumUnit_Label, 90);
    lv_obj_set_y(HRpage_NumUnit_Label, 40);
    lv_obj_set_align(HRpage_NumUnit_Label, LV_ALIGN_CENTER);
    lv_label_set_text(HRpage_NumUnit_Label, "次/分");
    lv_obj_set_style_text_color(HRpage_NumUnit_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(HRpage_NumUnit_Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(HRpage_NumUnit_Label, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);


    ////////////////////////////提示标签/////////////////////////////////
    HRpage_Measuring_Label = lv_label_create(Menu_HeatRatePage);
    lv_obj_set_width(HRpage_Measuring_Label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(HRpage_Measuring_Label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(HRpage_Measuring_Label, 0);
    lv_obj_set_y(HRpage_Measuring_Label, 100);
    lv_obj_set_align(HRpage_Measuring_Label, LV_ALIGN_CENTER);
    lv_label_set_text(HRpage_Measuring_Label, "Update every 10 seconds");
    lv_obj_set_style_text_color(HRpage_Measuring_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(HRpage_Measuring_Label, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(HRpage_Measuring_Label, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);


    Menu_HRPageTimer = lv_timer_create(HRPage_timer_cb, 50,  NULL);
    lv_obj_add_event_cb(Menu_HeatRatePage, HeartRate_Return_Menu, LV_EVENT_GESTURE, NULL);


}

void Menu_HeartRatePage_screen_deinit(void)
{
    lv_timer_del(Menu_HRPageTimer);
}