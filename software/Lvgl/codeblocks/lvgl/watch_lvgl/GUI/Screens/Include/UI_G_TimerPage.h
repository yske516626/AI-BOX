#ifndef _G_TIMERPAGE_H
#define _G_TIMERPAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../ui.h"
#include "../../ui_helpers.h"

extern page_t Menu_Timer;
extern lv_obj_t* Menu_TimerPage;

void Menu_TiemrPage_screen_init(void);
void Menu_TiemrPage_screen_deinit(void);

    
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
