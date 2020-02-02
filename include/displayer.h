#ifndef DISPLAYER_H_
#define DISPLAYER_H_

#include <stdint.h>
#include "i2c.h"
#include "memory.h"

#define PCF8574 0x27
#define PCF8574A 0x3f
#define DEVICE PCF8574A

void disp_init();
void disp_end();
void disp_clear_all();
void disp_move(uint8_t row, uint8_t col);
void disp_clear_line(uint8_t line, uint8_t max_cols);
void disp_write_char(uint8_t character);
void disp_write_dec(uint8_t number);
void disp_write_hex(uint8_t number);

#endif
