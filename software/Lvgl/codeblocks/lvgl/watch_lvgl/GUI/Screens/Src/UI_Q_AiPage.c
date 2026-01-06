#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../Include/UI_A_HomePage.h"
#include "../Include/UI_N_SettingPage.h"
#include "../Include/UI_Q_AiPage.h"
#include "../../../Func/Include/FuncHWDataManage.h"

/***********************************icon/img customize****************************************************************** */
#define LV_SYMBOL_DOG "\xEE\x99\x87"  // ai

LV_IMG_DECLARE(ui_img_MenuAI);

/***********************************Page definition****************************************************************** */
page_t Menu_AI = { ui_AiPage_screen_init, ui_AiPage_screen_deinit, &Menu_AiPage };

/***********************************obj****************************************************************** */
lv_obj_t* Menu_AiPage;
lv_obj_t* Testlabel;




/***********************************event****************************************************************** */






/***********************************page design****************************************************************** */

void ui_AiPage_screen_init(void)
{
	Menu_AiPage = lv_obj_create(NULL);
	lv_obj_set_style_bg_color(Menu_AiPage, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_clear_flag(Menu_AiPage, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_size(Menu_AiPage, 240, 280);



    Testlabel = lv_img_create(Menu_AiPage);
    lv_img_set_src(Testlabel, &ui_img_MenuAI);  // 设置图像源
    //lv_obj_set_y(img_heart, -50);
    lv_obj_align(Testlabel, LV_ALIGN_CENTER,0,0);

}


void ui_AiPage_screen_deinit(void)
{

}
