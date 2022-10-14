// *****************************
// (c)2022 SalaScience
// Controling all pins of PORTA
// *****************************
#include <avr/io.h>     // library providing all i/o definitions for various AVRs
#include <util/delay.h> // library providing delay functions
int main (void)
{
    DDRA = 0xFF; // setting all pins of port A as output 
    while (1) 
    { // infinite loop
     PORTA = 0xFF;    // all bits of PORTA are set to 1
     _delay_ms(1000); // wait 1000 ms
     PORTA = 0x00;    // all bits of PORTA are set to 0
     _delay_ms(1000); // wait 1000 ms
    }
 return 0;
}

// **********************************************************************
// Alternatively, instead of changing all bits of register PORTA, you 
// can change only a single bit in order to control a single output pin
// **********************************************************************

#include <avr/io.h>
#include <util/delay.h>
int main (void)
{
    DDRA |= (1 << PA3); // setting pin PA3 of PORTA as output
    while (1) 
    { // infinite loop
     PORTA |= (1 << PA3);   // setting 1 on PA3 bit of PORTA    
     _delay_ms(1000);       // wait 1000 ms
     PORTA &=~(1 << PA3);   // setting 0 on PA3 bit of PORTA    
     _delay_ms(1000);       // wait 1000 ms
    }
 return 0;
}