#ifndef LCD_LIB
#define LCD_LIB
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#define LCD_PORT PORTD
#define LCD_PORT_DDR DDRD
#define LCD_RS 0
#define LCD_E 1
#define LCD_D4 2
#define LCD_D5 3
#define LCD_D6 4
#define LCD_D7 5
#define SET_RS LCD_PORT |= (1 << LCD_RS);
#define SET_E LCD_PORT |= (1 << LCD_E);
#define CLR_RS LCD_PORT &= ~(1 << LCD_RS);
#define CLR_E LCD_PORT &= ~(1 << LCD_E);

void LCD_init(void);
void LCD_send_cmd(uint8_t cmd);
void LCD_send_data (uint8_t data);
void LCD_send_whole_byte(uint8_t data);
void LCD_text(char *str);
void LCD_integer(uint16_t value);
void LCD_gotoXY(uint8_t x, uint8_t y);
void LCD_clear(void);

#endif // LCD_LIB