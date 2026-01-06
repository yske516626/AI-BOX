#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../include/UI_G_Timerpage.h"
#include "../../../Func/Include/FuncHWDataManage.h"

/**
 *定时器的实现，需要利用freertos系统的tick中断，在tick中断的钩子函数中去更新时间数
 */


 /***********************************icon/img customize****************************************************************** */
#define LV_SYMBOL_START "\xEE\x98\xA4"
#define LV_SYMBOL_RE "\xEE\x98\x80"
 /***********************************Page definition****************************************************************** */
page_t Menu_Timer = { Menu_TiemrPage_screen_init,Menu_TiemrPage_screen_deinit,&Menu_TimerPage };


 /***********************************obj****************************************************************** */
lv_obj_t* Menu_TimerPage;

lv_obj_t* TimerPage_Meter;
lv_obj_t* TimerPage_StartBtn; //开始按键
lv_obj_t* TimerPage_StartLabel;
lv_obj_t* TimerPage_RestBtn; //重新开始按键
lv_obj_t* TimerPage_ResLabel;

lv_timer_t* TimerPage_Timer;

//数值标签
lv_obj_t* TimerPage_MinLabel; //分钟
lv_obj_t* TimerPage_ColonLabel; //:
lv_obj_t* TimerPage_SecondLabel; //秒
lv_obj_t* TimerPage_DropLabel;  //.
lv_obj_t* TimerPage_MillLabel; //毫秒

//数值存储，交由tick中断的钩子函数更新数值，10ms更新一次
uint8_t TimerPage_Flag; //是否启动了定时器
uint8_t TimerPage_Min = 0; //分钟数值
uint8_t TimerPage_Sec = 0; //秒
uint8_t TimerPage_10ms = 0; //毫秒只显示十、百、千位数
uint8_t TimerPage_ms = 0; //10ms记一次


 /***********************************event****************************************************************** */
void TimerPage_Return_Menu(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) //左滑回上一页
    {
        Return_Pre_Page();
    }
}

void TimerPage_StartBtn_eventcb(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        //checked
        TimerPage_Flag = 1;
        //lv_label_set_text(TimerPage_StartLabel, LV_SYMBOL_PAUSE);  //更换成暂定图标
        lv_timer_resume(TimerPage_Timer); 

    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        //released
        TimerPage_Flag = 0;
        lv_label_set_text(TimerPage_StartLabel, LV_SYMBOL_PLAY);
        lv_timer_pause(TimerPage_Timer);

    }


}

void TimerPage_ResBtn_eventcb(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED && !lv_obj_has_state(TimerPage_StartBtn, LV_STATE_CHECKED))
    {
        //clear
        lv_timer_pause(TimerPage_Timer);
        lv_label_set_text(TimerPage_MinLabel, "00");
        lv_label_set_text(TimerPage_SecondLabel, "00");
        lv_label_set_text(TimerPage_MillLabel, "00");
        TimerPage_Min = 0;
        TimerPage_Sec = 0;
		TimerPage_10ms = 0;
        TimerPage_ms = 0;

    }

}

