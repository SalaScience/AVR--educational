// **********************************
//  (c)2022 SalaScience
//  Decouncing based on bit shifts
// **********************************
// Notice: Switch is connected to PA0 without pull-up resistor. Internal pull-up is used.
// LED or other device is connected to PB3 
#include <avr/io.h>
#include <util/delay.h>
#define KEY_PRESSED !(PINA & (1 << PA0))
#define VAL1 (1 << 15)
#define VAL2 ((1 << 15)|(1 << 14))

// Debouncing function based on bit shifts
uint8_t deb_switch(void)
{
 static uint16_t key = 0; 
 key = (key << 1) | (KEY_PRESSED) | VAL1;
 if (key == VAL2) return 1; 
 return 0;
} 

int main (void)
{
  PORTA |= (1 << PA0); // internal pull-up resistor at PA0 (use only if there is no external pull-up on the pin)
  DDRB |= (1 << PB3);  // output direction at PB3
  while (1)
  {
	  if (deb_switch()))
	  {
	    PORTB ^= (1 << PB3); //do something, toggle the state on PB3
    }
	  _delay_ms(1);
  }
  return 0;
}
