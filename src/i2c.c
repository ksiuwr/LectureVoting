#include "i2c.h"
#include <util/delay.h>
#include <util/twi.h>
#include "uart.h"

#define I2C_DDR DDRC
#define I2C_PORT PORTC
#define SDA_PIN PC4
#define SCL_PIN PC5

void i2c_wait_()
{
    while(~TWCR & (1 << TWINT))
    {
        _delay_ms(100);
    }
}

void i2c_init(uint8_t twbr)
{
    I2C_DDR &= ~(1 << SDA_PIN) & ~(1 << SCL_PIN);  // set DDR on I2C pins to input
    I2C_PORT |= (1 << SDA_PIN) | (1 << SCL_PIN);  // set PORT on I2C pins to pullup

    TWSR &= ~(1 << TWPS1) & ~(1 << TWPS0);  // Prescaler is set to 1 by default
    TWBR = twbr;  // SCL frequency = F_CPU / (16 + 2 * TWBR * Prescaler)
    TWCR = (1 << TWEN);
}

void i2c_start(uint8_t address, i2c_mode mode)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    i2c_wait_();
    i2c_write((address << 1) | mode);  // 7-bit address + mode bit
}

void i2c_stop()
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2c_write(uint8_t value)
{
    TWDR = value;
    TWCR = (1 << TWINT) | (1 << TWEN);
    i2c_wait_();
}
