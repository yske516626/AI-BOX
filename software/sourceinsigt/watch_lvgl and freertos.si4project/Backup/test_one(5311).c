#include "lcd.h"
#include "init.h"
#include "delay.h"

void Test()
{
	LCD_Init();
	LCD_ShowChar(10, 10, 'A', 0X6B4D, 0X8410, 12, 0);
}