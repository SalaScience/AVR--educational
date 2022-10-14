#include <avr/io.h>
#include <util/delay.h>
int main (void)
{
    DDRA = 0xFF; // setting all pins of port A as output 
    while (1) 
    { // infinite loop
     PORTA = 0xFF;    // all bits of PORTA are set to 1
     _delay_ms(1000); // wait 1000 ms
     PORTA = 0x00;    // all bits of poRTA are set to 0
     _delay_ms(1000); // wait 1000 ms
    }
 return 0;
}