static void LabelRefresh_timer(lv_timer_t * timer)
{
    uint8_t strbuf[2];

    sprintf(strbuf,"%02d",TimerPage_Min);
    lv_label_set_text(TimerPage_MinLabel, strbuf);
    sprintf(strbuf,"%02d",TimerPage_Sec);
    lv_label_set_text(TimerPage_SecondLabel, strbuf);
    sprintf(strbuf,"%02d",TimerPage_10ms);
    lv_label_set_text(TimerPage_MillLabel, strbuf);


}

 /***********************************page design****************************************************************** */

 void Menu_TiemrPage_screen_init(void)
 {
     TimerPage_Flag = 0;
     TimerPage_Min = 0;
     TimerPage_Sec = 0;
     TimerPage_10ms = 0;
     TimerPage_ms = 0;

     Menu_TimerPage = lv_obj_create(NULL);
     lv_obj_clear_flag(Menu_TimerPage, LV_OBJ_FLAG_SCROLLABLE);

     TimerPage_Meter = lv_meter_create(Menu_TimerPage); //创建记时表盘
     lv_obj_set_size(TimerPage_Meter, 240, 240);  
     lv_obj_center(TimerPage_Meter); //居中
     lv_obj_remove_style(TimerPage_Meter, NULL, LV_PART_INDICATOR); ///移除指示器样式
     lv_meter_scale_t* scale_min = lv_meter_add_scale(TimerPage_Meter); //添加刻度
     //设置次要刻度线，次要刻度线的总数为61，线宽为1，线线长为10
     lv_meter_set_scale_ticks(TimerPage_Meter, scale_min, 61, 1, 10, lv_palette_main(LV_PALETTE_BLUE));
     //1/60：刻度的最小值和最大值（计时器0-60）；61根刻度线覆盖的角度范围为360；270：在9点钟位置的角度偏移（顺时钟），起始位置是在6点钟；
     lv_meter_set_scale_range(TimerPage_Meter, scale_min, 0, 60, 360, 270); //设置刻度标尺的值和角度范围

     //开始计时按钮
     TimerPage_StartBtn = lv_btn_create(Menu_TimerPage);
     lv_obj_set_size(TimerPage_StartBtn, 60, 60);
     lv_obj_set_style_radius(TimerPage_StartBtn, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_align(TimerPage_StartBtn, LV_ALIGN_CENTER);
     lv_obj_set_pos(TimerPage_StartBtn, 40, 50);
     lv_obj_add_flag(TimerPage_StartBtn, LV_OBJ_FLAG_CHECKABLE |LV_OBJ_FLAG_SCROLL_ON_FOCUS);  //添加这个有切换效果
     lv_obj_clear_flag(TimerPage_StartBtn, LV_OBJ_FLAG_SCROLLABLE);

     TimerPage_StartLabel = lv_label_create(TimerPage_StartBtn);
     lv_obj_set_align(TimerPage_StartLabel, LV_ALIGN_CENTER);
     lv_label_set_text(TimerPage_StartLabel, LV_SYMBOL_START); 
     lv_obj_set_style_text_font(TimerPage_StartLabel, &ui_icon_TimerPage24, LV_PART_MAIN | LV_STATE_DEFAULT);



     //复位按钮
     TimerPage_RestBtn = lv_btn_create(Menu_TimerPage);
     lv_obj_set_size(TimerPage_RestBtn, 60, 60);
     lv_obj_set_style_radius(TimerPage_RestBtn, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_align(TimerPage_RestBtn, LV_ALIGN_CENTER);
     lv_obj_set_pos(TimerPage_RestBtn, -40, 50);
     lv_obj_clear_flag(TimerPage_RestBtn, LV_OBJ_FLAG_SCROLLABLE);     

     TimerPage_StartLabel = lv_label_create(TimerPage_RestBtn);
     lv_obj_set_align(TimerPage_StartLabel, LV_ALIGN_CENTER);
     lv_label_set_text(TimerPage_StartLabel, LV_SYMBOL_RE); 
     lv_obj_set_style_text_font(TimerPage_StartLabel, &ui_icon_TimerPage24, LV_PART_MAIN | LV_STATE_DEFAULT);


     //数值标签显示
     TimerPage_MinLabel = lv_label_create(TimerPage_Meter);
     lv_obj_set_align(TimerPage_MinLabel, LV_ALIGN_CENTER);
     lv_obj_set_pos(TimerPage_MinLabel, -60, -20);
     lv_label_set_text(TimerPage_MinLabel, "00");
     lv_obj_set_style_text_font(TimerPage_MinLabel, &ui_font_Cuyuan38, LV_PART_MAIN | LV_STATE_DEFAULT);

     TimerPage_ColonLabel = lv_label_create(TimerPage_Meter);
     lv_obj_set_align(TimerPage_ColonLabel, LV_ALIGN_CENTER);
     lv_obj_set_pos(TimerPage_ColonLabel, -30, -20);
     lv_label_set_text(TimerPage_ColonLabel, ":");
     lv_obj_set_style_text_font(TimerPage_ColonLabel, &ui_font_Cuyuan38, LV_PART_MAIN | LV_STATE_DEFAULT);

     TimerPage_SecondLabel = lv_label_create(TimerPage_Meter);
     lv_obj_set_align(TimerPage_SecondLabel, LV_ALIGN_CENTER);
     lv_obj_set_pos(TimerPage_SecondLabel, 0, -20);
     lv_label_set_text(TimerPage_SecondLabel, "00");
     lv_obj_set_style_text_font(TimerPage_SecondLabel, &ui_font_Cuyuan38, LV_PART_MAIN | LV_STATE_DEFAULT);

     TimerPage_DropLabel = lv_label_create(TimerPage_Meter);
     lv_obj_set_align(TimerPage_DropLabel, LV_ALIGN_CENTER);
     lv_obj_set_pos(TimerPage_DropLabel, 30, -20);
     lv_label_set_text(TimerPage_DropLabel, ".");
     lv_obj_set_style_text_font(TimerPage_DropLabel, &ui_font_Cuyuan38, LV_PART_MAIN | LV_STATE_DEFAULT);

     TimerPage_MillLabel = lv_label_create(TimerPage_Meter);  //毫秒只显示十位数以上
     lv_obj_set_align(TimerPage_MillLabel, LV_ALIGN_CENTER);
     lv_obj_set_pos(TimerPage_MillLabel, 60, -20);
     lv_label_set_text(TimerPage_MillLabel, "00");
     lv_obj_set_style_text_font(TimerPage_MillLabel, &ui_font_Cuyuan38, LV_PART_MAIN | LV_STATE_DEFAULT);


     //事件
     lv_obj_add_event_cb(TimerPage_StartBtn, TimerPage_StartBtn_eventcb, LV_EVENT_ALL, NULL);
     lv_obj_add_event_cb(TimerPage_RestBtn, TimerPage_ResBtn_eventcb, LV_EVENT_ALL, NULL);
     lv_obj_add_event_cb(Menu_TimerPage, TimerPage_Return_Menu, LV_EVENT_GESTURE, NULL);

     //刷新数据
     TimerPage_Timer = lv_timer_create(LabelRefresh_timer, 10, NULL);
     lv_timer_pause(TimerPage_Timer);

 }

 void Menu_TiemrPage_screen_deinit(void)
 {
     
 }