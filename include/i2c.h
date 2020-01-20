#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void i2c_init(uint8_t twbr);
void i2c_start_write(uint8_t address);
void i2c_stop();
void i2c_transmit(uint8_t value);

#endif
