/*******************************************************************************
 * Size: 24 px
 * Bpp: 1
 * Opts: --bpp 1 --size 24 --no-compress --font iconfont.ttf --range 61122 --format lvgl -o ui_icon_Celsius24.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef UI_ICON_CELSIUS24
#define UI_ICON_CELSIUS24 1
#endif

#if UI_ICON_CELSIUS24

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+EEC2 "" */
    0xf, 0x0, 0x3, 0xc0, 0xf, 0xf0, 0x7, 0xff,
    0x7, 0xfc, 0x3, 0xff, 0xe1, 0xc3, 0x81, 0xf0,
    0xfc, 0xe0, 0x60, 0xf0, 0xf, 0xb8, 0x18, 0x78,
    0x1, 0xee, 0x6, 0x1c, 0x0, 0x3d, 0xc3, 0x87,
    0x0, 0x4, 0x7f, 0xe3, 0x80, 0x0, 0xf, 0xf0,
    0xe0, 0x0, 0x0, 0xf0, 0x38, 0x0, 0x0, 0x0,
    0xe, 0x0, 0x0, 0x0, 0x3, 0x80, 0x0, 0x0,
    0x0, 0xe0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0,
    0x0, 0xf, 0x0, 0xe, 0x0, 0x1, 0xc0, 0x3,
    0xc0, 0x0, 0x78, 0x1, 0xe0, 0x0, 0xf, 0x0,
    0x78, 0x0, 0x3, 0xe0, 0x7c, 0x0, 0x0, 0x7f,
    0xfe, 0x0, 0x0, 0x7, 0xff, 0x0, 0x0, 0x0,
    0x7f, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 568, .box_w = 34, .box_h = 23, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 61122, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_icon_Celsius24 = {
#else
lv_font_t ui_icon_Celsius24 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 23,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_ICON_CELSIUS24*/

