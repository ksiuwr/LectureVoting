#ifndef UART_H_
#define UART_H_

#include "types.h"

void uart_init();
character_t uart_read();
void uart_write(character_t data);
void uart_write_dec(number_t number);
void uart_write_hex(number_t number);

#endif
