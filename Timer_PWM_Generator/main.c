// ****************************************************
// (c)2022 SalaScience
// Timers -- PWM (Pulse Width Modulation) -- Generator
// ****************************************************

// ===========================================================
// Signal is generated on pin PD5 (port D). There should be
// a low-pass filter (e.g. RC cell) on this pin
// ===========================================================

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#define DATA_POINTS 200
#define MAX_AMPLITUDE 200

uint16_t data [DATA_POINTS];

ISR(TIMER1_COMPA_vect)
{
 static uint16_t index1 = 0;
 index1++;
 if (index1 >= DATA_POINTS) index1 = 0;
 OCR1A = data[index1];
}

int main (void)
{ 
  TCCR1B |= (1 << WGM13);
  TCCR1A |= (1 << WGM11);     // mode 10, phase correct PWM
  TCCR1B |= (1 << CS10);      // div 1 (prescaler), in our case F_CPU = 16MHz
  TCCR1A |= (1 << COM1A1);    // PD5 
  TIMSK |= (1 << OCIE1A);     // enable interrupt
  ICR1 = MAX_AMPLITUDE;       // TOP value is equal to the maximum length of the pulse which affects both the maximum amplitude and PWM frequency
  OCR1A = ICR1 / 2;           // we start with 50% duty cycle
  DDRD |= (1 << PD5);         // output on PD5
  
  // ======= Example -- Triangle signal ====
  data[0] = 0;
  for (uint16_t i = 1; i <= DATA_POINTS -1 ; i++)
  {
    if (i <= DATA_POINTS /2)
	  {
	    data[i] = data[i-1]+1;
	  } else data[i] = data[i-1]-1;
  }
  // =======================================
  sei();                      // globally enable interrupts
  
  while (1)
  {
    // empty while loop
  }
  return 0;
}