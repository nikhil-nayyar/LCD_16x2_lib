#include "lcd.h"
#include <string.h>
#include "systick.h"
#include "tm4c123gh6pm.h"

// --- Global Static Variables --- //
static unsigned long* ports[6] = {(unsigned long*) 0x40004000, 
	(unsigned long*) 0x40005000, 
	(unsigned long*) 0x40006000, 
	(unsigned long*) 0x40007000, 
	(unsigned long*) 0x40024000, 
	(unsigned long*) 0x40025000
};

// --- Initialization and Reset --- //
void LCD_16x2_Init_Simple(void){
	
	unsigned int lo_port = PORTD;
	unsigned int hi_port = PORTA;
	unsigned int ct_port = PORTF;

	LCD_16x2_Init_3_Ports(lo_port, hi_port, ct_port, 0xFF, 0x3C, 0x07);
	LCD_16x2_Control_Config(ON,NO_CURSOR,NO_BLINKING);
	LCD_16x2_Entry_Config(INCREMENT,NO_SCROLL);
	LCD_16x2_Function_Config(BIT8,LINE2,DOT40);
	
}

void LCD_16x2_Init_2_Ports(unsigned int DATA, unsigned int CTRL, unsigned long DATA_bits, unsigned long CTRL_bits){
	
	// --- retrieve data and control port pointers --- //
	unsigned long* data = ports[DATA];
	unsigned long* ctrl = ports[CTRL];

	// --- initialize clock for ports DATA and CTRL ports --- // 
	LCD_16x2_Init_Port_Clock(DATA,CTRL,NO_PORT);
	
	// --- configure data ports --- // 
	*(data+0x520/4) = 0x4C4F434B; // Unlock
	*(data+0x524/4) |= DATA_bits; // Commit
	*(data+0x400/4) |= DATA_bits; // Direction 
	*(data+0x51C/4) |= DATA_bits; // Digital Enable
	*(data+0x528/4) &= ~(DATA_bits); // Analog Enable
	*(data+0x420/4) &= ~(DATA_bits); // Alternate Function Select
	
	// --- configure control ports --- // 
	*(ctrl+0x520/4) = 0x4C4F434B; // Unlock
	*(ctrl+0x524/4) |= CTRL_bits; // Commit
	*(ctrl+0x400/4) |= CTRL_bits; // Direction 
	*(ctrl+0x51C/4) |= CTRL_bits; // Digital Enable
	*(ctrl+0x528/4) &= ~(CTRL_bits); // Analog Enable
	*(ctrl+0x420/4) &= ~(CTRL_bits); // Alternate Function Select
	

}

void LCD_16x2_Init_3_Ports(unsigned int LO, unsigned int HI, unsigned int CTRL, unsigned long LO_bits, unsigned long HI_bits, unsigned long CTRL_bits){
	
	volatile unsigned long delay;
	
		// --- retrieve data and control port pointers --- //
	volatile unsigned long* lo = ports[LO];
	volatile unsigned long* hi = ports[HI];
	volatile unsigned long* ctrl = ports[CTRL];

	// --- initialize clock for ports DATA and CTRL ports --- // 
	LCD_16x2_Init_Port_Clock(LO, HI, CTRL);
	delay = SYSCTL_RCGCGPIO_R;
		
	// --- configure data ports --- // 
	*(lo+(0x520/4)) = 0x4C4F434B; // Unlock
	*(lo+0x524/4) |= LO_bits; // Commit
	*(lo+0x400/4) |= LO_bits; // Direction 
	*(lo+0x51C/4) |= LO_bits; // Digital Enable
	*(lo+0x528/4) &= ~(LO_bits); // Analog Enable
	*(lo+0x420/4) &= ~(LO_bits); // Alternate Function Select
	
	// --- configure control ports --- // 
	*(hi+(0x520/4)) = 0x4C4F434B; // Unlock
	*(hi+0x524/4) |= HI_bits; // Commit
	*(hi+0x400/4) |= HI_bits; // Direction 
	*(hi+0x51C/4) |= HI_bits; // Digital Enable
	*(hi+0x528/4) &= ~(HI_bits); // Analog Enable
	*(hi+0x420/4) &= ~(HI_bits); // Alternate Function Select
	
		// --- configure control ports --- // 
	*(ctrl+0x520/4) = 0x4C4F434B; // Unlock
	*(ctrl+0x524/4) |= CTRL_bits; // Commit
	*(ctrl+0x400/4) |= CTRL_bits; // Direction 
	*(ctrl+0x51C/4) |= CTRL_bits; // Digital Enable
	*(ctrl+0x528/4) &= ~(CTRL_bits); // Analog Enable
	*(ctrl+0x420/4) &= ~(CTRL_bits); // Alternate Function Select
	
}

void LCD_16x2_Init_Port_Clock(unsigned int PORT1, unsigned int PORT2, unsigned int PORT3){
	
	volatile unsigned long delay;
	
	unsigned int ports = (1 << PORT1) + (1 << PORT2) + (1 << PORT3);
	SYSCTL_RCGCGPIO_R = ports;
	delay = SYSCTL_RCGCGPIO_R;

}

void LCD_16x2_Clear(void){
	
	unsigned char data = 0x01;
	unsigned char control = 0x4;
	
	LCD_16x2_Transmit_Command(data, control);
}

void LCD_16x2_Return(void){

	unsigned char data = 0x2;
	unsigned char control = 0x0;
	
	LCD_16x2_Transmit_Command(data,control);
}

void LCD_16x2_Control_Config(unsigned char on, unsigned char cursor, unsigned char blinking){
	
	unsigned char data = 0x08;
	data |= (on << 2);
	data |= (cursor << 1);
	data |= (blinking << 0);
	
	
	unsigned char control = 0x0;
	
	LCD_16x2_Transmit_Command(data, control);
}

void LCD_16x2_Function_Config(unsigned char length,  unsigned char lines, unsigned char font){
	
	unsigned char data = 0x20;
	data |= (length << 4);
	data |= (lines << 3);
	data |= (font << 2);
	
	unsigned char control = 0x0;
	
	LCD_16x2_Transmit_Command(data, control);
	
}

void LCD_16x2_Entry_Config(unsigned char increment, unsigned char scroll){
	unsigned char data = 0x4;
	data |= (increment << 1);
	data |= (scroll << 0);
	unsigned char control = 0x0;
	
	LCD_16x2_Transmit_Command(data,control);
}

// --- RAM and Cursor Manipulation --- //
void LCD_16x2_Cursor_Shift(unsigned char direction){

	unsigned char control = 0x0;
	unsigned char data = 0x10;
	data |= (direction << 2);
	
	LCD_16x2_Transmit_Command(data,control);
	
}

void LCD_16x2_Set_DDRAM(unsigned char addr){
	
	unsigned char control = 0x0;
	unsigned char data = 0x80;
	data |= addr;
	
	LCD_16x2_Transmit_Command(data,control);

}

void LCD_16x2_Shift_Display(unsigned char direction){
	unsigned char control = 0x0;
	unsigned char data = 0x18;
	data |= (direction << 2);
	
	LCD_16x2_Transmit_Command(data,control);
	
}

// --- Data/Command Writing (Instruction) --- //
void LCD_16x2_Write_Character(unsigned char data){
	unsigned char control = 0x1;
	LCD_16x2_Transmit_Command(data,control);
}

void LCD_16x2_Write_Row_1(char string[]){

	// Set DDRAM to 0x00;
	LCD_16x2_Set_DDRAM(0x00);
	
	// Write string
	for(unsigned int i = 0; i < strlen(string); i++){
		LCD_16x2_Write_Character(string[i]);
	}
	
}

void LCD_16x2_Write_Row_2(char string[]){

	// Set DDRAM to 0x40;
	LCD_16x2_Set_DDRAM(0x40);
	
	// Write string
	for(unsigned int i = 0; i < strlen(string); i++){
		LCD_16x2_Write_Character(string[i]);
	}
	
}


// --- Data/Command Writing (Physical) --- //
void LCD_16x2_Transmit_Command(unsigned char data, unsigned char ctrl){
	
	unsigned char hi = (data & 0xF0) >> 4;
	unsigned char lo = (data & 0x0F);
	
	LCD_16x2_Enable_OFF();
  LCD_16x2_Transmit_Command_HI(hi);
	LCD_16x2_Transmit_Command_LO(lo);
	LCD_16x2_Transmit_Command_CTRL(ctrl);
  LCD_16x2_Enable_ON();
	Delay_Nms(10);
	LCD_16x2_Enable_OFF();
}

void LCD_16x2_Transmit_Command_HI(unsigned char data){
	data = data << 2;
	GPIO_PORTA_DATA_R = 0x0;
	GPIO_PORTA_DATA_R |= data;
}


void LCD_16x2_Transmit_Command_LO(unsigned char data){
	GPIO_PORTD_DATA_R = 0;
	GPIO_PORTD_DATA_R |= data;
}


void LCD_16x2_Transmit_Command_CTRL(unsigned char data){
	GPIO_PORTF_DATA_R = 0;
	GPIO_PORTF_DATA_R |= data;
}

void LCD_16x2_Enable_ON(){
	GPIO_PORTF_DATA_R |= 0x4;
}

void LCD_16x2_Enable_OFF(){
	GPIO_PORTF_DATA_R &= ~( (unsigned long) 0x4);
}

// --- Testing & Diagnostic Functions --- //
void LCD_16x2_Test_ABCD(void){
	LCD_16x2_Write_Character('a');
	LCD_16x2_Write_Character('b');
	LCD_16x2_Write_Character('c');
	LCD_16x2_Write_Character('d');	
}

void LCD_16x2_Test_HelloWorld(void){
	
	LCD_16x2_Write_Row_1("Hello World");
	
}

void LCD_16x2_Test_Morbius(void){
	
	LCD_16x2_Write_Row_1("It's Morbing");
	LCD_16x2_Write_Row_2("Time");
	
}
