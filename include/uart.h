#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_init();
uint8_t uart_read();
void uart_write(uint8_t data);

#endif
