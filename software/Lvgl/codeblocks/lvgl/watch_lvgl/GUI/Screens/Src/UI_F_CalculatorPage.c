

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include "../../../../core/lv_obj_class.h"
#include "../Include/UI_F_CalculatorPage.h"



/******************************************函数声明************************************************************* */
static void Calculator_constructor(const lv_obj_class_t* class_p, lv_obj_t* obj);
static void Calculator_destructor(const lv_obj_class_t* class_p, lv_obj_t* obj);



/******************************************数据定义************************************************************* */
const lv_obj_class_t Calculator_class = {
    .constructor_cb = Calculator_constructor,
    .destructor_cb  = Calculator_destructor,
    .width_def      = 240,  //显示屏宽
    .height_def     = 280,  //显示屏高
    .instance_size  = sizeof(Calculator_t),  //类结构体的大小
    .base_class     = &lv_obj_class,         //定义的结构体
};


//计算器按钮矩阵数据
static const char * btnm_map[] = {  "(", ")", "C", "<-", "\n",
    "7", "8", "9", "/",  "\n",
    "4", "5", "6", "*",  "\n",
    "1", "2", "3", "-",  "\n",
    "0", ".", "=", "+",  ""};
//按钮的控制属性映射表
static const lv_btnmatrix_ctrl_t ctrl_map[] = { 1, 1, LV_BTNMATRIX_CTRL_CHECKED, LV_BTNMATRIX_CTRL_CHECKED,
    1, 1, 1, LV_BTNMATRIX_CTRL_CHECKED,
    1, 1, 1, LV_BTNMATRIX_CTRL_CHECKED,
    1, 1, 1, LV_BTNMATRIX_CTRL_CHECKED,
    1, 1, LV_BTNMATRIX_CTRL_CHECKED, LV_BTNMATRIX_CTRL_CHECKED };


// error list
static const Calculator_error_table_t error_table[] = {
{.error_code = no_error,            .message = "no error"},
{.error_code = syntax_error,        .message = "syntax error!"}
};

/******************************************内部：语法分析and计算************************************************************* */


/**
 * @brief 获取下一个字符对应的令牌：数字令牌还是计计算符号令牌
 * @note  
 * @param  obj: 
 * @retval 
 */
static Calculator_token_t calculator_get_next_token(lv_obj_t* obj)
{
    int i;
    Calculator_t * calc = (Calculator_t *)obj;

    // End of expression
    if (calc->curr_char == '\0')
        return TOKENIZER_ENDOFINPUT;

    if (isdigit(*calc->curr_char))  //当前字符是否为数字
    {
        for (i = 0; i <= 32; i++)  //表达式最长长度不超过32
        {
            if (!isdigit(*(calc->curr_char + i))) //下一个字符是不是为数字
            {
                calc->next_char = calc->curr_char + i;  
                return TOKENIZER_NUMBER;  //取得的数字，返回数字令牌
            }
        }
    }

    // 不是数字，判断是哪个计算符号，返回对用的令牌
    else
    {
        calc->next_char++; //如果上面分支没走，也就是不是数字，calc->next_char就是calc->curr_char，++才是下一个字符
        switch (*(calc->curr_char))
        {
        case '+':
            return TOKENIZER_PLUS;
        case '-':
            return TOKENIZER_MINUS;
        case '*':
            return TOKENIZER_ASTR;
        case '/':
            return TOKENIZER_SLASH;
        case '(':
            return TOKENIZER_LPAREN;
        case ')':
            return TOKENIZER_RPAREN;
        default:
            break;
        }
    }

    return TOKENIZER_ERROR; //错误令牌
}

/**
 * 解析下一个令牌
 * @param obj   
 */
static void calculator_tokenizer_next(lv_obj_t* obj)
{
    Calculator_t * calc = (Calculator_t *)obj;

    //解析到结束令牌
    if ((*(calc->curr_char) == '\0') || (calc->current_token == TOKENIZER_ENDOFINPUT))
        return;

    calc->curr_char = calc->next_char;
    calc->current_token = calculator_get_next_token(obj);  //获取下一个令牌并标记

    return;
}

