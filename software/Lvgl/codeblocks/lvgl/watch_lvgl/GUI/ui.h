// LVGL VERSION: 8.2.0


#ifndef _UI_H
#define _UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "../../src/widgets/lv_img.h"
#include "stdio.h"
#include "../Func/Include/FuncUiPageManage.h"



LV_FONT_DECLARE(ui_font_Cuyuan18);
LV_FONT_DECLARE(ui_font_Cuyuan20);
LV_FONT_DECLARE(ui_font_Cuyuan24);
LV_FONT_DECLARE(ui_font_Cuyuan30);
LV_FONT_DECLARE(ui_font_Cuyuan38);
LV_FONT_DECLARE(ui_font_Cuyuan48);
LV_FONT_DECLARE(ui_font_Cuyuan80);



LV_FONT_DECLARE(ui_icon_HomePage32);
LV_FONT_DECLARE(ui_icon_Celsius24);
LV_FONT_DECLARE(ui_icon_Date30);
LV_FONT_DECLARE(ui_icon_NFCButton34);
LV_FONT_DECLARE(ui_icon_MenuPageHost30);
LV_FONT_DECLARE(ui_icon_GamePage30);
LV_FONT_DECLARE(ui_icon_SettingPage30);
LV_FONT_DECLARE(ui_icon_CompassEnv_Page28);
LV_FONT_DECLARE(ui_icon_TimerPage24);
LV_FONT_DECLARE(ui_icon_MenuOderPage34);
LV_FONT_DECLARE(ui_icon_AIPage90);
LV_FONT_DECLARE(ui_icon_MenuAI30);



#define LV_SYMBOL_ok "\xEE\x9B\xB5"

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
