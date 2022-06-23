#include "lcd.h"
#include "system_TM4C123.h"
#include "systick.h"

uint32_t clk;

int main(void){
	
	SysTick_Init(15999);
	
	LCD_16x2_Init_Simple();
	LCD_16x2_Clear();
	Delay_Nms(1000);
	
	LCD_16x2_Test_HelloWorld();
	Delay_Nms(1000);
	LCD_16x2_Clear();
	
	clk = SystemCoreClock;
	
	return 0;
}