/**
 * Match the current token according to syntax rules.
 * 根据语法规则标记当前的令牌
 * @param curr_char       pointer to a calc object
 * @param token           token
 */
static void Match_token_rules(lv_obj_t* obj, Calculator_token_t token)
{
    Calculator_t * calc = (Calculator_t *)obj;

    if (token != calc->current_token)
    {
        //设置错误令牌
        calc->error_code = syntax_error;
        LV_UNUSED(calc->error_code);
    }

    calculator_tokenizer_next(obj);
}

static int calculator_expression(lv_obj_t* obj); //声明，第三优先级计算()递归调用
/**
 * @brief  第三优先级计算，也就是()的内容
 * @note   
 * @param  obj: 
 * @retval 
 */
static int calculator_third_level_priority(lv_obj_t* obj)
{
    int r = 0;
    Calculator_t * calc = (Calculator_t *)obj;

    // Type of current token
    switch (calc->current_token)
    {
        // Number (Terminator)
        case TOKENIZER_NUMBER:
            r = atoi(calc->curr_char); //将ASCII码转化为实际的数字
            Match_token_rules(obj, TOKENIZER_NUMBER); //标记当前令牌为数值
            break;
        //左括号
        case TOKENIZER_LPAREN:
            Match_token_rules(obj, TOKENIZER_LPAREN); //标记当前令牌为左括号
            // Treat the value in parentheses as a new expression and calculate recursively (recursion starts with function expr())
            r = calculator_expression(obj); //去计算括号内的值 -- 递归调用了
            //下一个令牌标记为右括号
            Match_token_rules(obj, TOKENIZER_RPAREN);
            break;
            //左括号和数字以外的令牌（乘除加减）交由递归调用的函数去处理
        default:
            calc->error_code = syntax_error;
            LV_UNUSED(calc->error_code);
    }

    // Returns the value of the factor
    return r;
}

/**
 * @brief  计算第二优先级的数据：乘或者除以
 * @note   
 * @param  obj: 
 * @retval 
 */
static int calculator_second_level_priority(lv_obj_t* obj)
{
    Calculator_t * calc = (Calculator_t *)obj;
    int f1, f2;
    Calculator_token_t op;

    // 获得左操作数，去计算第三优先级的内容，也就是( )
    f1 = calculator_third_level_priority(obj);

    // Get operator
    op = calc->current_token;

    // Operators can only be multiply or divide (same priority)
    while (op == TOKENIZER_ASTR || op == TOKENIZER_SLASH)
    {
        // Next token
        calculator_tokenizer_next(obj);

        // 右操作数
        f2 = calculator_third_level_priority(obj);
        switch ((int)op)
        {
            case TOKENIZER_ASTR:
                f1 = f1 * f2;
                break;
            case TOKENIZER_SLASH:
                f1 = f1 / f2;
                break;
        }
        // The value calculated above will be used as the left operand
        op = calc->current_token;
    }

    return f1;
}
////////////////////////////主////////////////////////////////
/**
 * @brief  计算表达式结果--------主要
 * @note   
 * @param  obj: 
 * @retval None
 */
static int calculator_expression(lv_obj_t* obj)
{
    Calculator_t * calc = (Calculator_t *)obj;
    int t1, t2 = 0;
    Calculator_token_t op;

    //获取第一操作数，也就是先计算高优先级的符号
    t1 = calculator_second_level_priority(obj);
    // Get operator
    op = calc->current_token;

    //第一优先级结果计算：+/-
    while (op == TOKENIZER_PLUS || op == TOKENIZER_MINUS)
    {
        // Next token
        calculator_tokenizer_next(obj);

        // 右操作数：第二操作数，一样，先去计算高优先级的
        t2 = calculator_second_level_priority(obj);
        switch ((int)op)
        {
            case TOKENIZER_PLUS:
                t1 = t1 + t2;
                break;
            case TOKENIZER_MINUS:
                t1 = t1 - t2;
                break;
        }
        op = calc->current_token;
    }

    return t1;
}

/**
 * @brief  语法分析器初始化
 * @note   
 * @param  *obj: 计算器结构体
 * @param  *expr: 表达式
 * @retval None
 */
