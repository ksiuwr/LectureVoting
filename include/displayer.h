#ifndef DISPLAYER_H_
#define DISPLAYER_H_

#include <stdint.h>
#include "i2c.h"
#include "memory.h"

void disp_init();
void disp_clear();
void disp_home();
void disp_write_char(uint8_t character);
void disp_write_dec(uint8_t number);

#endif
