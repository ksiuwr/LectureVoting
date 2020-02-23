#ifndef MEMORY_H_
#define MEMORY_H_

#include "types.h"

typedef struct
{
    number_t plus;
    number_t egal;
    number_t minus;
} memory;

const memory * mem_get();
void mem_init();
void mem_inc_plus();
void mem_inc_egal();
void mem_inc_minus();

#endif
