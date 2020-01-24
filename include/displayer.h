#ifndef DISPLAYER_H_
#define DISPLAYER_H_

#include <stdint>
#include "i2c.h"
#include "memory.h"

void disp_init();
void disp_send(uint8_t data);

#endif
