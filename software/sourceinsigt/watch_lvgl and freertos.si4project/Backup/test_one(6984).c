#include "lcd.h"
#include "init.h"
#include "delay.h"

// 初始化 GPIO
static void MX_GPIOC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 开启 GPIOB 时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // 配置 GPIOB_PIN_0 为输出模式
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // 推挽输出模式
    GPIO_InitStruct.Pull = GPIO_NOPULL;           // 不使用上下拉电阻
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // 输出速度
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void Test()
{
	//LCD_Init();
	//LCD_Set_Light(30);
	//LCD_ShowChar(10, 10, 'A', 0X6B4D, 0X8410, 12, 0);


	MX_GPIOC_Init();
	// 主循环
    while (1)
    {
        // 点亮 LED（假设连接在 GPIOB_PIN_0）
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

        // 延时（可以根据需要设置延时函数）
        HAL_Delay(1000);  // 延时 1 秒

        // 熄灭 LED
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);

        // 延时（可以根据需要设置延时函数）
        HAL_Delay(1000);  // 延时 1 秒
    }
}