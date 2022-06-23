#include "lcd.h"
#include "systick.h"

int main(void){
	
	SysTick_Init(15999,16000000);
	
	LCD_16x2_Init_Simple();
	LCD_16x2_Clear();
	Delay_Nms(1000);
	
	LCD_16x2_Test_HelloWorld();
	Delay_Nms(1000);
	LCD_16x2_Clear();
	
	
	return 0;
}