// *****************************
// (c)2022 SalaScience
// Interrupts -- Encoders
// *****************************

// ************************************************************************************
// Notice: Encoder is connected to pin PD3 (on port D) i.e. to external interrupt INT1,
// and to pin PB0 (on port B). Instead of PB0 you can use any GPIO pin.
// LEDs are connected to port A (pins PA0 to PA7) to indicate the position change.
// For the proper operation there should be hardware debouncing on pins PD3 and PB0
// ************************************************************************************

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t counter = 4; 

ISR(INT1_vect)
{
	if (PINB & (1 << PB0)) counter++; else counter--;
}

int main (void)
{
	sei(); 					// sets I-bit in SREG, globally enables interrupts
	MCUCR |= (1 << ISC11); 	// falling edge
	GICR |= (1 << INT1); 	// enable INT1
	DDRA |= 0xFF; 			// output direction for LEDs

	// **********************************************************
	// OPTIONAL IF THERE ARE NO PULL-UP RESISTORS ON PD3 AND PB0
	// **********************************************************
	// 	PORTD |= (1 << PD3); //pull-up INT1
	// 	PORTB |= (1 << PB0); //pull-up (any other pin)
	// **********************************************************
	
	while (1)
  	{
		PORTA = (1 << counter); // to indicate the position on LEDs
  	}
 	return 0;
}