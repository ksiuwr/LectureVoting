#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

typedef enum
{
    I2C_Read = 0,  // mode bit for reading
    I2C_Write = 1  // mode bit for writing
} i2c_mode;

void i2c_init(uint8_t twbr);
void i2c_start(uint8_t address, i2c_mode mode);
void i2c_stop();
void i2c_write(uint8_t value);

#endif
