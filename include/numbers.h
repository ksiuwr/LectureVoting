#ifndef NUMBERS_H_
#define NUMBERS_H_

#include "types.h"

typedef struct
{
    character_t hundreds;
    character_t tens;
    character_t ones;
} digits;

static inline digits code_dec(number_t number)
{
    digits d;

    d.hundreds = +'0' + (number % 1000) / 100;
    d.tens = +'0' + (number % 100) / 10;
    d.ones = +'0' + number % 10;

    return d;
}

static inline digits code_hex(number_t number)
{
    digits d;
    number_t huns_rem = (number % 4096) / 256;
    number_t tens_rem = (number % 256) / 16;
    number_t ones_rem = number % 16;

    d.hundreds = huns_rem < 10 ? +'0' + huns_rem : +'a' + huns_rem - 10;
    d.tens = tens_rem < 10 ? +'0' + tens_rem : +'a' + tens_rem - 10;
    d.ones = ones_rem < 10 ? +'0' + ones_rem : +'a' + ones_rem - 10;

    return d;
}

#endif
