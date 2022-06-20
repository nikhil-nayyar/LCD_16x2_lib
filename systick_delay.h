#ifndef SYSTICK_DELAY
#define SYSTICK_DELAY

extern unsigned int tick_count;

/*
 * delay for N ms
 */ 
void delayNms(unsigned int ms);

#endif