static void calculator_tokenizer_init(lv_obj_t *obj, char *expr)
{
    Calculator_t * calc = (Calculator_t *)obj;

    calc->curr_char = calc->next_char = expr;  //指向同一表达式
    calc->current_token = calculator_get_next_token(obj);  //获取令牌并标记它

    return;
}
/******************************************内部：类构造/析构函数************************************************************* */
/////////////////////////回调函数///////////////////////////////
void calculator_btnm_changed_event_cb(lv_event_t* e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * user_data = lv_event_get_user_data(e);

    
    uint32_t id = lv_btnmatrix_get_selected_btn(obj);  //哪个按钮被点击了
    const char * txt = lv_btnmatrix_get_btn_text(obj, id); //所点击按钮对应的数据

    Calculator_t * calc = (Calculator_t *)user_data;

    if(code == LV_EVENT_VALUE_CHANGED)
    {
        // Perform operations
        if (strcmp(txt, "=") == 0)
        {
            char tmp_buff[32];
            int calc_results;

            //语法分析器初始化
            calculator_tokenizer_init(user_data, calc->calc_exp);

            //计算出表达式的结果
            calc_results = calculator_expression(user_data);

            if (calc->error_code != no_error)
            {
                // Find the error code and display the corresponding message
                for (int i = 0; i < sizeof(error_table); i++)
                {
                    if (error_table[i].error_code == calc->error_code)
                    {
                        lv_textarea_add_text(calc->ta_hist, "\n");
                        lv_textarea_add_text(calc->ta_hist, error_table[i].message);
                        lv_textarea_add_text(calc->ta_hist, "\n");
                    }
                }
                calc->error_code = no_error;
            }
            else
            {
                //将结算结果拼接在表达式后面
                lv_snprintf(tmp_buff, sizeof(tmp_buff), "%s=%d", lv_textarea_get_text(calc->ta_input), calc_results);
                lv_textarea_set_text(calc->ta_hist, tmp_buff); // 将包含计算结果的表达式同步显示在历史区域
                lv_textarea_set_text(calc->ta_input, tmp_buff); //将包含结算结果的表达式显示出来
                // Empty expression
                memset(calc->calc_exp, 0, sizeof(calc->calc_exp));
                calc->count = 0;

            }

        }
        // clear
        else if (strcmp(txt, "C") == 0)
        {
            lv_textarea_set_text(calc->ta_input, "");
            // Empty expression
            memset(calc->calc_exp, 0, sizeof(calc->calc_exp));
            calc->count = 0;
        }
        // del char
        else if (strcmp(txt, "<-") == 0)
        {
            lv_textarea_del_char(calc->ta_input);
            calc->calc_exp[calc->count-1] = '\0';
            calc->count--;
        }
        // Add char
        else
        {
            if((calc->count == 0) && (strcmp(lv_textarea_get_text(calc->ta_input), "") == 0))
                lv_textarea_set_text(calc->ta_input, "");

            lv_textarea_add_text(calc->ta_input, txt);
            strcat(&calc->calc_exp[0], txt);
            calc->count++;
        }
    }
}

