#ifndef _J_ENVPAGE_H
#define _J_ENVPAGE_H

#ifdef __cplusplus
extern "C" {
#endif

    extern page_t Menu_Env;
    extern lv_obj_t* Menu_EnvPage;

    void Menu_EnvPage_screen_init(void);
    void Menu_EnvPage_screen_deinit(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif