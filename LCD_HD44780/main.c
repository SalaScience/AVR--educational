// ========================================================
// (c)2022 SalaScience
// Example: Using LCD library to display text and variables
// ========================================================
#include <avr/io.h>
#include "lcd_lib.h"
#include <util/delay.h>
int main (void)
{
  LCD_init();                   // LCD initialization
  uint16_t voltage =5;
  while (1)
  {
   LCD_gotoXY(0,1);             // go to position 0 in the first row, 
   LCD_text("Voltage = ");      // displaying text
   LCD_integer(voltage);        // displaying variables
   LCD_text(" V   ");
   _delay_ms(1000);
  }
  return 0;
}
