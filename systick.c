#include "systick.h"
#include "tm4c123gh6pm.h"

static volatile unsigned int delay_count;
static volatile unsigned short delay_flag;

void SysTick_Init(unsigned int period){
	
	// reconfigure systick for wait
	NVIC_ST_CTRL_R &=0x00; // disable systick
	NVIC_ST_CTRL_R |= 0x6; 	// enable clock source and interrupt
	
	NVIC_ST_RELOAD_R = period; 	// set period
  NVIC_ST_CURRENT_R = 0x0; 	// clear current with write
	NVIC_ST_CTRL_R |= 0x1; // 	// enable systick
	
}

void SysTick_Handler(void){
	
	delay_count -= 1;
	
	if(delay_flag && !delay_count){
		delay_flag = 0;
	}	
	
	
}

void Delay_Nms(unsigned int ms){
	
	delay_count = ms;
	delay_flag = 1;
	while(delay_flag);
	

}

