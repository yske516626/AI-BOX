#include "lcd_init.h"
#include "delay.h"
#include "spi.h"
#include "tim.h"

/*
	设计LCD显示屏的初始化，以及提供对LCD寄存器操作实现显示的函数接口
*/



void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure = {0};
	
	__HAL_RCC_GPIOC_CLK_ENABLE();
 	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitStructure.Pin = LCD_RES;	 
 	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 		 //推挽输出
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//速度50MHz
 	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOB
 	HAL_GPIO_WritePin(GPIOB, LCD_RES, GPIO_PIN_SET);

	GPIO_InitStructure.Pin = LCD_DC;	 
 	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 		 //推挽输出
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//速度50MHz
 	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);	  //初始化GPIOC
 	HAL_GPIO_WritePin(GPIOC, LCD_DC, GPIO_PIN_SET);

	GPIO_InitStructure.Pin = LCD_CS;	 
 	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 		 //推挽输出
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//速度50MHz
 	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);	  //初始化GPIOD
 	HAL_GPIO_WritePin(GPIOD, LCD_CS, GPIO_PIN_SET);

}




/*
	LCD写入串行数据
*/
void LCD_WR_DATA8(u8 dat)
{
	HAL_SPI_Transmit(&hspi1,&dat,1,1);
}



