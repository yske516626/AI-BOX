#ifndef _N_SettingPAGE_H
#define _N_SettingPAGE_H
#ifdef __cplusplus
extern "C" {
#endif
    #include "../../ui.h"
    #include "../../ui_helpers.h"

    extern page_t Menu_Setting;
    extern lv_obj_t* Menu_SettingPage;
    void Menu_SettingPage_screen_init(void);
    void Menu_SettingPage_screen_deinit(void);


#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif