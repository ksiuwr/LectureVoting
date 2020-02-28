#include "show_uart.h"
#include "memory.h"

void show_one_vote_(character_t sign, number_t value)
{
    uart_write(sign);
    uart_write_dec(value);
}

void show_uart_vote(character_t sign, number_t value)
{
    if(UART_ENABLED)
    {
        show_one_vote_(sign, value);
        uart_write('\r');
        uart_write('\n');
    }
}

void show_uart_all()
{
    if(UART_ENABLED)
    {
        const memory * m = mem_get();

        show_one_vote_(SIGN_PLUS, m->plus);
        uart_write(' ');
        show_one_vote_(SIGN_EGAL, m->egal);
        uart_write(' ');
        show_one_vote_(SIGN_MINUS, m->minus);
        uart_write('\r');
        uart_write('\n');
    }
}

void show_uart_error()
{
    if(UART_ENABLED)
    {
        uart_write(SignError[0]);
        uart_write(SignError[1]);
        uart_write(SignError[2]);
        uart_write('\r');
        uart_write('\n');
    }
}
