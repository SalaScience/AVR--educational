// ****************************************************
//  (c)2022 SalaScience
//  Controlling a stepper motor
// ****************************************************
// Notice: stepper motor driver is connected to port A via PA0, PA1, PA2 and PA3 pins
// You can use either single phase or two-phase scheme
#include <avr/io.h>
#include <util/delay.h>
#define MOTOR_DELAY 3
int main (void)
{
  DDRA = 0x0F; // output direction on pins from 0 to 4 of port A
  while (1)
  { 
    // ===== Single phase scheme ======
    for (uint8_t i = 0; i < 4; i++)
    {
     PORTA = (1 << i);
     _delay_ms(MOTOR_DELAY);
    }
    // ================================

    // ====== Two-phase scheme ========
    for (uint8_t i = 0; i < 3; i++)
    {
     PORTA = (3 << i);
     _delay_ms(MOTOR_DELAY);
    }
    PORTA = 9;
    _delay_ms(MOTOR_DELAY);
    // ================================
  }
  return 0;
}
