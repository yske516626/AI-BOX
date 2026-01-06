#ifndef _H_COMPASSPAGE_H
#define _H_COMPASSPAGE_H

#ifdef __cplusplus
extern "C" {
#endif

extern lv_obj_t* Menu_CompassPage;
extern page_t Menu_Compass;

void Menu_CompassPage_screen_init(void);
void Menu_CompassPage_screen_deinit(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif