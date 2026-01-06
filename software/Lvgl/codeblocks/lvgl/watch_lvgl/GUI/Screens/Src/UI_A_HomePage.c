#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../Include/UI_A_HomePage.h"
#include "../Include/UI_B_MenuPage.h"

#include "../../../Func/Include/FuncHWDataManage.h"

/***********************************icon customize****************************************************************** */
#define LV_SYMBOL_Moon "\xEE\x9B\x82" 
#define LV_SYMBOL_Day  "\xEE\x98\xAE"
#define LV_SYMBOL_Foot  "\xEE\x9C\xA0"   //步数图标：ui_icon_HomePage32
#define LV_SYMBOL_Heat  "\xEE\x9B\x88"   //心图标:ui_icon_HomePage32
#define LV_SYMBOL_Celsius   "\xEE\xBB\x82"  //摄氏度图标:ui_icon_Celsius24
#define LV_SYMBOL_Date   "\xEE\xA6\xAB"  //日期图标:ui_icon_Date32
#define LV_SYMBOL_NFC   "\xEE\xBC\x8D"  //NFC图标
#define LV_SYMBOL_BLUE "\xEE\x99\x9F"
#define LV_SYMBOL_SHUTDOWN  "\xEE\xA3\x98"
#define LV_SYMBOL_SETTING  "\xEE\x99\x83"

LV_IMG_DECLARE(ui_img_home_page);
//////////////////////////////////////////////////////////////////////////
//home page definition
lv_obj_t* ui_HomePage;
lv_obj_t* ui_PowerPage;

//Temperature_design:
lv_obj_t* Home_Temp_Contain;  //主：温度设计容纳
lv_style_t style_Temp;

lv_obj_t* Day_Or_Night;  //次1：白天 or 夜晚容纳
lv_style_t style_Day_Or_Night; //次1样式
lv_obj_t* DayNight_Label;  //次1-1：白天 or 夜晚标签图标显示

lv_obj_t* Tem_Num_Label;  // 次2：温度数值显示
lv_obj_t* Celsius_Label; // 次2：摄氏度图标显示

uint8_t ui_TempValue = 10; //温度数值

//////////////////////////////////////////////////////////////////////////
//Time definition
lv_obj_t* Home_Time_Contain;  //主：时间设计容纳
lv_style_t style_Time;

lv_obj_t* ui_TimeHourLabel;   //小时标签
lv_obj_t * ui_TimeColonLabel;  //小时和分钟中间间隔符号
lv_obj_t * ui_TimeMinuteLabel; //分钟标签

lv_timer_t* ui_HomePageTimer;  //用于更新时间值

//Time definition num：
uint8_t ui_TimeHourValue = 11;
uint8_t ui_TimeMinuteValue = 59;
const char * ui_Days[7] = {"Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat.", "Sun."};
uint8_t ui_DateMonthValue = 11;
uint8_t ui_DateDayValue = 30;
uint8_t ui_DataWeekdayValue = 2;


////////////////////////////////////////////////////////////ee//////////////
//Date definition
lv_obj_t* Home_Date_Contain;
lv_style_t style_Date;

lv_obj_t* Date_icon_Label;
lv_obj_t* Date_Num_Label;



//////////////////////////////////////////////////////////////////////////
//Heart Rate Definition
lv_obj_t* Home_HeartRate_Contain;
lv_style_t style_HeartRate;

lv_obj_t* HeartRate_icon_Label; //心型图标
lv_obj_t* HeartRate_Num_Label;  //心率显示

uint8_t ui_HeartRate_Num = 150;  //心率值存储

//////////////////////////////////////////////////////////////////////////
//步数设计
lv_obj_t* Home_Foots_Contain;
lv_style_t style_Foots;

lv_obj_t* Home_Foots_icon_Contain; //建立在Home_Foots_Contain上
lv_style_t style_Foots_icon_Contain;

lv_obj_t* Foots_icon_Label; //步数图标标签
lv_obj_t* Foots_Num_Label;  //步数显示

uint32_t Foots_Num = 2000;

//////////////////////////////////////////////////////////////////////////
//上滑控制中心页设计
lv_obj_t* Home_Setting_Contain;

lv_obj_t* Setting_NFCButton; 
lv_obj_t* NFCIcon;

lv_obj_t* Setting_BLEButton;
lv_obj_t* BLEIcon;

lv_obj_t* Setting_ShutdownButton;
lv_obj_t* ShutdownIcon;

lv_obj_t* Setting_SetButton;
lv_obj_t* SetIcon;

lv_obj_t* Setting_LightSlider;
lv_obj_t* LightIcon;

uint8_t LightSlider_Num = 50;
//////////////////////////////////////////////////////////////////////////
//关节界面
lv_obj_t* PowerSlider;
lv_obj_t* PowerLabel;

/***********************************variables definition****************************************************************** */

uint8_t ui_HomePage_NFCButton_EN = 0; //0：不启用nfc
uint8_t ui_HomePage_BLEButton_EN = 0;  //蓝牙

/***********************************Page definition****************************************************************** */
page_t Page_Home = { ui_HomePage_screen_init, ui_HomePage_screen_deinit, &ui_HomePage };

page_t Page_power = {ui_PowerPage_screen_init, ui_PowerPage_screen_deinit, &ui_PowerPage};



