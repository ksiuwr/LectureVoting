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

void error_multiple()
{
    disp_move(1, 0);
    disp_write_char('_');
    disp_write_char('|');
    disp_write_char('_');
    uart_write('\r');
    uart_write('\n');
    uart_write('_');
    uart_write('|');
    uart_write('_');
    uart_write('\r');
    uart_write('\n');
}

void show()
{
    disp_move(1, 0);
    disp_write_char(0xF3);
    show_status_disp();
    show_status_uart();
    disp_clear_line(1, 2);
}

int main()
{
    uint8_t was_error = 0;

    mem_init();
    uart_init();
    btn_init();
    disp_init();
    show();

    while(1)
    {
        switch(btn_click())
        {
            case No:
                if(was_error)
                    disp_clear_line(1, 3);

                was_error = 0;
                break;

            case Voted:
                show();
                break;

            case Resetting:
                show();
                break;

            case Multiple:
                was_error = 1;
                error_multiple();
                break;

            default:
                break;
        }

        _delay_us(500);
    }

    disp_end();

    return 0;
}
