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

int main()
{
    mem_init();
    uart_init();
    btn_init();
    disp_init();

    return 0;
}
