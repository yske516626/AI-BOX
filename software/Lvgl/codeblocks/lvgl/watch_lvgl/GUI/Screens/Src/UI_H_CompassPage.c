#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../include/UI_H_CompassPage.h"
#include "../../../Func/Include/FuncHWDataManage.h"

/***********************************icon/img customize****************************************************************** */
LV_IMG_DECLARE(ui_img_compass_needle_png);

#define LV_SYMBOL_POINTER "\xEE\x98\x81"
#define LV_SYMBOL_ALTITUDE "\xEE\x98\x80"

/***********************************Page definition****************************************************************** */
page_t Menu_Compass = { Menu_CompassPage_screen_init,Menu_CompassPage_screen_deinit,&Menu_CompassPage };



/***********************************obj****************************************************************** */

lv_obj_t* Menu_CompassPage;
lv_obj_t* CompassPage_Meter;
lv_obj_t* CompassPage_pointer;  //img

lv_obj_t* CompassPage_Dir; //方向容器
lv_obj_t* CompassPage_DirLabel;//方向数值显示
lv_obj_t* CompassPage_DirIcon; //方向指针图标

lv_obj_t* CompassPage_Altitude; //海拔容纳
lv_obj_t* CompassPage_AltitudeLabel;
lv_obj_t* CompassPage_AltitudeIcon;

lv_timer_t* CompassPage_Timer;
/***********************************event****************************************************************** */

static void CompassPage_timer_cb(lv_timer_t * timer)
{
    int value_strbuf[6];

    lv_img_set_angle(CompassPage_pointer, HWInterface.Ecompass.direction * 10);  //根据获取的方向值让图像选装
    sprintf(value_strbuf,":%d", HWInterface.Ecompass.direction);
    lv_label_set_text(CompassPage_DirLabel, value_strbuf);

    //set text
    sprintf(value_strbuf,":%dm", HWInterface.Barometer.altitude);
    lv_label_set_text(CompassPage_AltitudeLabel, value_strbuf);

}

void CompassPage_Return_Menu(lv_event_t* e)
{
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) //左滑回上一页
    {
        Return_Pre_Page();
    }

}

