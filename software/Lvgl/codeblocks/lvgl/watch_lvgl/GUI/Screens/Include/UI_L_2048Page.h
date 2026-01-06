#ifndef _L_2048PAGE_H
#define _L_2048PAGE_H
#ifdef __cplusplus
extern "C" {
#endif
    
#include "../../ui.h"
#include "../../ui_helpers.h"

extern lv_obj_t * ui_Game2048Page;

extern page_t GamePage_2048;

void ui_Game2048Page_screen_init(void);
void ui_Game2048Page_screen_deinit(void);


#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif