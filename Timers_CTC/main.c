// ***********************************************
// (c)2022 SalaScience
// Timers -- CTC (Clear Timer on Compare) mode
// ***********************************************

// *****************************************************************
// Notice: Timer works in CTC mode (mode 4 or 12). F_CPU is 16 MHz.
// Prescaler of 256 and TOP value of 62499 are used, 
// thus the interrupt on compare is executed every second (1 Hz).
// LEDs are connected to port A. In effect diodes are blinking
// with a frequency of 1 Hz.
// *****************************************************************

#include <avr/io.h>
#include <avr/interrupt.h>

// ISR = Interrupt Service Routine
ISR (TIMER1_COMPA_vect)
{
  PORTA ^= 0xFF;                           // change (toggle) state on all pins of port A
}

int main (void)
{
  // TCCR1B |= (1 << WGM12);                // CTC mode 4
  TCCR1B |= (1 << WGM12) | (1 << WGM13);    // CTC mode 12
  TCCR1B |= (1 << CS12);                    // divider (prescaler) 256
  // OCR1A = 62499;                         // TOP value (CTC mode 4) -- 16-bit register 
  ICR1 = 62499;                             // TOP value (CTC mode 12) -- 16-bit register 
  TIMSK |= (1 << OCIE1A);                   // Enable timer interrupt
  DDRA = 0xFF;                              // Direction of port A 
  sei();                                    // Interrupts globally enabled (set I-bit in SREG)
 
  while (1)
  {
    // empty while loop
  }
  return 0;
}