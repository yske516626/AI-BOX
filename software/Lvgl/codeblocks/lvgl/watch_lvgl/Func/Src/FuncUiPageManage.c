#include "../Include/FuncUiPageManage.h"
#include "../../GUI/Screens/Include/UI_A_HomePage.h"
#include "../../GUI/Screens/Include/UI_B_MenuPage.h"

/********define*********/
#define error 1
#define success 0


/********definition*********/
pageStack_t pageStack;


static void Stack_Init(pageStack_t* stack)
{
    stack->top = 0;
}

/**
 * @brief  入栈
 * @note
 * @param  stack:
 * @param  page:
 * @retval
 */
static uint8_t Stack_Push(pageStack_t* stack, page_t* page)
{
    if (stack->top >= MAX_DEPTH)
    {
        return error;
    }
    stack->pages[stack->top] = page;
    stack->top++;
    return success;
}

/**
 * @brief  出栈。调用其释放函数清除资源
 * @note
 * @param  stack:
 * @retval
 */
static unsigned char Stack_Pop(pageStack_t* stack)
{
    if (stack->top <= 0)
    {
        return error;
    }
    stack->pages[--stack->top]->deinit();
    return success;
}

/**
 * @brief  栈是否为空
 * @note
 * @param  stack:
 * @retval 1：空；0：非空
 */
static int8_t Stack_Is_Empty(const pageStack_t* stack)
{
    return stack->top == 0;
}

/**
 * @brief  获取栈顶数据
 * @note
 * @param  stack:
 * @retval
 */
static page_t* Stack_Get_Top(pageStack_t* stack)
{
    if (stack->top == 0)
        return NULL;
    return stack->pages[stack->top - 1];
}

/******************************************************************************** */

/**
 * @brief  获取栈顶页面
 * @note
 * @retval page_t or NULL
 */
page_t* Get_Top_Page(void)
{
    return Stack_Get_Top(&pageStack);
}
/**
 * @brief  Return to the previous page 返回上一页
 * @note   
 * @retval None
 */
void Return_Pre_Page(void)
{
    if (Stack_Is_Empty(&pageStack))
    {
        return;
    }
    Stack_Pop(&pageStack);  //出栈，弹出当前的页面,并且会释放掉
    //栈为空，入栈并且切换到菜单界面
    if (Stack_Is_Empty(&pageStack))
    {
        Stack_Push(&pageStack, &Page_Home);
        Stack_Push(&pageStack, &Page_Menu);  //位于栈顶，显示该界面
        Page_Menu.init();
        lv_scr_load_anim(*Page_Menu.page_obj, LV_SCR_LOAD_ANIM_MOVE_LEFT, 50, 0, true);
    }
    else {
        //切换到上一个页面
        page_t *previous_page = pageStack.pages[pageStack.top - 1];
        previous_page->init();
        lv_scr_load_anim(*(previous_page->page_obj), LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 0, true);
    }
}


/**
 * @brief  回到Page_Home
 * @note
 * @retval None
 */
void Return_First_Page(void) {

    if (Stack_Is_Empty(&pageStack)) {
        // 栈为空时，不应发生
        return;
    }

    // 弹出除栈底的所有页面
    while(pageStack.top > 1)
        Stack_Pop(&pageStack); //释放出栈顶的所有页面，也就是只剩下Page_home
    pageStack.pages[pageStack.top - 1]->init(); // 初始化新页面
    lv_scr_load_anim(*pageStack.pages[pageStack.top - 1]->page_obj, LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 0, true); // 加载并应用动画
}

/**
 * @brief  加载新页面
 * @note   比如当前位于菜单界面，点击测心率，会跳到心率界面（心率界面入栈）
 *         但是原栈顶（菜单界面）并不出栈，只是释放资源减少CPU占用率。还需要保留
 *         返回菜单界面（调用Return_Pre_Page：弹出心率界面同时释放资源）时还需要用到
 *         可用于滑动界面弹出后，清除homepage
 * @param  newPage:
 * @retval None
 */
void Load_New_Page(page_t* newPage)
{
    

    if (pageStack.top > 0)
        pageStack.pages[pageStack.top - 1]->deinit(); //释放掉当前页面占用的cpu资源，但不出栈

    if (Stack_Push(&pageStack, newPage) == error)
        return;    //新的页面入栈
    newPage->init(); //新页面初始化
    lv_scr_load_anim(*newPage->page_obj, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true); // 加载并应用动画
}


void Pages_init(void)
{
    Stack_Init(&pageStack);
    Stack_Push(&pageStack, &Page_Home);
    Page_Home.init();
    lv_disp_load_scr(*Page_Home.page_obj);
}
