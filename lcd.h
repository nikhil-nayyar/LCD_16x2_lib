#ifndef LCD_H
#define LCD_H

// --- Options for LCD_16x2_Function_Config --- //
#define BIT4 0
#define BIT8 1
#define LINE1 0
#define LINE2 1
#define DOT40 0
#define DOT50 1

// --- Options for LCD_16x2_Control_Config --- //
#define ON 1 
#define OFF 0
#define BLINKING 1 
#define NO_BLINKING 0 
#define CURSOR 1 
#define NO_CURSOR 0

// --- Options for LCD_16x2_Entry_Config --- //
#define INCREMENT 1
#define DECREMENT 0
#define SCROLL 1 
#define NO_SCROLL 0

// --- Options for Scrolling and Cursor Shifting --- //
#define RIGHT 1
#define LEFT 0

// --- Options for Selecting Data/Control Ports --- //
#define PORTA  0 
#define PORTB  1
#define PORTC  2
#define PORTD  3
#define PORTE  4
#define PORTF  5
#define NO_PORT -1


// --- Initialization and Reset --- //

/*
 *  intializes LCD by making relevant function calls with default settings
 *  INPUT: N/A
 *  OUTPUT: N/A
 */
void LCD_16x2_Init_Simple(void);

/*
 * initializes Port A,D,F for LCD GPIO operation
 * INPUT: N/A
 * OUTPUT: N/A
 */
void LCD_16x2_Init_2_Ports(unsigned int DATA, unsigned int CTRL, unsigned long DATA_bits, unsigned long CTRL_bits);

/*
 * initializes Port A,D,F for LCD GPIO operation
 * INPUT: N/A
 * OUTPUT: N/A
 */
void LCD_16x2_Init_3_Ports(unsigned int LO, unsigned int HI, unsigned int CTRL, unsigned long LO_bits, unsigned long HI_bits, unsigned long CTRL_bits);

/*
 * initializes Port A,D,F for LCD GPIO operation
 * INPUT: N/A
 * OUTPUT: N/A
 */
void LCD_16x2_Init_Port_Clock(unsigned int PORT1, unsigned int PORT2, unsigned int PORT3);

/*
 * clears LCD screen
 * INPUT: N/A
 * OUTPUT: N/A
 */
void LCD_16x2_Clear(void);

/*
 * returns LCD screen to home, sets DDRAM address to 0x0
 * INPUT: N/A
 * OUTPUT: N/A
 */
void LCD_16x2_Return(void);

/*
 * configures LCD ON/OFF, cursor, and cursor blinking
 * INPUT: ON - turns display on/off | CURSOR - turns cursor on/off | BLINKING | turns blinking on/off
 * OUTPUT: N/A
*/
void LCD_16x2_Control_Config(unsigned char on, unsigned char cursor, unsigned char blinking);
	
/*
 * configures LCD bit transmission length, number of lines, and font resolution
 * INPUT: LENGTH - 4 bit or 8 bit transmission | LINES - 1 or 2 display lines | FONT - 40 bit or 50 bit res.
 * OUTPUT: N/A
 */
void LCD_16x2_Function_Config(unsigned char length,  unsigned char lines, unsigned char font);

/*
 * configures LCD behavior for DDRAM updating and display scrolling
 * INPUT: INCREMENT - increment or decrement after write | SCROLL - display scrolls with new writes
 * OUTPUT: N/A
 */
void LCD_16x2_Entry_Config(unsigned char increment, unsigned char scroll);

// --- RAM and Cursor Manipulation --- //

/*
 * instructs LCD to shift cursor without updating DDRAM address
 * INPUT: DIRECTION - shift left or right
 * OUTPUT: N/A
 */
void LCD_16x2_Cursor_Shift(unsigned char direction);

/*
 * instructs LCD to update DDRAM address
 * INPUT: ADDRESS - updated DDRAM location
 * OUTPUT: N/A
 */
void LCD_16x2_Set_DDRAM(unsigned char addr);

/*
 * instructs LCD to scroll display
 * INPUT: DIRECTION - scroll left or right
 * OUTPUT: N/A
 */
void LCD_16x2_Shift_Display(unsigned char direction);

// --- Data/Command Writing (Physical) --- //

/*
 * sends write command to LCD with given character
 * INPUT: data - character to be written to LCD display at stored DDRAM address
 * OUTPUT: N/A
 */
void LCD_16x2_Write_Character(unsigned char data);

/*
 * repeatedly sends write command to LCD with sequence of characters
 * INPUT: string - string to be written to row 1 of display
 * OUTPUT: N/A
 */
void LCD_16x2_Write_Row_1(char string[]);

/*
 * repeatedly sends write command to LCD with sequence of characters
 * INPUT: string - string to be written to row 2 of display (will not work in 1 Line mode)
 * OUTPUT: N/A
 */
void LCD_16x2_Write_Row_2(char string[]);

char lcd_read_char(void); // #TODO

/*
 * writes data nibbles to respective lines
 * INPUT: DATA - 8 data bits | CTRL - 2 data bits controlling R/S and R/W
 * OUTPUT: N/A
 */
void LCD_16x2_Transmit_Command(unsigned char data, unsigned char ctrl);

 /*
  * writes upper data nibble
  * INPUT: DATA - 4 upper bits for transmission
  * OUTPUT: N/A
  */
void LCD_16x2_Transmit_Command_HI(unsigned char data);

 /*
  * writes lower data nibble
  * INPUT: DATA - 4 lower bits for transmission
  * OUTPUT: N/A
  */
void LCD_16x2_Transmit_Command_LO(unsigned char data);

 /*
  * writes control data nibble
  * INPUT: DATA - 2 control bits for transmission
  * OUTPUT: N/A
  */
void LCD_16x2_Transmit_Command_CTRL(unsigned char data);

 /*
  * DISABLES control bit, LCD does not read command/data on lines
  * INPUT: N/A
  * OUTPUT: N/A
  */
void LCD_16x2_Enable_OFF(void);

 /*
  * ENABLES control bit, LCD does reads command/data on lines
  * INPUT: N/A
  * OUTPUT: N/A
  */
void LCD_16x2_Enable_ON(void);
 
 // --- Testing & Diagnostic Functions --- //
  /*
  * ENABLES prints 4 characters to display
  * INPUT: N/A
  * OUTPUT: N/A
  */
void LCD_16x2_Test_ABCD(void);

 /*
  * ENABLES prints hello world to row 1
  * INPUT: N/A
  * OUTPUT: N/A
  */
void LCD_16x2_Test_HelloWorld(void);

 /*
  * ENABLES test rows 1 and rows 2
  * INPUT: N/A
  * OUTPUT: N/A
  */
void LCD_16x2_Test_Morbius(void);

#endif
