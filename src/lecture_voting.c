#include <util/delay.h>
#include "buttons.h"
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

    _delay_ms(500);
    show_status_uart();

    while(1)
    {
        while(btn_released())
            _delay_ms(50);

        while(!btn_released())
        {
            btn_click();
            _delay_ms(200);
        }

        show_status_uart();
        _delay_ms(100);
    }

    return 0;
}