/***********************************event callback****************************************************************** */
//实时更新页面数据，利用lvgl的定时器触发回调函数
//关于数据的实时更新，交由freertos中创建专门的传感器任务来让传感器实时工作并将数据更新
//一旦检测到获取的新的传感器数据和记录数据的变量就更新
static void HomePage_timer_cb(lv_timer_t* timer)
{
    uint8_t value_strbuf[10];
    if (Get_Top_Page()->page_obj == &ui_HomePage)
    {
        /*
        lv_obj_set_style_text_opa(ui_TimeColonLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        osDelay(500);
        lv_obj_set_style_text_opa(ui_TimeColonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        */

        HW_DateTimeTypeDef DateTime;//利用RCT获取时间
        HWInterface.RealTimeClock.GetTimeDate(&DateTime);

        //更行当前几时几分
        if (ui_TimeHourValue != DateTime.Hours)
        {
            ui_TimeHourValue = DateTime.Hours;
            sprintf(value_strbuf, "%2d", ui_TimeHourValue);
            lv_label_set_text(ui_TimeHourLabel, value_strbuf);
        }
        if (ui_TimeMinuteValue != DateTime.Minutes)
        {
            ui_TimeMinuteValue = DateTime.Minutes;
            sprintf(value_strbuf, "%2d", ui_TimeMinuteValue);
            lv_label_set_text(ui_TimeMinuteLabel, value_strbuf);

        }

        //更新当前几号
        if (ui_DateDayValue != DateTime.Date)
        {
            ui_DateDayValue = DateTime.Date;
            ui_DataWeekdayValue = DateTime.WeekDay;
            sprintf(value_strbuf, "%2d", ui_DateDayValue);
            lv_label_set_text(Date_Num_Label, value_strbuf);

        }
        

        //更新当前温度、白天/晚上图标
        if (ui_TempValue != (int8_t)HWInterface.AHT21.temperature)
        {
            ui_TempValue = (int8_t)HWInterface.AHT21.temperature;
            sprintf(value_strbuf, "%d", ui_TempValue);
            lv_label_set_text(Tem_Num_Label, value_strbuf);
        }
        if ((ui_TimeHourValue >= 6) && (ui_TimeHourValue <= 18))
        {
            lv_label_set_text(DayNight_Label, LV_SYMBOL_Day);
        }else 
        {
            lv_label_set_text(DayNight_Label, LV_SYMBOL_Moon);
        }
        
        //更新心率值：
        if (ui_HeartRate_Num != HWInterface.HR_meter.HeartRate)
        {
            ui_HeartRate_Num = HWInterface.HR_meter.HeartRate;
            sprintf(value_strbuf, "%d", ui_HeartRate_Num);
            lv_label_set_text(HeartRate_Num_Label, value_strbuf);
        }

        //更新当前步数
        if (Foots_Num != HWInterface.Motion.Steps)
        {
            Foots_Num = HWInterface.Motion.Steps;
            sprintf(value_strbuf, "%d", Foots_Num);
            lv_label_set_text(Foots_Num_Label, value_strbuf);
        }

    }
}


static void anim_y_cb(void* var, int32_t v) {
    lv_obj_t* obj = (lv_obj_t*)var;
    lv_obj_set_y(obj, v);
}
//主界面，上滑显示设置中心，下滑回去，右滑进入菜单
void ui_event_HomePage(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_anim_t a;//动画
    //A gesture is detected. Get the gesture with lv_indev_get_gesture_dir(lv_indev_get_act());
    if (code == LV_EVENT_GESTURE) {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir == LV_DIR_TOP) {  //上滑，显示，过度动画设计
            lv_anim_init(&a);
            lv_anim_set_var(&a, Home_Setting_Contain);
            lv_anim_set_exec_cb(&a, anim_y_cb);
            //设置页面y轴数：280 -- 到屏幕顶y轴数：0 = LV_VER_RES（280）-280
            lv_anim_set_values(&a, lv_obj_get_y(Home_Setting_Contain), LV_VER_RES - lv_obj_get_height(Home_Setting_Contain));  // Assume LV_VER_RES is the screen height
            lv_anim_set_time(&a, 20);  // Duration in milliseconds
            lv_anim_start(&a);
        }
        else if (dir == LV_DIR_BOTTOM) //向下滚动：返回home_page
        {
            lv_anim_init(&a);
            lv_anim_set_var(&a, Home_Setting_Contain);
            lv_anim_set_exec_cb(&a, anim_y_cb);
            //设置页面y轴数：0 -- 到屏幕底部y轴数：280
            lv_anim_set_values(&a, lv_obj_get_y(Home_Setting_Contain), LV_VER_RES);  // Assume LV_VER_RES is the screen height
            lv_anim_set_time(&a, 20);  // Duration in milliseconds
            lv_anim_start(&a);
        }
        else if (dir == LV_DIR_RIGHT) //右滑进入菜单
        {
            Load_New_Page(&Page_Menu); //加载新的界面
        }
    }
}



void ui_event_ShutDownPage(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    //A gesture is detected. Get the gesture with lv_indev_get_gesture_dir(lv_indev_get_act());
    if (code == LV_EVENT_GESTURE) {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir == LV_DIR_LEFT) //左滑回到主界面
        {
            //Load_New_Page(&Page_Home); //加载新的界面
            Return_Pre_Page();
        }
    }
		
}

