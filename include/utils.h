#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>

typedef struct
{
    uint8_t hundreds;
    uint8_t tens;
    uint8_t ones;
} bcd;

inline bcd code_dec(uint8_t number)
{
    bcd d;

    d.hundreds = uart_write(+'0' + (number % 1000) / 100);
    d.tens = uart_write(+'0' + (number % 100) / 10);
    d.ones = uart_write(+'0' + number % 10);

    return d;
}

#endif
