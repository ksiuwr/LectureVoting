#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdint.h>

typedef struct
{
    uint8_t plus;
    uint8_t minus;
    uint8_t egal;
} memory;

typedef enum
{
    Plus,
    Minus,
    Egal
} vote;

const memory * mem_get();
void mem_init();
void mem_increment(vote v);
uint8_t mem_sign(vote v);

#endif
