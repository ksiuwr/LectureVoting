#ifndef DISPLAYER_H_
#define DISPLAYER_H_

#include <stdint.h>
#include "i2c.h"
#include "memory.h"

void disp_init();
void disp_send_command(uint8_t cmd);
void disp_send_data(uint8_t data);

#endif
