#ifndef SYSTICK
#define SYSTICK

/*
 *  Write to relevant Systick Registers
 */

void SysTick_Init(void);

/*
 * Overwrite base Systick Interrupt Handler
 */

void SysTick_Handler(void);

#endif