/***********************************page design****************************************************************** */
void Menu_CompassPage_screen_init(void)
{

    uint8_t value_strbuf[10];

    Menu_CompassPage = lv_obj_create(NULL);
    //lv_obj_clear_flag(Menu_CompassPage, LV_OBJ_FLAG_SCROLLABLE);

    //创建刻度盘
    CompassPage_Meter = lv_meter_create(Menu_CompassPage);
    lv_obj_set_size(CompassPage_Meter, 230, 230);
    lv_obj_center(CompassPage_Meter);
    lv_obj_set_pos(CompassPage_Meter,0,-20);

    //设置次要刻度线
    lv_meter_scale_t* scale_360 = lv_meter_add_scale(CompassPage_Meter);
    lv_meter_set_scale_ticks(CompassPage_Meter, scale_360, 61, 1, 10, lv_palette_main(LV_PALETTE_GREY));
    //设置次要刻度线第一根对应的最小值和最后一根的最大值，设置61根刻度线所要覆盖的角度范围，设置刻度盘的初始旋转角度
    lv_meter_set_scale_range(CompassPage_Meter, scale_360, 0, 360, 360, 270);

    //设置主要刻度线
    lv_meter_scale_t* scale_12 = lv_meter_add_scale(CompassPage_Meter);
    lv_meter_set_scale_ticks(CompassPage_Meter, scale_12, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(CompassPage_Meter, scale_12, 1, 2, 15, lv_color_white(), 15);
    //30一主要刻度线，因此第一根刻度线对应值0，最后一根对应330（值取决于次要刻度线：0-360，可以认为主要刻度线覆盖在上面）
    //330：12根刻度线从第1根到第12根覆盖的角度为330，第一根刻度线起始位置为0点钟方向(默认起始位置是从3点钟开始的，因此旋转270)
    lv_meter_set_scale_range(CompassPage_Meter, scale_12, 0, 330, 330, 270);


    //方向指针
    CompassPage_pointer = lv_img_create(CompassPage_Meter);
    lv_img_set_src(CompassPage_pointer, &ui_img_compass_needle_png);
    lv_obj_set_width(CompassPage_pointer, LV_SIZE_CONTENT);
    lv_obj_set_height(CompassPage_pointer, LV_SIZE_CONTENT);
    lv_obj_set_align(CompassPage_pointer, LV_ALIGN_CENTER);
    lv_obj_add_flag(CompassPage_pointer, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(CompassPage_pointer, LV_OBJ_FLAG_SCROLLABLE);
    lv_img_set_angle(CompassPage_pointer, HWInterface.Ecompass.direction * 10);

    //方向数值
    CompassPage_Dir = lv_obj_create(Menu_CompassPage);
    lv_obj_set_size(CompassPage_Dir, 80, 30);
    lv_obj_align_to(CompassPage_Dir, Menu_CompassPage, LV_ALIGN_BOTTOM_MID, -60, -10);
    lv_obj_add_flag(CompassPage_Dir, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_set_style_radius(CompassPage_Dir, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(CompassPage_Dir, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);

    CompassPage_DirIcon = lv_label_create(CompassPage_Dir);
    lv_obj_set_align(CompassPage_DirIcon,LV_ALIGN_LEFT_MID);
    lv_obj_set_pos(CompassPage_DirIcon,-10,0);
    lv_label_set_text(CompassPage_DirIcon, LV_SYMBOL_POINTER);
    lv_obj_set_style_text_font(CompassPage_DirIcon, &ui_icon_CompassEnv_Page28, LV_PART_MAIN | LV_STATE_DEFAULT);

    CompassPage_DirLabel = lv_label_create(CompassPage_Dir);
    lv_obj_set_align(CompassPage_DirLabel,LV_ALIGN_LEFT_MID);
    lv_obj_set_pos(CompassPage_DirLabel,17,0);
    sprintf(value_strbuf,":%d", HWInterface.Ecompass.direction);
    //sprintf(value_strbuf,":%d", 360);
    lv_label_set_text(CompassPage_DirLabel, value_strbuf);
    lv_obj_set_style_text_font(CompassPage_DirLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //海拔数值
    CompassPage_Altitude = lv_obj_create(Menu_CompassPage);
    lv_obj_set_size(CompassPage_Altitude, 100, 30);
    lv_obj_align_to(CompassPage_Altitude, Menu_CompassPage, LV_ALIGN_BOTTOM_MID, 60, -10);
    lv_obj_add_flag(CompassPage_Altitude, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_set_style_radius(CompassPage_Altitude, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(CompassPage_Altitude, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);

    CompassPage_AltitudeIcon = lv_label_create(CompassPage_Altitude);
    lv_obj_set_align(CompassPage_AltitudeIcon,LV_ALIGN_LEFT_MID);
    lv_obj_set_pos(CompassPage_AltitudeIcon,-10,0);
    lv_label_set_text(CompassPage_AltitudeIcon, LV_SYMBOL_ALTITUDE);
    lv_obj_set_style_text_font(CompassPage_AltitudeIcon, &ui_icon_CompassEnv_Page28, LV_PART_MAIN | LV_STATE_DEFAULT);

    CompassPage_AltitudeLabel = lv_label_create(CompassPage_Altitude);
    lv_obj_set_align(CompassPage_AltitudeLabel,LV_ALIGN_LEFT_MID);
    lv_obj_set_pos(CompassPage_AltitudeLabel,17,0);
    sprintf(value_strbuf,":%dm", HWInterface.Barometer.altitude); //海拔
    //sprintf(value_strbuf,":%d", 360);
    lv_label_set_text(CompassPage_AltitudeLabel, value_strbuf);
    lv_obj_set_style_text_font(CompassPage_AltitudeLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //事件
    lv_obj_add_event_cb(Menu_CompassPage, CompassPage_Return_Menu,LV_EVENT_GESTURE, NULL);
    CompassPage_Timer = lv_timer_create(CompassPage_timer_cb, 500, NULL);

}

void Menu_CompassPage_screen_deinit(void)
{
    lv_timer_del(CompassPage_Timer);
}
