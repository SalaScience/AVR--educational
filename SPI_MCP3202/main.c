// ===================================
// (c)2023 SalaScience
// SPI bus -- using MCP3202 (ADC)
// ===================================
#include <avr/io.h>
#include "lcd_lib.h"
#include <util/delay.h>
#define SET_CS PORTB |= (1 << PB4)
#define CLR_CS PORTB &=~(1 << PB4)
//SPI
void SPI_init(void)
{
 DDRB = (1 << PB5) | (1 << PB7) | (1 << PB4);
 SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);       // F_CPU/16
}

uint8_t SPI_transceive (uint8_t data)
{
 SPDR = data;
 while(!(SPSR & (1 << SPIF)));
 return SPDR;
}

int main (void)
{
 LCD_init();
 SPI_init();
 SET_CS;
 while (1)
 {
   CLR_CS;                                            // beginning of communication
   SPI_transceive(0x01);                              // start bit
   uint8_t temp_H = SPI_transceive(0x80);             // single ended, CH0 and receiving data (high byte)
   uint8_t temp_L = SPI_transceive(0x00);             // receiving data (low byte)
   uint16_t value = temp_L + ((temp_H & 0x0F) << 8);  // output value
   SET_CS;                                            // end of communication
   LCD_clear();
   LCD_integer(value);
   _delay_ms(500);
 }
 return 0;
}
