#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "sys.h"

#define LCD_W 240 //宽
#define LCD_H 280 //高



#define LCD_SCL_PORT        GPIOB  //LCD_CSL > SPI_CSL
#define LCD_CSL             GPIO_PIN_3

#define LCD_SDA_PORT        GPIOB  //LCD_SDA > SPI_MOSI
#define LCD_SDA             GPIO_PIN_5

#define LCD_RES_PORT        GPIOB  
#define LCD_RES             GPIO_PIN_4

#define LCD_DC_PORT         GPIOC
#define LCD_DC              GPIO_PIN_12

#define LCD_CS_PORT         GPIOD
#define LCD_CS             GPIO_PIN_2

#define LCD_BLK_PORT         GPIOA
#define LCD_BLK              GPIO_PIN_15

#define LCD_SCL_Set() HAL_GPIO_WritePin(SCLK_PORT,SCLK_PIN,GPIO_PIN_SET)
#define LCD_SCL_ReSet() HAL_GPIO_WritePin(SCLK_PORT,SCLK_PIN,GPIO_PIN_RESET)

#define LCD_MOSI_Set() HAL_GPIO_WritePin(SDA_PORT,SDA_PIN,GPIO_PIN_SET)
#define LCD_MOSI_ReSet() HAL_GPIO_WritePin(SDA_PORT,SDA_PIN,GPIO_PIN_RESET)/

#define LCD_RES_Set()  HAL_GPIO_WritePin(RES_PORT,RES_PIN,GPIO_PIN_SET)
#define LCD_RES_ReSet()  HAL_GPIO_WritePin(RES_PORT,RES_PIN,GPIO_PIN_RESET)

#define LCD_DC_Set()   HAL_GPIO_WritePin(DC_PORT,DC_PIN,GPIO_PIN_SET)
#define LCD_DC_ReSet()   HAL_GPIO_WritePin(DC_PORT,DC_PIN,GPIO_PIN_RESET)
 		     
#define LCD_CS_Set()   HAL_GPIO_WritePin(CS_PORT,CS_PIN,GPIO_PIN_SET)
#define LCD_CS_ReSet()   HAL_GPIO_WritePin(CS_PORT,CS_PIN,GPIO_PIN_RESET)

#define LCD_BLK_Set()  HAL_GPIO_WritePin(BLK_PORT,BLK_PIN,GPIO_PIN_SET)
#define LCD_BLK_ReSet()  HAL_GPIO_WritePin(BLK_PORT,BLK_PIN,GPIO_PIN_RESET)


