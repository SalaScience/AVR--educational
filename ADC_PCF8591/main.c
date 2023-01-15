// ===================================
// (c)2023 SalaScience
// Using external ADC PCF8591
// ===================================
#include <avr/io.h>
#include "lcd_lib.h"
#include <util/delay.h>
// =========================================
// Slave address + R/W bit for PCF8591 ADC
#define SLA_W 0x90
#define SLA_R 0x91
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

void I2C_send_control_byte (uint8_t data)
{
 I2C_start();
 I2C_write_byte(SLA_W);
 I2C_write_byte(data);
 I2C_stop(); 
}

uint8_t I2C_receive(void)
{
 I2C_start();
 I2C_write_byte(SLA_R);
 uint8_t temp;
 temp = I2C_read_byte(0);
 I2C_stop();
 return temp;
}

int main (void)
{
 LCD_init();
 I2C_init();
 I2C_send_control_byte(0x00);           // ADC CH0, single ended mode, 
 I2C_start();
 I2C_write_byte(SLA_R);
 uint8_t value;
 while (1)
 {
  value = I2C_read_byte(1); 
  LCD_clear();
  LCD_integer(value);
  _delay_ms(1000);
 }
 return 0;
}
