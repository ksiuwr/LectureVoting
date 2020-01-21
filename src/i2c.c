#include "i2c.h"
#include <util/delay.h>
#include <util/twi.h>

void i2c_wait()
{
    while(~TWCR & (1 << TWINT))
    {
        _delay_us(100);
    }
}

void i2c_init(uint8_t twbr)
{
    TWSR &= ~(1 << TWPS1) & ~(1 << TWPS0);  // Prescaler is set to 1 by default
    TWBR = twbr;  // SCL frequency = F_CPU / (16 + 2 * TWBR * Prescaler)
    TWCR |= (1 << TWEN);
    TWCR &= ~(1 << TWIE);
}

void i2c_start_write(uint8_t address)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    TWCR &= ~(1 << TWSTO);
    i2c_wait();
    i2c_transmit((address << 1) & 0xf7);  // 7-bit address + write bit as 0
}

void i2c_stop()
{
    TWCR |= (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    TWCR &= ~(1 << TWSTA);
}

void i2c_transmit(uint8_t value)
{
    TWDR = value;
    TWCR |= (1 << TWINT) | (1 << TWEN);
    TWCR &= ~(1 << TWSTA) & ~(1 << TWSTO);
    i2c_wait();
}
