/*
setting function achieve page
*/
#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../include/UI_O_SetFunAchPage.h"
#include "../../../Func/Include/FuncHWDataManage.h" 

/***********************************icon/img customize****************************************************************** */
#


/***********************************Page definition****************************************************************** */
page_t Setting_Bright = { Setting_BrightPage_screen_init,Setting_BrightPage_screen_deinit,&Setting_BrightPage };

page_t Setting_Hibernate = { Setting_HibernatePage_screen_init,Setting_HibernatePage_screen_deinit,&Setting_HibernatePage };






/***********************************obj****************************************************************** */
lv_obj_t * Setting_BrightPage;


lv_obj_t* Setting_HibernatePage;
lv_obj_t * Setting_HibernateRoller;
lv_obj_t * Setting_HibernateUnitLabel;
lv_obj_t * Setting_HibernateOKButton;
lv_obj_t * Setting_HibernateOKLabel;
lv_obj_t * Setting_Hibernateicon;




static lv_style_t style_radio;
static lv_style_t style_radio_chk;
static uint32_t active_index = 0;

/***********************************value****************************************************************** */
static uint8_t BrightTimes[] = { 10, 15, 20, 30, 45, 60 };
static uint8_t HibernateTimes[] = { 15,20,25,35,50,65 };

uint8_t BrightValue = 10;
uint8_t HibernateValue = 15;

uint8_t BrightSelected = 0;
uint8_t HibernateSelected = 0;

/***********************************event****************************************************************** */
void ReturnSetting_event_cb(lv_event_t* e)
{
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        Return_Pre_Page();
    }
}

void ReturnSetting_Hibernate_event_cb(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        HibernateSelected = lv_roller_get_selected(Setting_HibernateRoller);
        HibernateValue = HibernateTimes[HibernateSelected];
        Return_Pre_Page();
    }
}

static void radio_event_handler(lv_event_t * e)
{
    lv_obj_t * act_cb = lv_event_get_target(e); // 获取点击的 checkbox
    lv_obj_t * cont = lv_obj_get_parent(lv_obj_get_parent(act_cb)); // 获取 Setting_BrightPage（frame 的父容器）
    uint8_t * active_id = lv_event_get_user_data(e);

    // 清除所有 checkbox 的选中状态
    uint8_t i;
    for (i = 0; i < lv_obj_get_child_cnt(cont); i++) {
        lv_obj_t * frame = lv_obj_get_child(cont, i);
        lv_obj_t * cb = lv_obj_get_child(frame, 1); // 每个 frame 的第二个子对象是 checkbox
        lv_obj_clear_state(cb, LV_STATE_CHECKED);
    }

    // 设置当前 checkbox 为选中状态
    lv_obj_add_state(act_cb, LV_STATE_CHECKED);

    // 更新选中索引
    *active_id = lv_obj_get_index(lv_obj_get_parent(act_cb)); // frame 的索引

    //更新到全局变量存储起来
    BrightSelected = *active_id;  
    BrightValue = BrightTimes[BrightSelected];
    
    //printf("Selected screen timeout: %d seconds\n", BrightValue);
}




/***********************************page design****************************************************************** */


///////////////亮屏时间/////////////

static void radiobutton_create(lv_obj_t* parent, const char* txt)
{
    // 创建方框容器
    lv_obj_t* frame = lv_obj_create(parent);
    lv_obj_set_size(frame, 240, 50);
    lv_obj_set_align(frame, LV_ALIGN_CENTER);
    lv_obj_set_style_border_opa(frame, 0, LV_PART_MAIN); // 黑色边框
    lv_obj_set_style_bg_color(frame, lv_color_hex(0x7A7A7A), LV_PART_MAIN); 
    lv_obj_set_flex_flow(frame, LV_FLEX_FLOW_ROW); // 水平排列
    lv_obj_set_flex_align(frame, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 两端对齐

    // 创建左侧秒数标签
    lv_obj_t* label = lv_label_create(frame);
    lv_label_set_text(label, txt);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_14, LV_PART_MAIN); // 14 号字体
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN); 

    // 创建右侧单选按钮
    lv_obj_t* obj = lv_checkbox_create(frame);
    lv_checkbox_set_text(obj, ""); // 无文本，仅显示按钮
    lv_obj_add_style(obj, &style_radio, LV_PART_INDICATOR); // 未选中样式
    lv_obj_add_style(obj, &style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED); // 选中样式
    lv_obj_add_event_cb(obj, radio_event_handler, LV_EVENT_CLICKED, &active_index); // 直接绑定事件到 checkbox}
}

