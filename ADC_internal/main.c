// ===================================
// (c)2022 SalaScience
// Using internal ADC in ATmega32
// ===================================
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_lib.h"
volatile uint16_t adc_output, voltage;

ISR(ADC_vect)
{
 uint16_t ADC_L, ADC_H;
 // Reading value from ADC
 ADC_L = ADCL;
 ADC_H = ADCH & 0x03;
 adc_output = ((ADC_H << 8) + ADC_L); 
 // Vref = AVcc = 5V = 5000 mV
 // adc_output is in the range 0 -- 1023
 // voltage = ( (uint32_t) adc_output * 5000 / 1024);   // conversion to mV
 voltage = (((uint32_t) adc_output * 5000) >> 10);      // conversion to mV
}

int main (void)
{
  LCD_init();
  ADMUX |= (1 << REFS0);                                // ADC0 input, AVcc - is a reference voltage Vref
  ADCSRA |= (1 << ADIE) |  (1 << ADEN);                 // enabled ADC, enabled interrupts, single conversion
  //ADCSRA |= (1 << ADATE);                             // free-running mode
  ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // div 128 = 125kHz
  ADCSRA |= (1 << ADSC);                                // start the first conversion 
  sei();                                                // enable interrupts
  while (1)
  {
   LCD_gotoXY (0,1);
   LCD_integer(voltage);
   LCD_text(" mV   ");
   LCD_gotoXY (0,2);
   LCD_integer(adc_output);
   LCD_text("     ");
   ADCSRA |= (1 << ADSC);                               // start conversion
   _delay_ms(500);
  }
  return 0;
}