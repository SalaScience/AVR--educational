// **********************************
// (c)2022 SalaScience 
// Controling registers -- overview
// **********************************
#include <avr/io.h>     // library providing all i/o definitions for various AVRs
int main (void)
{
    PORTA |=  (1 << 3); // sets 1 on the 3rd bit of register PORTA
    PORTA &= ~(1 << 5); // sets 0 on the 5th bit of register PORTA
    
    PORTA ^= (1 << 2);  // toggles the 2nd bit of registrer PORTA
                        // toggle means that if there is 0 it becomes 1, or if there is 1 it becomes 0

    DDRA = 0xFF;        //sets all bits of register DDRA to 1 (because 0xFF = 0b11111111)
    DDRA = 0x00;        //sets all bits of register DDRA to 0 (because 0x00 = 0b00000000)

    while (1) 
    {
      // infinite loop
    }
 return 0;
}
