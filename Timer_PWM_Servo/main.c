// ***********************************************
// (c)2022 SalaScience
// Timers -- PWM (Pulse Width Modulation) mode
// ***********************************************

// *******************************************************************************
// Servomechanism is connected to PD5 on port D (pin OC1A)
// OC1A pin is in non-inverting mode: clear (0) at BOTTOM, set (1) on compare
// In such mode:  Duty Cycle [%] = OCR1A / ICR1 * 100%
// Most of the servomechanisms work at 50Hz and react to the pulse duration:
// approx. 1 ms -- far left position
// approx. 1.5 ms -- middle position
// approx. 2 ms -- far right position
// *******************************************************************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main (void)
{
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);  // PWM 14th mode 
  TCCR1B |= (1 << CS11);                  // prescaler 8
  TCCR1A |= (1 << COM1A1);                // non-inverting mode on OC1A pin
  ICR1 = 39999;                           // ~period 20ms
  OCR1A = 2000;                           // 1ms pulse (far left position)
  DDRD |= (1 << PD5);                     // OC1A - output direction
  while (1)
  {
   _delay_ms(2000); 
   OCR1A = 4000; // far right (2 ms)
   _delay_ms(2000);
   OCR1A = 2000; // far left (1 ms)
  }
  return 0;
}
