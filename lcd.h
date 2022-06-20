#ifndef LCD_H
#define LCD_H

#define BIT4 0
#define BIT8 1
#define LINE1 0
#define LINE2 1
#define DOT40 0
#define DOT50 1

#define ON 1 
#define OFF 0
#define BLINKING 1 
#define NO_BLINKING 0 
#define CURSOR 1 
#define NO_CURSOR 0

#define INCREMENT 1
#define DECREMENT 0
#define SCROLL 1 
#define NO_SCROLL 0

#define RIGHT 1
#define LEFT 0

// --- Initialization and Reset --- //

/*
 * combines various initialization functions into one call
 */
void lcd_general_init(void);

/*
 * initializes Port A,D,F for LCD GPIO operation
 */
void lcd_init(void);

/*
 * clears LCD screen
 */
void lcd_display_clear(void);

/*
 * returns LCD screen to home
 */
void lcd_display_return(void);

  /*
  * turns display on
	*/
void lcd_display_control(unsigned char on, unsigned char cursor, unsigned char blinking);
	
 /*
 * initializes lcd functionality
 */
void lcd_display_function(unsigned char length,  unsigned char lines, unsigned char font);

/*
 * 
 */
void lcd_display_entry(unsigned char increment, unsigned char scroll);

// --- RAM and Cursor Manipulation --- //

void lcd_cursor_shift(unsigned char direction);

void lcd_set_ddram(unsigned char addr);

void lcd_display_shift(unsigned char direction);

// --- Data/Command Writing (Physical) --- //

void lcd_write_char(unsigned char input);

void lcd_write_string(char string[]);

void lcd_write_row1(char string[]);

void lcd_write_row2(char string[]);

char lcd_read_char(void);

 /*
  * writes data nibbles to respective lines
  */
void lcd_send_command(unsigned char data, unsigned char ctrl);

 /*
  * writes hiper data nibble
  */
void lcd_send_command_hi(unsigned char data);

 /*
  * writes lower data nibble
  */
void lcd_send_command_lo(unsigned char data);

 /*
  * writes control nibble
  */
void lcd_send_command_ct(unsigned char data);

void lcd_enable_off(void);

void lcd_enable_on(void);
 
 // --- Testing & Diagnostic Functions --- //
void abcd(void);

void hello_world(void);

void morbing(void);

#endif
