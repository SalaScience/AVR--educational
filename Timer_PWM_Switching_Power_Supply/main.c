// ***********************************************************************
// (c)2022 SalaScience
// Timers -- PWM (Pulse Width Modulation) -- Boost Switching Power Supply
// ***********************************************************************

// ========================================================================
// Base (or Gate) of a transistor from Boost Switching Power Supply should
// be connected (through appropriate resistor) with pin PD5 on port D.
// Pulses should be short and the duty cycle should be low to decrese 
// the average current flowing through the transistor. 
// The frequency should be relatively high to get the maximum efficiency.
// The higher the duty cycle the higher the output voltage.
// ========================================================================
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{ 
  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  TCCR1A |= (1 << WGM11);                   // Fast PWM, mode 14
  TCCR1B |= (1 << CS10);                    // div 1 (prescaler) 
  TCCR1A |= (1 << COM1A1);                  // output on PD5, non-inverting mode
  ICR1 = 1000;                              // TOP value
  OCR1A = 100;                              // value of OCR1A is proportional to the duty cycle (in this case duty cycle is 10%)  
  DDRD |= (1 << PD5);                       // output direction on pin PD5 
  while (1)
  {
      // empty while loop
  }

  return 0;
}
