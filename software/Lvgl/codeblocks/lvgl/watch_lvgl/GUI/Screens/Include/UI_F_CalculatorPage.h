#ifndef _F_CALCULATORPAGE_H
#define _F_CALCULATORPAGE_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "../../ui.h"
#include "../../ui_helpers.h"


// 令牌：会根据获取的令牌决定语法树怎么走：是数字还是计算符号，先+还是先乘.....
typedef enum {
    TOKENIZER_ERROR = 0,    // Error
    TOKENIZER_ENDOFINPUT,   // End of input
    TOKENIZER_NUMBER,       // number
    TOKENIZER_PLUS,         // +
    TOKENIZER_MINUS,        // -
    TOKENIZER_ASTR,         // *
    TOKENIZER_SLASH,        // /
    TOKENIZER_LPAREN,       // (
    TOKENIZER_RPAREN,       // )
} Calculator_token_t;
    
//错误码枚举
 typedef enum {
    no_error = 0,           // no error
    syntax_error = 1,           // syntax error
} Calculator_error_t;


 //错误码和相应消息
 typedef struct {
    Calculator_error_t error_code;
    char   *message;
} Calculator_error_table_t;

//计算数据显示
typedef struct {
    lv_obj_t obj;
    lv_obj_t * ta_hist;                         // 历史显示
    lv_obj_t * ta_input;                        // 输入显示
    lv_obj_t * btnmatrix;                       // 矩阵按钮
    char     * curr_char;                       // 当前表达式的字符显示
    char     * next_char;                       // 表达式的下一字符显示
    Calculator_token_t  current_token;                     // 令牌
    Calculator_error_t  error_code;                        // 错误码
    uint16_t count;                             // 记录表达式位置
    char     calc_exp[32]; // 表达式，最长长度为32
} Calculator_t;




/***********************包装******************************** */

extern page_t Menu_Calculator;
extern lv_obj_t* Menu_CalculatorPage;

void Menu_CalculatorPage_screen_init(void);
void Menu_CalculatorPage_screen_deinit(void);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif