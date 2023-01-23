// ===================================
// (c)2023 SalaScience
// Using RTC (Real Time Clock) PCF8563
// ===================================
#include <avr/io.h>
#include "lcd_lib.h"
#include <util/delay.h>
// =========================================
// Slave address + R/W bit for PCF8563 RTC
#define SLA_W 0xA2
#define SLA_R 0xA3
// =========================================

void I2C_init(void)
{
 // I2C frequency = 100kHz
 TWBR = 18;
 TWSR = (1 << TWPS0); // prescaler = 4 = 4^1
}

void I2C_start(void)
{
 TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
 while (!(TWCR & (1 << TWINT)));
}

void I2C_stop(void)
{
 TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void I2C_write_byte(uint8_t data)
{
 TWDR = data;
 TWCR = (1 << TWINT) | (1 << TWEN);
 while (!(TWCR & (1 << TWINT)));
}

uint8_t I2C_read_byte(uint8_t ack)
{
 if (ack)
 {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
 } else TWCR = (1 << TWINT) | (1 << TWEN);
 while (!(TWCR & (1 << TWINT)));
 return TWDR;
}

uint8_t I2C_read_data (uint8_t addr)
{
 I2C_start();
 I2C_write_byte(SLA_W);
 I2C_write_byte(addr);
 I2C_start(); 			//repeated start
 I2C_write_byte(SLA_R);
 uint8_t temp = I2C_read_byte(0);
 I2C_stop();
 return temp;
}

void I2C_send_data (uint8_t addr, uint8_t data)
{
 I2C_start();
 I2C_write_byte(SLA_W);
 I2C_write_byte(addr);
 I2C_write_byte(data);
 I2C_stop();
}

int main (void)
{
 LCD_init();
 I2C_init();

 uint8_t sec, min, hrs;
 hrs = 10;
 I2C_send_data(0x04, ((hrs / 10) << 4 )+ (hrs % 10)); // setting hours
  
 while (1)
 {
  LCD_clear();
  // reading seconds
  sec = I2C_read_data(0x02);
  sec = 10 * ((sec & 0x70) >> 4) + (sec & 0x0F);
  // reading minutes
  min = I2C_read_data(0x03);
  min = 10 * ((min & 0x70) >> 4) + (min & 0x0F);
  // reading hours
  hrs = I2C_read_data(0x04);
  hrs = 10 * ((hrs & 0x30) >> 4) + (hrs & 0x0F);
  // displaying time
  if (hrs < 10) LCD_text("0");
  LCD_integer(hrs);
  LCD_text(":");
  if (min < 10) LCD_text("0");
  LCD_integer(min);
  LCD_text(":");
  if (sec < 10) LCD_text("0");
  LCD_integer(sec);
  _delay_ms(200);
 }
 return 0;
}
