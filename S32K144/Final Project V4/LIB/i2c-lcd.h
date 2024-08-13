#ifndef __I2CLCD_H
#define __I2CLCD_H

#include "main.h"

#define _LCD_CLEAR				      1    		
#define _LCD_RETURN_HOME		    2
#define _LCD_ENTRY_MODE			    6
#define _LCD_TURN_OFF			      8
#define _LCD_TURN_ON			      12
#define _LCD_CURSOR_OFF			    12 	  
#define _LCD_UNDERLINE_ON		    14
#define _LCD_BLINK_CURSOR_ON	  15
#define _LCD_MOVE_CURSOR_LEFT	  16
#define _LCD_MOVE_CURSOR_RIGHT	17
#define _LCD_SHIFT_LEFT			    24
#define _LCD_SHIFT_RIGHT		    28
#define _LCD_4BIT_1LINE_5x7FONT	0x20
#define _LCD_4BIT_2LINE_5x7FONT	0x28
#define _LCD_8BIT_1LINE_5x7FONT	0x30
#define _LCD_8BIT_2LINE_5x7FONT	0x38
#define _LCD_FIRST_ROW			    128
#define _LCD_SECOND_ROW			    192

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_put_cur(unsigned char row, unsigned char col);  // put cursor at the entered position row (0 or 1), col (0-15);

void lcd_clear (void);

void lcd_send_num(uint8_t data);

#endif