void Setting_BrightPage_screen_init(void)
{ 

    lv_style_init(&style_radio);
    lv_style_set_radius(&style_radio, LV_RADIUS_CIRCLE);

    lv_style_init(&style_radio_chk);
    lv_style_set_bg_img_src(&style_radio_chk, NULL);
    // 创建页面容器
    Setting_BrightPage = lv_obj_create(NULL);
    lv_obj_set_y(Setting_BrightPage, 20);
    lv_obj_set_align(Setting_BrightPage, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(Setting_BrightPage, LV_FLEX_FLOW_COLUMN); // 垂直排列
    lv_obj_set_style_pad_row(Setting_BrightPage, 10, LV_PART_MAIN); // 方框间距 10 像素
    lv_obj_set_style_bg_color(Setting_BrightPage, lv_color_hex(0x000000), LV_PART_MAIN); 
    lv_obj_set_scrollbar_mode(Setting_BrightPage, LV_SCROLLBAR_MODE_OFF); // 隐藏滚动条

    // 定义秒数选项
    static const char * times[] = {"10s", "15s", "20s", "30s", "45s", "60s"};
    uint32_t i;
    for (i = 0; i < 6; i++) {
        radiobutton_create(Setting_BrightPage, times[i]);
    }

    // 默认勾选
    lv_obj_t * frame = lv_obj_get_child(Setting_BrightPage, BrightSelected); //父对象的第x个子对象
    lv_obj_t * cb = lv_obj_get_child(frame, 1); //该子对象下的第二个子对象就是button
    lv_obj_add_state(cb, LV_STATE_CHECKED);

    lv_obj_add_event_cb(Setting_BrightPage, ReturnSetting_event_cb, LV_EVENT_GESTURE, NULL);
    
}

void Setting_BrightPage_screen_deinit(void)
{
}



//////////////设备开始停止工作时间/////////////
void Setting_HibernatePage_screen_init(void)
{
    Setting_HibernatePage = lv_obj_create(NULL);
    lv_obj_clear_flag(Setting_HibernatePage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    Setting_HibernateRoller = lv_roller_create(Setting_HibernatePage);
    lv_roller_set_options(Setting_HibernateRoller, "15\n20\n25\n35\n50\n65", LV_ROLLER_MODE_NORMAL);
    lv_roller_set_selected(Setting_HibernateRoller,HibernateSelected,LV_ANIM_OFF);
    lv_obj_set_height(Setting_HibernateRoller, 150);
    lv_obj_set_width(Setting_HibernateRoller, LV_SIZE_CONTENT);   /// 0
    lv_obj_set_align(Setting_HibernateRoller, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(Setting_HibernateRoller, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(Setting_HibernateRoller, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Setting_HibernateRoller, &ui_font_Cuyuan38, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Setting_HibernateRoller, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Setting_HibernateRoller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(Setting_HibernateRoller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(Setting_HibernateRoller, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(Setting_HibernateRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Setting_HibernateRoller, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Setting_HibernateRoller, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(Setting_HibernateRoller, lv_color_hex(0x0064FF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(Setting_HibernateRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(Setting_HibernateRoller, 2, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(Setting_HibernateRoller, 1, LV_PART_SELECTED | LV_STATE_DEFAULT);

    Setting_HibernateUnitLabel = lv_label_create(Setting_HibernatePage);
    lv_obj_set_width(Setting_HibernateUnitLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(Setting_HibernateUnitLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(Setting_HibernateUnitLabel, 60);
    lv_obj_set_y(Setting_HibernateUnitLabel, 0);
    lv_obj_set_align(Setting_HibernateUnitLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Setting_HibernateUnitLabel, "秒");
    lv_obj_set_style_text_font(Setting_HibernateUnitLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

    Setting_HibernateOKButton = lv_btn_create(Setting_HibernatePage);
    lv_obj_set_width(Setting_HibernateOKButton, 240);
    lv_obj_set_height(Setting_HibernateOKButton, 50);
    lv_obj_set_align(Setting_HibernateOKButton, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(Setting_HibernateOKButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(Setting_HibernateOKButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(Setting_HibernateOKButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Setting_HibernateOKButton, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Setting_HibernateOKButton, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Setting_HibernateOKButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(Setting_HibernateOKButton, 128, LV_PART_MAIN | LV_STATE_PRESSED);

    Setting_HibernateOKLabel = lv_label_create(Setting_HibernateOKButton);
    lv_obj_set_width(Setting_HibernateOKLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(Setting_HibernateOKLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(Setting_HibernateOKLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Setting_HibernateOKLabel, LV_SYMBOL_ok);
    lv_obj_set_style_text_font(Setting_HibernateOKLabel, &ui_icon_MenuOderPage34, LV_PART_MAIN | LV_STATE_DEFAULT);
    

    lv_obj_add_event_cb(Setting_HibernateOKButton, ReturnSetting_Hibernate_event_cb, LV_EVENT_ALL, NULL);
}

void Setting_HibernatePage_screen_deinit(void)
{

}


