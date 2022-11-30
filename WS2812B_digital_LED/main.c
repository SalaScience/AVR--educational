// ****************************************************
//  (c)2022 SalaScience
//  Controlling digital LED WS2812B
// ****************************************************
#include <avr/io.h>
#include <util/delay.h>
// ==== USED PORT, DDR AND PIN NUMBER ================
#define UPORT PORTC
#define UDDR DDRC
#define UP PC7
// ============ PULSE DURATION IN MICROSECONDS =======
#define RESET_TIME 300
#define LONG_STATE 0.8
#define SHORT_STATE 0.4
// ===================================================

// Reset pulse
static inline void WS2812B_reset(void)
{
 UPORT &= ~(1 << UP);
 _delay_us(RESET_TIME);
}

// Sending a single bit
void WS2812B_send_bit(uint8_t bit_value)
{
 if (bit_value)
 { 
  // Sending 1
  UPORT |= (1 << UP);
  _delay_us(LONG_STATE);
  UPORT &= ~(1 << UP);
  _delay_us(SHORT_STATE);
 } else
 {
  // Sending 0 
  UPORT |= (1 << UP);
  _delay_us(SHORT_STATE);
  UPORT &= ~(1 << UP);
  _delay_us(LONG_STATE);
 }
}

// Sending a whole byte (8 bits) statring from MSB
void WS2812B_send_byte(uint8_t byte_value)
{
 for (int8_t i = 7 ; i >= 0 ; i--)
 {
  if (byte_value & (1 << i)) WS2812B_send_bit(1);
   else WS2812B_send_bit(0); 
 }
}

int main (void)
{
  // Setting high state on the data pin
  UDDR |= (1 << UP);
  UPORT |= (1 << UP);
  //Colors coded as GG RR BB (Green, Red, Blue)
  // 16 colors as there are 16 LEDs
  uint32_t colors[16] = 
  { 0x5700B7, 
    0x5700B7, 
    0x5700B7,
    0x5700B7,
    0x5700B7,
    0x5700B7,
    0x5700B7,
    0x5700B7,
    0xDDFF00,
    0xDDFF00,
    0xDDFF00,
    0xDDFF00,
    0xDDFF00,
    0xDDFF00,
    0xDDFF00,
    0xDDFF00
  }; 
  
  // Sending data to 16 LEDs
  for (uint8_t n = 0; n <= 15; n++)
  {
	 WS2812B_send_byte (((colors[n] & 0xFF0000) >> 16)/3); // Green 
	 WS2812B_send_byte (((colors[n] & 0x00FF00) >> 8)/3);  // Red
	 WS2812B_send_byte ((colors[n] & 0x0000FF)/3);         // Blue
  }
   WS2812B_reset(); 
  
  while (1)
  {
   
  }
  return 0;
}
