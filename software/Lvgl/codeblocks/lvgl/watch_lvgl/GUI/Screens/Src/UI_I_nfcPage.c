#include "../../ui.h"
#include "../../ui_helpers.h"
#include "../include/UI_I_nfcPage.h"
#include "../include/UI_B_MenuPage.h"
#include "../../../Func/Include/FuncHWDataManage.h"
/***********************************icon/img customize****************************************************************** */


/***********************************Page definition****************************************************************** */
page_t Menu_NFC = { Menu_nfcPage_screen_init,Menu_nfcPage_screen_deinit,&Menu_nfcPage };




/***********************************obj****************************************************************** */
lv_obj_t* Menu_nfcPage;
lv_obj_t* Menu_nfc_warnningIcon;
lv_obj_t* Menu_nfc_warnningLabel;

lv_obj_t* Menu_nfc_Cannel;
lv_obj_t* Menu_nfc_CannelLabel;


/***********************************event****************************************************************** */
void nfcPage_event_cb(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED)
    {
        // Return_Pre_Page();
        lv_obj_del(Menu_nfcPage);
        lv_obj_add_flag(ui_MenuPage,LV_OBJ_FLAG_SCROLLABLE);
    }
}

void Box_Create(void)
{
    Menu_nfcPage = lv_obj_create(ui_MenuPage);
    lv_obj_set_width(Menu_nfcPage, 200);
    lv_obj_set_height(Menu_nfcPage, 130);
    lv_obj_align_to(Menu_nfcPage, Menu_nfcCard_Row, LV_ALIGN_CENTER, 0, 0);
    lv_obj_clear_flag(Menu_nfcPage,LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(Menu_nfcPage, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(Menu_nfcPage, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_nfc_warnningIcon = lv_label_create(Menu_nfcPage);
    lv_obj_set_width(Menu_nfc_warnningIcon, LV_SIZE_CONTENT);  
    lv_obj_set_height(Menu_nfc_warnningIcon, LV_SIZE_CONTENT);    
    lv_obj_set_align(Menu_nfc_warnningIcon, LV_ALIGN_TOP_MID);
    lv_label_set_text(Menu_nfc_warnningIcon, LV_SYMBOL_WARNING);
    lv_obj_set_style_text_color(Menu_nfc_warnningIcon, lv_color_hex(0x0080FF), LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_nfc_warnningLabel = lv_label_create(Menu_nfcPage);
    lv_obj_set_width(Menu_nfc_warnningLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(Menu_nfc_warnningLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(Menu_nfc_warnningLabel, 0);
    lv_obj_set_y(Menu_nfc_warnningLabel, 25);
    lv_obj_set_align(Menu_nfc_warnningLabel, LV_ALIGN_TOP_MID);
    lv_label_set_text(Menu_nfc_warnningLabel, "开发中");
    lv_obj_set_style_text_color(Menu_nfc_warnningLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Menu_nfc_warnningLabel, &ui_font_Cuyuan18, LV_PART_MAIN | LV_STATE_DEFAULT);

    Menu_nfc_Cannel = lv_obj_create(Menu_nfcPage);
    lv_obj_set_width(Menu_nfc_Cannel, 200);
    lv_obj_set_height(Menu_nfc_Cannel, 30);
    lv_obj_set_x(Menu_nfc_Cannel, 0);
    lv_obj_set_y(Menu_nfc_Cannel, 14);
    lv_obj_set_align(Menu_nfc_Cannel, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(Menu_nfc_Cannel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(Menu_nfc_Cannel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_nfc_Cannel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Menu_nfc_Cannel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(Menu_nfc_Cannel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(Menu_nfc_Cannel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(Menu_nfc_Cannel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(Menu_nfc_Cannel, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Menu_nfc_Cannel, lv_color_hex(0x969696), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(Menu_nfc_Cannel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    Menu_nfc_CannelLabel = lv_label_create(Menu_nfc_Cannel);
    lv_obj_set_width(Menu_nfc_CannelLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(Menu_nfc_CannelLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(Menu_nfc_CannelLabel, LV_ALIGN_CENTER);
    lv_label_set_text(Menu_nfc_CannelLabel, "OK");
    lv_obj_set_style_text_color(Menu_nfc_CannelLabel, lv_color_hex(0x5FB878), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(Menu_nfc_CannelLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_add_event_cb(Menu_nfc_Cannel, nfcPage_event_cb, LV_EVENT_ALL, NULL);
}


/***********************************page design****************************************************************** */
void Menu_nfcPage_screen_init(void)
{

    Box_Create();

}

void Menu_nfcPage_screen_deinit(void)
{

}