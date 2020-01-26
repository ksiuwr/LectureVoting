#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>

typedef struct
{
    uint8_t hundreds;
    uint8_t tens;
    uint8_t ones;
} digits;

inline digits code_dec(uint8_t number)
{
    digits d;

    d.hundreds = +'0' + (number % 1000) / 100;
    d.tens = +'0' + (number % 100) / 10;
    d.ones = +'0' + number % 10;

    return d;
}

inline digits code_hex(uint8_t number)
{
    digits d;
    uint8_t tens_rem = (number % 256) / 16;
    uint8_t ones_rem = number % 16;

    d.hundreds = +'x';
    d.tens = tens_rem < 10 ? +'0' + tens_rem : +'a' + tens_rem - 10;
    d.ones = ones_rem < 10 ? +'0' + ones_rem : +'a' + ones_rem - 10;

    return d;
}

#endif
