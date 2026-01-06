#ifndef _O_SetFunAchPAGE_H
#define _O_SetFunAchPAGE_H
#ifdef __cplusplus
extern "C" {
#endif
    #include "../../ui.h"
    #include "../../ui_helpers.h"

    extern page_t Setting_Bright;
    extern lv_obj_t* Setting_BrightPage;;
    void Setting_BrightPage_screen_init(void);
    void Setting_BrightPage_screen_deinit(void);

    extern page_t Setting_Hibernate;
    extern lv_obj_t* Setting_HibernatePage;
    void Setting_HibernatePage_screen_init(void);
    void Setting_HibernatePage_screen_deinit(void);




#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif