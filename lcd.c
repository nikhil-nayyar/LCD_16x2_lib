#include "lcd.h"
#include <string.h>
#include <systick_delay.h>
#include "tm4c123gh6pm.h"

// --- Initialization and Reset --- //
void lcd_general_init(void){

	lcd_init();
	lcd_display_control(ON,NO_CURSOR,NO_BLINKING);
	lcd_display_entry(INCREMENT,NO_SCROLL);
	lcd_display_function(BIT8,LINE2,DOT40);
	
}

void lcd_init(void){
	
	// declare local variables
	volatile unsigned long delay;
	
	unsigned long activeA = 0x3C;
	unsigned long activeF = 0x07;
	unsigned long activeD = 0x0F;
	
	// --- initialize clock for ports A, D, F --- // 
	SYSCTL_RCGC2_R = 0x29;
	delay = SYSCTL_RCGCGPIO_R;
	
	// --- configure port A --- // 
	GPIO_PORTA_DIR_R = activeA;
	GPIO_PORTA_DEN_R = activeA;	
	GPIO_PORTA_AMSEL_R =0x0;
	GPIO_PORTA_AFSEL_R &= 0x0;

	// --- configure port D --- // 
	GPIO_PORTD_DIR_R = activeD;
	GPIO_PORTD_DEN_R = activeD;	
	GPIO_PORTD_AMSEL_R = 0x0;
	GPIO_PORTD_AFSEL_R &= 0x0;
	
	// --- configure port F --- // 
	GPIO_PORTF_LOCK_R  = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1;
	GPIO_PORTF_DIR_R = activeF;
	GPIO_PORTF_DEN_R = activeF;	
	GPIO_PORTF_AMSEL_R = 0x0;
	GPIO_PORTF_AFSEL_R &= 0x0;
}

void lcd_display_clear(void){
	
	unsigned char data = 0x01;
	unsigned char control = 0x4;
	
	lcd_send_command(data, control);
}

void lcd_display_return(void){

	unsigned char data = 0x2;
	unsigned char control = 0x0;
	
	lcd_send_command(data,control);
}

void lcd_display_control(unsigned char on, unsigned char cursor, unsigned char blinking){
	
	unsigned char data = 0x08;
	data |= (on << 2);
	data |= (cursor << 1);
	data |= (blinking << 0);
	
	
	unsigned char control = 0x0;
	
	lcd_send_command(data, control);
}

void lcd_display_function(unsigned char length,  unsigned char lines, unsigned char font){
	
	unsigned char data = 0x20;
	data |= (length << 4);
	data |= (lines << 3);
	data |= (font << 2);
	
	unsigned char control = 0x0;
	
	lcd_send_command(data, control);
	
}

void lcd_display_entry(unsigned char increment, unsigned char scroll){
	unsigned char data = 0x4;
	data |= (increment << 1);
	data |= (scroll << 0);
	unsigned char control = 0x0;
	
	lcd_send_command(data,control);
}

// --- RAM and Cursor Manipulation --- //
void lcd_cursor_shift(unsigned char direction){

	unsigned char control = 0x0;
	unsigned char data = 0x10;
	data |= (direction << 2);
	
	lcd_send_command(data,control);
	
}

void lcd_set_ddram(unsigned char addr){
	
	unsigned char control = 0x0;
	unsigned char data = 0x80;
	data |= addr;
	
	lcd_send_command(data,control);

}

void lcd_display_shift(unsigned char direction){
	unsigned char control = 0x0;
	unsigned char data = 0x18;
	data |= (direction << 2);
	
	lcd_send_command(data,control);
	
}

// --- Data/Command Writing (Instruction) --- //
void lcd_write_char(unsigned char data){
	unsigned char control = 0x1;
	lcd_send_command(data,control);
}

void lcd_write_row1(char string[]){

	// Set DDRAM to 0x00;
	lcd_set_ddram(0x00);
	
	// Write string
	for(unsigned int i = 0; i < strlen(string); i++){
		lcd_write_char(string[i]);
	}
	
}

void lcd_write_row2(char string[]){

	// Set DDRAM to 0x40;
	lcd_set_ddram(0x40);
	
	// Write string
	for(unsigned int i = 0; i < strlen(string); i++){
		lcd_write_char(string[i]);
	}
	
}


// --- Data/Command Writing (Physical) --- //
void lcd_send_command(unsigned char data, unsigned char ctrl){
	
	unsigned char hi = (data & 0xF0) >> 4;
	unsigned char lo = (data & 0x0F);
	
	lcd_enable_off();
  lcd_send_command_hi(hi);
	lcd_send_command_lo(lo);
	lcd_send_command_ct(ctrl);
  lcd_enable_on();
	delayNms(1);
	lcd_enable_off();
}

void lcd_send_command_hi(unsigned char data){
	data = data << 2;
	GPIO_PORTA_DATA_R = 0x0;
	GPIO_PORTA_DATA_R |= data;
}


void lcd_send_command_lo(unsigned char data){
	GPIO_PORTD_DATA_R = 0;
	GPIO_PORTD_DATA_R |= data;
}


void lcd_send_command_ct(unsigned char data){
	GPIO_PORTF_DATA_R = 0;
	GPIO_PORTF_DATA_R |= data;
}

void lcd_enable_on(){
	GPIO_PORTF_DATA_R |= 0x4;
}

void lcd_enable_off(){
	GPIO_PORTF_DATA_R &= ~( (unsigned long) 0x4);
}


// --- Testing & Diagnostic Functions --- //
void abcd(void){
	lcd_write_char('a');
	lcd_write_char('b');
	lcd_write_char('c');
	lcd_write_char('d');	
}

void hello_world(void){
	
	lcd_write_row1("Hello World");
	
}

void morbing(void){
	
	lcd_write_row1("It's Morbing");
	lcd_write_row2("Time");
	
}