void ui_event_NFCButton(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED))  //触发事件的对象出否处于按下状态
    {
        //checked
        ui_HomePage_NFCButton_EN=1;
				//ICcard_Select(1);
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        //released
        ui_HomePage_NFCButton_EN=0;
				//ICcard_Select(0);
    }
}


void ui_event_BELButton(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        //checked
        ui_HomePage_BLEButton_EN = 1;
        //ICcard_Select(1);
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        //released
        ui_HomePage_BLEButton_EN = 0;
        //ICcard_Select(0);
    }
}

void ui_event_ShutdownButton(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED)
    {
			//power slider
        Load_New_Page(&Page_power);
			// ui_PowerPage_screen_init();
			// lv_scr_load_anim(ui_PowerPage,LV_SCR_LOAD_ANIM_MOVE_RIGHT,0,0,true);
			// user_Stack_Push(&ScrRenewStack,(long long int)&ui_PowerPage);
    }
}

//滑动关机
void ui_event_PowerSlider(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED)
    {
			
    }
		if(event_code == LV_EVENT_CLICKED)
		{
			//power down if slider value >= 90
			if(lv_slider_get_value(PowerSlider) >=90)
			{
				//Power_DisEnable();
			}
        }
}


void ui_event_SettingButton(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED)
    {
        //设置中心待实现
        //ui_SetPage_screen_init();
		//lv_scr_load_anim(ui_SetPage,LV_SCR_LOAD_ANIM_MOVE_RIGHT,0,0,true);
		//user_Stack_Push(&ScrRenewStack,(long long int)&ui_SetPage);
    }
}

void ui_event_LightSlider(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED)
    {
        LightSlider_Num = lv_slider_get_value(Setting_LightSlider);
        #if HW_USE_HARDWARE 
            LCD_Set_Light(LightSlider_Num);
        #endif
            //printf("%d\n", LightSlider_Num);
    }
}
/***********************************page design****************************************************************** */
uint8_t value_strbuf[10];

//边框间隔为15不使用，实际可使用：高250宽210
//设计：方框高度为59.5，方框之间的间隔为4

