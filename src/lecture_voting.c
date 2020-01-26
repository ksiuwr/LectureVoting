#include <util/delay.h>
#include "buttons.h"
#include "displayer.h"
#include "memory.h"
#include "uart.h"

void show_status_uart()
{
    uart_write('+');
    uart_write_dec(mem_get()->plus);
    uart_write(' ');
    uart_write('-');
    uart_write_dec(mem_get()->minus);
    uart_write(' ');
    uart_write('?');
    uart_write_dec(mem_get()->egal);
    uart_write('\r');
}

void show_status_disp()
{
    disp_move(0, 0);
    disp_write_char('+');
    disp_write_dec(mem_get()->plus);
    disp_write_char(' ');
    disp_write_char('-');
    disp_write_dec(mem_get()->minus);
    disp_write_char(' ');
    disp_write_char('?');
    disp_write_dec(mem_get()->egal);
}

int main()
{
    mem_init();
    uart_init();
    btn_init();
    disp_init();

    while(1)
    {
        show_status_disp();
        _delay_ms(1000);
    }

    return 0;
}
