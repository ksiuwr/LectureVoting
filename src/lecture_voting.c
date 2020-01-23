#include <util/delay.h>
#include "buttons.h"
#include "memory.h"
#include "uart.h"

int main()
{
    mem_init();
    btn_init();
    uart_init();

    while(1)
    {
        while(btn_pressed())
        {
            btn_click();
            _delay_ms(200);
        }

        uart_write('+');
        uart_write_dec(mem_get()->plus);
        uart_write(' ');
        uart_write('-');
        uart_write_dec(mem_get()->minus);
        uart_write(' ');
        uart_write('?');
        uart_write_dec(mem_get()->egal);
        uart_write('\r');
        _delay_ms(100);
    }

    return 0;
}
