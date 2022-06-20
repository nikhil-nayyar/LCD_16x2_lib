#include "systick_delay.h"
#include "systick.h"
#include "tm4c123gh6pm.h"

unsigned int tick_count;


void delayNms(unsigned int ms){
	
	tick_count = ms;
	while(tick_count != (unsigned int) 0){}

}