//构造函数，设计计算器
static void Calculator_constructor(const lv_obj_class_t* class_p, lv_obj_t* obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");
    Calculator_t* calculator = (Calculator_t*)obj;

    calculator->curr_char = NULL;
    calculator->next_char = NULL;
    calculator->current_token = TOKENIZER_ERROR;
    calculator->error_code = no_error;
    calculator->count = 0;

    //布局设置
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);


    //上一条计算数据显示区域
    calculator->ta_hist = lv_textarea_create(obj);
    lv_obj_set_style_bg_color(calculator->ta_hist, lv_color_hex(0xffffff), 0); //背景
    lv_obj_set_style_text_color(calculator->ta_hist,lv_color_hex(0x000000) , 0); //字体颜色
    lv_obj_set_style_radius(calculator->ta_hist, 0, 0);

    lv_obj_set_size(calculator->ta_hist, 240, 35); //历史计算文本框大小
    lv_textarea_set_cursor_click_pos(calculator->ta_hist, false); //关标定位禁用
    lv_textarea_set_max_length(calculator->ta_hist, 32);  //上一次计算结果显示，表达式最长长度为32
    lv_textarea_set_align(calculator->ta_hist, LV_TEXT_ALIGN_RIGHT);
    lv_textarea_set_text(calculator->ta_hist, "");
    lv_textarea_set_placeholder_text(calculator->ta_hist, "CALC HISTORY\t\t"); //占位符
    lv_obj_set_style_border_width(calculator->ta_hist, 0, 0);
    lv_obj_clear_flag(calculator->ta_hist, LV_OBJ_FLAG_SCROLLABLE);  //取消滚动


    //正在计算数据的显示区域
    calculator->ta_input = lv_textarea_create(obj);
    lv_obj_set_style_bg_color(calculator->ta_input, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_color(calculator->ta_input, lv_color_hex(0x000000), 0);
    lv_obj_set_style_radius(calculator->ta_input, 0, 0);
    lv_obj_set_style_border_width(calculator->ta_input, 0, 0);

    lv_obj_set_size(calculator->ta_input, 240, 25); //输入计算文本的显示区域大小
    lv_textarea_set_one_line(calculator->ta_input, true); //单行输入
    lv_textarea_set_cursor_click_pos(calculator->ta_input, false); //关标定位关闭
    lv_textarea_set_max_length(calculator->ta_input, 32);  //表达式最长长度
    
    lv_textarea_set_align(calculator->ta_input, LV_TEXT_ALIGN_RIGHT); //文本默认右对齐
    lv_textarea_set_text(calculator->ta_input, "");

    //按键矩阵，上面输入+历史显示框的高度为75，按键矩阵的高度为280-75 = 205
    calculator->btnmatrix = lv_btnmatrix_create(obj);
    lv_obj_set_style_radius(calculator->btnmatrix, 0, 0);
    lv_obj_set_style_border_width(calculator->btnmatrix, 0, 0);
    lv_obj_set_style_bg_color(calculator->btnmatrix, lv_color_hex(0xffffff),LV_PART_MAIN);  //背景为白
    lv_obj_set_size(calculator->btnmatrix, 240, 220);
    lv_btnmatrix_set_map(calculator->btnmatrix, btnm_map); //设置显示的按钮矩阵
    lv_obj_set_style_text_color(calculator->btnmatrix, lv_color_hex(0x000000), LV_PART_ITEMS | LV_STATE_DEFAULT); // 黑色字体
    lv_obj_set_style_bg_color(calculator->btnmatrix, lv_color_hex(0xe0e0e0), LV_PART_ITEMS | LV_STATE_DEFAULT); // 浅灰色背景
    lv_btnmatrix_set_ctrl_map(calculator->btnmatrix, ctrl_map); //设置按钮的控制属性
    lv_obj_add_event_cb(calculator->btnmatrix, calculator_btnm_changed_event_cb, LV_EVENT_VALUE_CHANGED, obj);

    LV_TRACE_OBJ_CREATE("finished");

}

//析构函数
static void Calculator_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);

}

/******************************************开放接口************************************************************* */


//计算器初始化，回去调用类内部的构造函数
lv_obj_t * Calculator_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(&Calculator_class, parent); //回去调用构造函数实现页面
    lv_obj_class_init_obj(obj);
    return obj;
}


/******************************************界面实现************************************************************* */

page_t Menu_Calculator = { Menu_CalculatorPage_screen_init, Menu_CalculatorPage_screen_deinit, &Menu_CalculatorPage };

lv_obj_t* Menu_CalculatorPage;


//回调函数
void Calculator_Return_Menu(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) //左滑回上一页
    {
        Return_Pre_Page();
    }
}

void Menu_CalculatorPage_screen_init(void)
{
    Menu_CalculatorPage = lv_obj_create(NULL);
    lv_obj_clear_flag(Menu_CalculatorPage, LV_OBJ_FLAG_SCROLLABLE);
    Calculator_create(Menu_CalculatorPage);

    lv_obj_add_event_cb(Menu_CalculatorPage, Calculator_Return_Menu, LV_EVENT_GESTURE, NULL);


}


void Menu_CalculatorPage_screen_deinit(void)
{
    //NULL
}
