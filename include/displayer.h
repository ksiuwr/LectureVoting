#ifndef DISPLAYER_H_
#define DISPLAYER_H_

#include "i2c.h"
#include "memory.h"

void disp_init();
void disp_send(const memory * m);

#endif
