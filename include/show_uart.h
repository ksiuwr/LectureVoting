#ifndef SHOW_UART_H_
#define SHOW_UART_H_

#include "showing.h"
#include "types.h"
#include "uart.h"

#define UART_ENABLED 0

void show_uart_vote(character_t sign, number_t value);
void show_uart_all();
void show_uart_error();

#endif
