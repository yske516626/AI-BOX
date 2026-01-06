#ifndef PAGE_STACK_H
#define PAGE_STACK_H

#include "../../GUI/ui.h"




#define MAX_DEPTH 6 //页面栈深度

//单个页面结构体
typedef struct {
    void (*init)(void);  //该页面对应的初始化函数
    void (*deinit)(void);  //该页面对应的释放函数
    lv_obj_t** page_obj; //指向页面对象
}page_t;

//多个页面结构体，使用堆栈来进行管理
typedef struct
{
    page_t* pages[MAX_DEPTH];
    uint8_t top; //栈顶
}pageStack_t;

extern pageStack_t pageStack;

page_t* Get_Top_Page(void);






#endif