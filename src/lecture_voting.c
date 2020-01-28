#include <util/delay.h>
#include "buttons.h"
#include "displayer.h"
#include "memory.h"
#include "uart.h"

const uint8_t COL_PLUS = 0;
const uint8_t COL_MINUS = 5;
const uint8_t COL_EGAL = 10;
const uint8_t SIGN_PLUS = '+';
const uint8_t SIGN_MINUS = '-';
const uint8_t SIGN_EGAL = '?';

void show_vote_disp(uint8_t col, uint8_t sign, uint8_t value)
{
    disp_move(0, col);
    disp_write_char(sign);
    disp_write_dec(value);
}

void show_votes_uart()
{
    const memory * m = mem_get();

    uart_write('+');
    uart_write_dec(m->plus);
    uart_write(' ');
    uart_write('-');
    uart_write_dec(m->minus);
    uart_write(' ');
    uart_write('?');
    uart_write_dec(m->egal);
    uart_write('\r');
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

void show_all()
{
    const memory * m = mem_get();

    disp_move(1, 0);
    disp_write_char(0xF3);
    show_vote_disp(COL_PLUS, SIGN_PLUS, m->plus);
    show_vote_disp(COL_MINUS, SIGN_MINUS, m->minus);
    show_vote_disp(COL_EGAL, SIGN_EGAL, m->egal);
    show_votes_uart();
    disp_clear_line(1, 1);
}

void add_vote(uint8_t col, uint8_t sign, uint8_t value)
{
    disp_move(1, 0);
    disp_write_char(0xF3);
    show_vote_disp(col, sign, value);
    show_votes_uart();
    disp_clear_line(1, 1);
}

int main()
{
    uint8_t was_error = 0;

    mem_init();
    uart_init();
    btn_init();
    disp_init();
    show_all();

    while(1)
    {
        switch(btn_click())
        {
            case VotedPlus:
                add_vote(COL_PLUS, SIGN_PLUS, mem_get()->plus);
                break;

            case VotedMinus:
                add_vote(COL_MINUS, SIGN_MINUS, mem_get()->minus);
                break;

            case VotedEgal:
                add_vote(COL_EGAL, SIGN_EGAL, mem_get()->egal);
                break;

            case No:
                if(was_error)
                    disp_clear_line(1, 3);

                was_error = 0;
                break;

            case Resetting:
                disp_clear_all();
                show_all();
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
