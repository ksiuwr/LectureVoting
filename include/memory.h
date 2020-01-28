#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdint.h>

typedef struct
{
    uint8_t plus;
    uint8_t minus;
    uint8_t egal;
} memory;

const memory * mem_get();
void mem_init();
void mem_inc_plus();
void mem_inc_minus();
void mem_inc_egal();

#endif
