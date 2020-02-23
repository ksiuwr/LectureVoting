#include "show_uart.h"
#include "memory.h"

void show_uart_vote(character_t sign, number_t value)
{
    uart_write(sign);
    uart_write_dec(value);

    if(value < 100)
        uart_write(' ');

    if(value < 10)
        uart_write(' ');
}

void show_uart_all()

{
    const memory * m = mem_get();

    show_uart_vote(SIGN_PLUS, m->plus);
    uart_write(' ');
    show_uart_vote(SIGN_MINUS, m->minus);
    uart_write(' ');
    show_uart_vote(SIGN_EGAL, m->egal);
    uart_write('\r');
}

void show_uart_error()
{
    uart_write('\r');
    uart_write('\n');
    uart_write(SignError[0]);
    uart_write(SignError[1]);
    uart_write(SignError[2]);
    uart_write('\r');
    uart_write('\n');
}
