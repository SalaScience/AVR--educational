#include "lcd_lib.h"

static inline void LCD_send_half_byte(uint8_t data)
{
 SET_E;
 if (data & (1 << 0)) LCD_PORT |= (1 << LCD_D4); else LCD_PORT &=~(1 << LCD_D4);
 if (data & (1 << 1)) LCD_PORT |= (1 << LCD_D5); else LCD_PORT &=~(1 << LCD_D5);
 if (data & (1 << 2)) LCD_PORT |= (1 << LCD_D6); else LCD_PORT &=~(1 << LCD_D6);
 if (data & (1 << 3)) LCD_PORT |= (1 << LCD_D7); else LCD_PORT &=~(1 << LCD_D7);
 CLR_E; 
}

void LCD_send_whole_byte(uint8_t data)
{
 LCD_send_half_byte(data >> 4);
 _delay_us(120);
 LCD_send_half_byte(data);
 _delay_us(120);
}

// Sending command
void LCD_send_cmd(uint8_t cmd)
{
 CLR_RS; // clear RS line (0)
 LCD_send_whole_byte(cmd);
}

// Sending data (characters/symbols)
void LCD_send_data (uint8_t data)
{
 SET_RS; // set RS line (1)
 LCD_send_whole_byte(data);
}

// Initialization
void LCD_init(void)
{
 LCD_PORT_DDR |= (1 << LCD_RS);
 LCD_PORT_DDR |= (1 << LCD_E);
 LCD_PORT_DDR |= (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6)
 | (1 << LCD_D7);
 CLR_RS;
 CLR_E;
 _delay_ms(50);
 LCD_send_half_byte(0x03);
 _delay_ms(4.1);
 LCD_send_half_byte(0x03);
 _delay_us(100);
 LCD_send_half_byte(0x03);
 _delay_us(100);
 LCD_send_half_byte(0x02);
 _delay_us(100);
 // ==== 4-bit interface ===========
 LCD_send_whole_byte( (1 << 5) | (1 << 3)); // 4-bit, 2 lines, 5x8 dots
 _delay_us(100);
 LCD_send_whole_byte(1 << 3); // display OFF
 _delay_us(100);
 LCD_send_whole_byte(1); // display clear
 _delay_ms(3);
 LCD_send_whole_byte(0x06); // entry mode, increment, no display shift
 _delay_us(100);
 LCD_send_whole_byte(0x0F); // display ON, blinking cursor
 _delay_ms(3);
}

void LCD_text(char *str)
{
 while (*str) LCD_send_data(*str++);
}

void LCD_integer(uint16_t value)
{
 char buf1[12];
 LCD_text(itoa(value, buf1, 10)); // base 10 
}

void LCD_clear(void)
{
 LCD_send_cmd(0x01);
 _delay_ms(3);
}

void LCD_gotoXY(uint8_t x, uint8_t y)
{
 uint8_t addr = 0;
 if (y == 1) addr = x;
 if (y == 2) addr = x + 0x40; // 64
 if (y == 3) addr = x + 0x54; // 84
 if (y == 4) addr = x + 0x14; // 20
 LCD_send_cmd((1 << 7) | addr);
 _delay_us(40);
}


