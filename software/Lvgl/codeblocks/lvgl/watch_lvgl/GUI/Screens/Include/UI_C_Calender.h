#ifndef _C_CALENDARPAGE_H
#define _C_CALENDARPAGE_H

#ifdef __cplusplus
extern "C" {
#endif

extern page_t Menu_Calender;
extern lv_obj_t* Menu_CalendarPage;
extern lv_obj_t* Component_Calendar;

void Menu_CalendarPage_screen_init(void);
void Menu_CalendarPage_screen_deinit(void);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif