// ****************************************************
//  (c)2022 SalaScience
//  Interfacing switches/buttons/keys with decouncing 
// ****************************************************
// Note: Switch is connected to pin PA5 on port A. You can use any GPIO pin for that task.
#include <avr/io.h>    
#define KEY_PRESSED !(PINA & (1 << PA5))

int main (void)
{
 DDRA &= ~(1 << PA5);   // Setting PA5 pin as input. Should be used  only if you previously changed the direction of this pin.
                        // By defult all the pins are set as inputs at startup.
 uint8_t c = 0;         // counter variable
 while (1)
 {
   if ((KEY_PRESSED) && (!c)) // execute when key is pressed and counter is zero
   {
    // Do something here. This code will be executed only once after pressing the key  
     c = 250; // this value depends on the execution time of the rest of your source code
   }
   if ((!KEY_PRESSED) && (c)) c++; //increase the counter when the key is not pressed and counter is not zero
   
   // The rest of your source code
 }
 return 0;
}

