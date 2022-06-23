#ifndef SYSTICK
#define SYSTICK

/*	
 *  Initialize SysTick with given period
 */

void SysTick_Init(unsigned int reload_count, unsigned long clock_frequency);


/*
 * delay for N ms
 */ 
void Delay_Nms(unsigned int ms);

#endif