//温度方框设计
void Temperature_design(void)
{
    Home_Temp_Contain = lv_obj_create(ui_HomePage);
    lv_obj_set_width(Home_Temp_Contain, 210);
    lv_obj_set_height(Home_Temp_Contain, 59.5);
    lv_obj_set_y(Home_Temp_Contain, 15); //相对于TOP_MID下移15，边框15不用
    lv_obj_set_align(Home_Temp_Contain, LV_ALIGN_TOP_MID);
    //lv_obj_set_align(Home_Temp_Contain, LV_ALIGN_CENTER);

    lv_style_init(&style_Temp);
    lv_style_set_bg_color(&style_Temp, lv_color_hex(0x00b7d6));
    lv_style_set_bg_opa(&style_Temp, 70); //透明度
    lv_style_set_radius(&style_Temp, 30.5);
    //lv_style_set_border_color(&style_Temp, lv_color_hex(0x000000));
    lv_style_set_border_opa(&style_Temp, 0);  //透明度
    lv_obj_add_style(Home_Temp_Contain, &style_Temp, 0); //添加样式
    lv_obj_clear_flag(Home_Temp_Contain, LV_OBJ_FLAG_SCROLLABLE); //禁用滚动标志位

    //图标容器
    Day_Or_Night = lv_obj_create(Home_Temp_Contain);
    lv_obj_set_width(Day_Or_Night, 61);
    lv_obj_set_height(Day_Or_Night, 61);
    lv_obj_set_x(Day_Or_Night, 72.5);
    lv_obj_set_align(Day_Or_Night, LV_ALIGN_CENTER);

    lv_style_init(&style_Day_Or_Night);
    lv_style_set_bg_color(&style_Day_Or_Night, lv_color_hex(0x00b7d6));
    lv_style_set_bg_opa(&style_Day_Or_Night, 100);  //透明度
    lv_style_set_border_width(&style_Day_Or_Night, 4);
    lv_style_set_border_color(&style_Day_Or_Night, lv_color_hex(0xffffff)); //pd:1b1c1d
    //lv_style_set_border_opa(&style_Day_Or_Night, 70);  //透明度
    lv_style_set_radius(&style_Day_Or_Night, 30.5);  // 设置为圆
    lv_obj_add_style(Day_Or_Night, &style_Day_Or_Night, 0); //添加样式
    lv_obj_clear_flag(Day_Or_Night, LV_OBJ_FLAG_SCROLLABLE); //禁用滚动标志位

    //显示图标：白天或者夜晚
    DayNight_Label = lv_label_create(Day_Or_Night);
    lv_obj_set_width(DayNight_Label, LV_SIZE_CONTENT);
    lv_obj_set_height(DayNight_Label, LV_SIZE_CONTENT);
    lv_obj_set_align(DayNight_Label, LV_ALIGN_CENTER);
    if ((ui_TimeHourValue >= 6) && (ui_TimeHourValue <= 18))
        lv_label_set_text(DayNight_Label, LV_SYMBOL_Day); //白天图标
    else
        lv_label_set_text(DayNight_Label, LV_SYMBOL_Moon); //晚上图标
    lv_obj_set_style_text_color(DayNight_Label, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_text_opa(DayNight_Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(DayNight_Label, &ui_icon_HomePage32, LV_PART_MAIN | LV_STATE_DEFAULT);


    //温度数值显示
    Tem_Num_Label = lv_label_create(Home_Temp_Contain);
    lv_obj_set_width(Tem_Num_Label, LV_SIZE_CONTENT);
    lv_obj_set_height(Tem_Num_Label, LV_SIZE_CONTENT);
    lv_obj_set_x(Tem_Num_Label, -30); //center为基点，右移20
    lv_obj_set_align(Tem_Num_Label, LV_ALIGN_CENTER);
    sprintf(value_strbuf,"%2d",ui_TempValue);
    lv_label_set_text(Tem_Num_Label, value_strbuf);
    lv_obj_set_style_text_color(Tem_Num_Label, lv_color_hex(0x4c7498), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Tem_Num_Label, &ui_font_Cuyuan30, LV_PART_MAIN | LV_STATE_DEFAULT);


    Celsius_Label = lv_label_create(Home_Temp_Contain);
    lv_obj_set_width(Celsius_Label, LV_SIZE_CONTENT);
    lv_obj_set_height(Celsius_Label, LV_SIZE_CONTENT);
    lv_obj_set_x(Celsius_Label, 10); //center为基点，右移10
    lv_obj_set_align(Celsius_Label, LV_ALIGN_CENTER);
    lv_label_set_text(Celsius_Label, LV_SYMBOL_Celsius);
    lv_obj_set_style_text_color(Celsius_Label, lv_color_hex(0x4c7498), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Celsius_Label, &ui_icon_Celsius24, LV_PART_MAIN | LV_STATE_DEFAULT);
}

//时间方框设计
void Time_design(void)
{
    //容器设计
    Home_Time_Contain = lv_obj_create(ui_HomePage);
    lv_obj_set_width(Home_Time_Contain, 210);
    lv_obj_set_height(Home_Time_Contain, 59.5);
    
    lv_obj_set_y(Home_Time_Contain, -31.75);//相对于CENTER上移动59.5/2+4/2
    lv_obj_set_align(Home_Time_Contain, LV_ALIGN_CENTER); //参考父对象ui_HomePage

    lv_style_init(&style_Time);
    lv_style_set_bg_color(&style_Time, lv_color_hex(0x0041d5));
    lv_style_set_bg_opa(&style_Time, 70);
    lv_style_set_border_opa(&style_Time, 0);
    lv_style_set_radius(&style_Time, 30);
    
    lv_obj_add_style(Home_Time_Contain, &style_Time, 0);
    lv_obj_clear_flag(Home_Time_Contain, LV_OBJ_FLAG_SCROLLABLE); 
    //时间标签添加：

    //小时标签
    ui_TimeHourLabel = lv_label_create(Home_Time_Contain);
    lv_obj_set_width(ui_TimeHourLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeHourLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_TimeHourLabel, -35); //center为基点，左移20
    lv_obj_set_align(ui_TimeHourLabel, LV_ALIGN_CENTER);
    sprintf(value_strbuf,"%2d",ui_TimeHourValue);  //小时值拷贝到缓冲区
    lv_label_set_text(ui_TimeHourLabel, value_strbuf);
    lv_obj_set_style_text_color(ui_TimeHourLabel, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeHourLabel, &ui_font_Cuyuan48, LV_PART_MAIN | LV_STATE_DEFAULT);


    //中间分割
    ui_TimeColonLabel = lv_label_create(Home_Time_Contain);
    lv_obj_set_width(ui_TimeColonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeColonLabel, LV_SIZE_CONTENT);
    lv_obj_set_y(ui_TimeColonLabel, -5); //center为基点，上移20
    lv_obj_set_align(ui_TimeColonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TimeColonLabel, ":");
    lv_obj_set_style_text_color(ui_TimeColonLabel, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeColonLabel, &ui_font_Cuyuan48, LV_PART_MAIN | LV_STATE_DEFAULT);

    //分钟标签
    ui_TimeMinuteLabel = lv_label_create(Home_Time_Contain);
    lv_obj_set_width(ui_TimeMinuteLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeMinuteLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_TimeMinuteLabel, 40); //center为基点，右移25
    lv_obj_set_align(ui_TimeMinuteLabel, LV_ALIGN_CENTER);
    sprintf(value_strbuf,"%2d",ui_TimeMinuteValue);  //小时值拷贝到缓冲区
    lv_label_set_text(ui_TimeMinuteLabel, value_strbuf);
    lv_obj_set_style_text_color(ui_TimeMinuteLabel, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeMinuteLabel, &ui_font_Cuyuan48, LV_PART_MAIN | LV_STATE_DEFAULT);

}

//"几号" 样式设计
void Date_design(void)
{
    //日期容器设置
    Home_Date_Contain = lv_obj_create(ui_HomePage);
    lv_obj_set_width(Home_Date_Contain, 59.5);
    lv_obj_set_height(Home_Date_Contain, 59.5);
    lv_obj_set_x(Home_Date_Contain, 15); //相较于LV_ALIGN_LEFT_MID右移15，边框15不用
    lv_obj_set_y(Home_Date_Contain, 31.75);//相对于LV_ALIGN_LEFT_MID下移 59.5/2 + 4/2
    lv_obj_set_align(Home_Date_Contain, LV_ALIGN_LEFT_MID);

    lv_style_init(&style_Date);
    //lv_style_set_bg_color(&style_Date, lv_color_hex(0x00b7d6));
    lv_style_set_radius(&style_Date, 29.75); //半径
    lv_style_set_bg_opa(&style_Date, 70);
    lv_style_set_border_opa(&style_Date, 0);
    lv_obj_add_style(Home_Date_Contain, &style_Temp, 0); //添加样式
    lv_obj_clear_flag(Home_Date_Contain, LV_OBJ_FLAG_SCROLLABLE); //禁用滚动标志位

    //icon
    Date_icon_Label = lv_label_create(Home_Date_Contain);
    lv_obj_set_width(Date_icon_Label, LV_SIZE_CONTENT);
    lv_obj_set_height(Date_icon_Label, LV_SIZE_CONTENT);
    lv_obj_set_align(Date_icon_Label, LV_ALIGN_CENTER);
    lv_label_set_text(Date_icon_Label, LV_SYMBOL_Date);
    lv_obj_set_style_text_color(Date_icon_Label, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Date_icon_Label, &ui_icon_Date30, LV_PART_MAIN | LV_STATE_DEFAULT);

    Date_Num_Label = lv_label_create(Home_Date_Contain);
    lv_obj_set_width(Date_Num_Label, LV_SIZE_CONTENT);
    lv_obj_set_height(Date_Num_Label, LV_SIZE_CONTENT);
    lv_obj_set_y(Date_Num_Label, 5); //center为基点，下移25
    lv_obj_set_align(Date_Num_Label, LV_ALIGN_CENTER);
    sprintf(value_strbuf,"%2d",ui_DateDayValue); 
    lv_label_set_text(Date_Num_Label, value_strbuf);
    lv_obj_set_style_text_color(Date_Num_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Date_Num_Label, &lv_font_montserrat_14 , LV_PART_MAIN | LV_STATE_DEFAULT);  //使用内置字体

}

//心率样式设计
void Heart_Rate_Design(void)
{
    //容器设计  
    Home_HeartRate_Contain = lv_obj_create(ui_HomePage);
    lv_obj_set_width(Home_HeartRate_Contain, 100);  //210 - 59.5 - 5 
    lv_obj_set_height(Home_HeartRate_Contain, 59.5);
    lv_obj_set_x(Home_HeartRate_Contain, -15);//左移动15，边框15不使用
    lv_obj_set_y(Home_HeartRate_Contain, 31.75); //在LV_ALIGN_RIGHT_MID基础上下移动59.5/2+4/2
    lv_obj_set_align(Home_HeartRate_Contain, LV_ALIGN_RIGHT_MID); //参考父对象ui_HomePage

    lv_style_init(&style_HeartRate);
    lv_style_set_bg_color(&style_HeartRate, lv_color_hex(0xec47a7));  //粉色背景
    lv_style_set_bg_opa(&style_HeartRate, 70);
    lv_style_set_border_opa(&style_HeartRate, 0);
    lv_style_set_radius(&style_HeartRate, 30);
    
    lv_obj_add_style(Home_HeartRate_Contain, &style_HeartRate, 0);
    lv_obj_clear_flag(Home_HeartRate_Contain, LV_OBJ_FLAG_SCROLLABLE);


    //心率图标
    HeartRate_icon_Label = lv_label_create(Home_HeartRate_Contain);
    lv_obj_set_width(HeartRate_icon_Label, LV_SIZE_CONTENT);  
    lv_obj_set_height(HeartRate_icon_Label, LV_SIZE_CONTENT);
    //lv_obj_set_x(HeartRate_icon_Label, 40);
    lv_obj_set_align(HeartRate_icon_Label, LV_ALIGN_LEFT_MID);
    lv_label_set_text(HeartRate_icon_Label, LV_SYMBOL_Heat);
    lv_obj_set_style_text_color(HeartRate_icon_Label, lv_color_hex(0xff3399), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(HeartRate_icon_Label, &ui_icon_HomePage32, LV_PART_MAIN | LV_STATE_DEFAULT);
    

    HeartRate_Num_Label = lv_label_create(Home_HeartRate_Contain);
    lv_obj_set_width(HeartRate_Num_Label, LV_SIZE_CONTENT);  
    lv_obj_set_height(HeartRate_Num_Label, LV_SIZE_CONTENT);
    //lv_obj_set_x(HeartRate_Num_Label, -10);
    lv_obj_set_align(HeartRate_Num_Label, LV_ALIGN_RIGHT_MID);
    if (ui_HeartRate_Num > 0)
    {
        sprintf(value_strbuf, "%2d", ui_HeartRate_Num);  //小时值拷贝到缓冲区
        lv_label_set_text(HeartRate_Num_Label, value_strbuf);
    }
        
    else
        lv_label_set_text(HeartRate_Num_Label, "－－");
    
    lv_obj_set_style_text_color(HeartRate_Num_Label, lv_color_hex(0xff3399), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(HeartRate_Num_Label, &ui_font_Cuyuan24, LV_PART_MAIN | LV_STATE_DEFAULT);


}


//步数方框设计
void Foots_design(void)
{
    //容器：放图标容器和步数显示
    Home_Foots_Contain = lv_obj_create(ui_HomePage);
    lv_obj_set_width(Home_Foots_Contain, 210);
    lv_obj_set_height(Home_Foots_Contain, 59.5);
    lv_obj_set_y(Home_Foots_Contain, -15); //相对于LV_ALIGN_BOTTOM_MID上移15，边框15不用
    lv_obj_set_align(Home_Foots_Contain, LV_ALIGN_BOTTOM_MID);

    lv_style_init(&style_Foots);
    lv_style_set_bg_color(&style_Foots, lv_color_hex(0xceaa14));
    lv_style_set_bg_opa(&style_Foots, 70);
    lv_style_set_border_opa(&style_Foots, 0);
    lv_style_set_radius(&style_Foots, 30.5);

    lv_obj_add_style(Home_Foots_Contain, &style_Foots, 0); //添加样式
    lv_obj_clear_flag(Home_Foots_Contain, LV_OBJ_FLAG_SCROLLABLE); //禁用滚动标志位

    
    //容器：放步数icon
    Home_Foots_icon_Contain = lv_obj_create(Home_Foots_Contain);
    lv_obj_set_width(Home_Foots_icon_Contain, 61);
    lv_obj_set_height(Home_Foots_icon_Contain, 61);
    lv_obj_set_x(Home_Foots_icon_Contain, -74.5);
    lv_obj_set_align(Home_Foots_icon_Contain, LV_ALIGN_CENTER);

    lv_style_init(&style_Foots_icon_Contain);
    lv_style_set_bg_color(&style_Foots_icon_Contain, lv_color_hex(0xceaa14)); //背景
    lv_style_set_border_width(&style_Foots_icon_Contain, 5); 
    lv_style_set_border_color(&style_Foots_icon_Contain, lv_color_hex(0xffffff)); //边框颜色
    lv_style_set_bg_opa(&style_Foots_icon_Contain, 70);
    lv_style_set_radius(&style_Foots_icon_Contain, 30.5);  // 设置为圆
    lv_obj_add_style(Home_Foots_icon_Contain, &style_Foots_icon_Contain, 0); //添加样式
    lv_obj_clear_flag(Home_Foots_icon_Contain, LV_OBJ_FLAG_SCROLLABLE); //禁用滚动标志位

    //显示图标：白天或者夜晚
    Foots_icon_Label = lv_label_create(Home_Foots_icon_Contain);
    lv_obj_set_width(Foots_icon_Label, LV_SIZE_CONTENT);
    lv_obj_set_height(Foots_icon_Label, LV_SIZE_CONTENT);
    lv_obj_set_align(Foots_icon_Label, LV_ALIGN_CENTER);
    lv_label_set_text(Foots_icon_Label, LV_SYMBOL_Foot); //白天图标
    lv_obj_set_style_text_color(Foots_icon_Label, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_text_opa(DayNight_Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Foots_icon_Label, &ui_icon_HomePage32, LV_PART_MAIN | LV_STATE_DEFAULT);


    //步数数值显示
    Foots_Num_Label = lv_label_create(Home_Foots_Contain);
    lv_obj_set_width(Foots_Num_Label, LV_SIZE_CONTENT);
    lv_obj_set_height(Foots_Num_Label, LV_SIZE_CONTENT);
    lv_obj_set_x(Foots_Num_Label, 30); //center为基点，右移30
    lv_obj_set_align(Foots_Num_Label, LV_ALIGN_CENTER);
    if (Foots_Num > 0)
    {
        sprintf(value_strbuf, "%2d", Foots_Num);  //小时值拷贝到缓冲区
        lv_label_set_text(Foots_Num_Label, value_strbuf);
        lv_obj_set_style_text_color(Foots_Num_Label, lv_color_hex(0x4c7498), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(Foots_Num_Label, &ui_font_Cuyuan30, LV_PART_MAIN | LV_STATE_DEFAULT);
        
    }
    else
    {
        lv_label_set_text(Foots_Num_Label, "－－");
        lv_obj_set_style_text_color(Foots_Num_Label, lv_color_hex(0x4c7498), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(Foots_Num_Label, &ui_font_Cuyuan24, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

}

//设置中心页面：从屏幕底部向上滑，触发事件调用回调函数
void Setting_design(void)
{
    Home_Setting_Contain = lv_obj_create(ui_HomePage);

    lv_obj_set_size(Home_Setting_Contain, 240, 280);  // 根据需要调整尺寸
    lv_obj_set_style_bg_color(Home_Setting_Contain, lv_color_hex(0x323232), 0);
    lv_obj_set_style_bg_opa(Home_Setting_Contain, 99, LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_radius(Home_Setting_Contain, 10, 0);  // 设置圆角
    lv_obj_set_style_border_width(Home_Setting_Contain, 0, 0);  // 无边框
    lv_obj_set_y(Home_Setting_Contain, LV_VER_RES);  // 初始位置在屏幕底部之外

    //NFC按钮
    Setting_NFCButton = lv_btn_create(Home_Setting_Contain);
    lv_obj_set_width(Setting_NFCButton, 50);
    lv_obj_set_height(Setting_NFCButton, 50);
    lv_obj_set_x(Setting_NFCButton, -80);
    lv_obj_set_y(Setting_NFCButton, 20);
    lv_obj_set_align(Setting_NFCButton, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(Setting_NFCButton, 25,0); //设置成圆形
    lv_obj_add_flag(Setting_NFCButton, LV_OBJ_FLAG_CHECKABLE);     /// Flags:可点击
    lv_obj_set_style_bg_color(Setting_NFCButton, lv_color_hex(0x3D3D3D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Setting_NFCButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Setting_NFCButton, lv_color_hex(0xFFB90F), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(Setting_NFCButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    if(ui_HomePage_NFCButton_EN) //若是默认启用NFC，状态设置为点击状态
    {lv_obj_add_state(Setting_NFCButton, LV_STATE_CHECKED);}
    lv_obj_add_event_cb(Setting_NFCButton, ui_event_NFCButton, LV_EVENT_ALL, NULL);

    NFCIcon = lv_label_create(Setting_NFCButton);
    lv_obj_set_width(NFCIcon, LV_SIZE_CONTENT); 
    lv_obj_set_height(NFCIcon, LV_SIZE_CONTENT);  
    lv_obj_set_align(NFCIcon, LV_ALIGN_CENTER);
    lv_label_set_text(NFCIcon, LV_SYMBOL_NFC);
    lv_obj_set_style_text_color(NFCIcon, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(NFCIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(NFCIcon, &ui_icon_NFCButton34, LV_PART_MAIN | LV_STATE_DEFAULT);

    //蓝牙按钮
    Setting_BLEButton = lv_btn_create(Home_Setting_Contain);
    lv_obj_set_width(Setting_BLEButton, 50);
    lv_obj_set_height(Setting_BLEButton, 50);
    lv_obj_set_y(Setting_BLEButton, 20);
    lv_obj_set_align(Setting_BLEButton, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(Setting_BLEButton, 25,0); //设置成圆形
    lv_obj_add_flag(Setting_BLEButton, LV_OBJ_FLAG_CHECKABLE);     /// Flags:可点击
    lv_obj_set_style_bg_color(Setting_BLEButton, lv_color_hex(0x3D3D3D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Setting_BLEButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Setting_BLEButton, lv_color_hex(0xFFB90F), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(Setting_BLEButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    if(ui_HomePage_BLEButton_EN) //若是默认启用NFC，状态设置为点击状态
    {lv_obj_add_state(Setting_BLEButton, LV_STATE_CHECKED);}
    lv_obj_add_event_cb(Setting_BLEButton, ui_event_BELButton, LV_EVENT_ALL, NULL);

    BLEIcon = lv_label_create(Setting_BLEButton);
    lv_obj_set_width(BLEIcon, 50);  
    lv_obj_set_height(BLEIcon, 50);
    lv_obj_set_x(BLEIcon, 9);
    lv_obj_set_y(BLEIcon,6);
    lv_obj_set_align(BLEIcon, LV_ALIGN_CENTER);
    lv_label_set_text(BLEIcon, LV_SYMBOL_BLUE); //自带蓝牙图标
    lv_obj_set_style_text_color(BLEIcon, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(BLEIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(BLEIcon, &ui_icon_MenuOderPage34, LV_PART_MAIN | LV_STATE_DEFAULT);


    //关机按钮
    Setting_ShutdownButton = lv_btn_create(Home_Setting_Contain);
    lv_obj_set_width(Setting_ShutdownButton, 50);
    lv_obj_set_height(Setting_ShutdownButton, 50);
    lv_obj_set_y(Setting_ShutdownButton, 90);
    lv_obj_set_align(Setting_ShutdownButton, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(Setting_ShutdownButton, 25,0); //设置成圆形
    lv_obj_add_flag(Setting_ShutdownButton, LV_OBJ_FLAG_CHECKABLE);     /// Flags:可点击
    lv_obj_set_style_bg_color(Setting_ShutdownButton, lv_color_hex(0x3D3D3D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Setting_ShutdownButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Setting_ShutdownButton, lv_color_hex(0xFFB90F), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(Setting_ShutdownButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_event_cb(Setting_ShutdownButton, ui_event_ShutdownButton, LV_EVENT_ALL, NULL);

    ShutdownIcon = lv_label_create(Setting_ShutdownButton);
    lv_obj_set_width(ShutdownIcon, 50);  
    lv_obj_set_height(ShutdownIcon, 50);
    lv_obj_set_x(ShutdownIcon, 8.5);
    lv_obj_set_y(ShutdownIcon,6);
    lv_obj_set_align(ShutdownIcon, LV_ALIGN_CENTER);
    lv_label_set_text(ShutdownIcon, LV_SYMBOL_SHUTDOWN); 
    lv_obj_set_style_text_color(ShutdownIcon, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ShutdownIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ShutdownIcon, &ui_icon_MenuOderPage34, LV_PART_MAIN | LV_STATE_DEFAULT);


    //设置中心键
    Setting_SetButton = lv_btn_create(Home_Setting_Contain);
    lv_obj_set_width(Setting_SetButton, 50);
    lv_obj_set_height(Setting_SetButton, 50);
    lv_obj_set_y(Setting_SetButton, 90);
    lv_obj_set_x(Setting_SetButton, -80);
    lv_obj_set_align(Setting_SetButton, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(Setting_SetButton, 25,0); //设置成圆形
    lv_obj_add_flag(Setting_SetButton, LV_OBJ_FLAG_CHECKABLE);     /// Flags:可点击
    lv_obj_set_style_bg_color(Setting_SetButton, lv_color_hex(0x3D3D3D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Setting_SetButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Setting_SetButton, lv_color_hex(0xFFB90F), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(Setting_SetButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_event_cb(Setting_SetButton, ui_event_SettingButton, LV_EVENT_ALL, NULL);

    SetIcon = lv_label_create(Setting_SetButton);
    lv_obj_set_width(SetIcon, 50);  
    lv_obj_set_height(SetIcon, 50);
    lv_obj_set_x(SetIcon, 8.5);
    lv_obj_set_y(SetIcon,6);
    lv_obj_set_align(SetIcon, LV_ALIGN_CENTER);
    lv_label_set_text(SetIcon, LV_SYMBOL_SETTING); //自带
    lv_obj_set_style_text_color(SetIcon, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(SetIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(SetIcon, &ui_icon_MenuOderPage34, LV_PART_MAIN | LV_STATE_DEFAULT);


    //亮度调节
    //lv_obj_t* Setting_LightSlider;
    //lv_obj_t* LightIcon;
    Setting_LightSlider = lv_slider_create(Home_Setting_Contain);
    lv_obj_set_width(Setting_LightSlider, 50);
    lv_obj_set_height(Setting_LightSlider, 120);
    lv_obj_set_x(Setting_LightSlider, -20);
    lv_obj_set_y(Setting_LightSlider, 20);
    lv_obj_set_align(Setting_LightSlider, LV_ALIGN_TOP_RIGHT);
    // if (lv_slider_get_mode(Setting_LightSlider) == LV_SLIDER_MODE_RANGE)
    //     lv_slider_set_left_value(Setting_LightSlider, 0, LV_ANIM_OFF);
    lv_slider_set_range(Setting_LightSlider, 0, 100); //值：0-100
    lv_slider_set_value(Setting_LightSlider, LightSlider_Num, LV_ANIM_OFF); //初始值
    lv_obj_set_style_radius(Setting_LightSlider, 15, LV_PART_MAIN | LV_STATE_DEFAULT); //背景
    lv_obj_set_style_bg_color(Setting_LightSlider, lv_color_hex(0x3D3D3D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Setting_LightSlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(Setting_LightSlider, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);  //滑动条
    lv_obj_set_style_bg_color(Setting_LightSlider, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Setting_LightSlider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Setting_LightSlider, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT); //旋钮设置透明
    lv_obj_set_style_bg_opa(Setting_LightSlider, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(Setting_LightSlider, ui_event_LightSlider, LV_EVENT_ALL, NULL);



}

/***********************************page init****************************************************************** */
void ui_HomePage_screen_init(void)
{
    //ui_MenuScrollY = 0;
    

    ui_HomePage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_HomePage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t *img = lv_img_create(ui_HomePage);  // 在 obj 上创建图像对象
    lv_img_set_src(img, &ui_img_home_page);  // 设置图像源
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);  // 图像居中显示

    // delay_ms(500);

    Temperature_design();
    Time_design();
    Date_design();
    Heart_Rate_Design();
    Foots_design();
    Setting_design();

    ui_HomePageTimer = lv_timer_create(HomePage_timer_cb, 500,  NULL);
    lv_obj_add_event_cb(ui_HomePage, ui_event_HomePage, LV_EVENT_ALL, NULL);
    
}



void ui_HomePage_screen_deinit(void)
{
    lv_timer_del(ui_HomePageTimer);
}



void ui_PowerPage_screen_init(void)
{
    ui_PowerPage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_PowerPage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    PowerSlider = lv_slider_create(ui_PowerPage);
    lv_obj_set_width(PowerSlider, 220);
    lv_obj_set_height(PowerSlider, 50);
    lv_obj_set_align(PowerSlider, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(PowerSlider, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(PowerSlider, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(PowerSlider, lv_color_hex(0x800000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(PowerSlider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(PowerSlider, lv_color_hex(0x800000), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(PowerSlider, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    PowerLabel = lv_label_create(PowerSlider);
    lv_obj_set_width(PowerLabel, LV_SIZE_CONTENT);  
    lv_obj_set_height(PowerLabel, LV_SIZE_CONTENT);  
    lv_obj_set_align(PowerLabel, LV_ALIGN_CENTER);
    lv_label_set_text(PowerLabel, "滑动关机");
    lv_obj_set_style_text_color(PowerLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(PowerLabel, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(PowerLabel, &ui_font_Cuyuan20, LV_PART_MAIN | LV_STATE_DEFAULT);

		//events
    lv_obj_add_event_cb(PowerSlider, ui_event_PowerSlider, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PowerPage, ui_event_ShutDownPage, LV_EVENT_ALL, NULL);

}

void ui_PowerPage_screen_deinit(void)
{
    //NULL
}