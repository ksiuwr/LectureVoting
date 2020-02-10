#include <util/delay.h>
#include "buttons.h"
#include "displayer.h"
#include "memory.h"
#include "types.h"
#include "uart.h"

const character_t ColPlus = 0;
const character_t ColMinus = 5;
const character_t ColEgal = 10;
const character_t SignPlus = '+';
const character_t SignMinus = '-';
const character_t SignEgal = '?';

void show_vote_disp(uint8_t col, character_t sign, number_t value)
{
    disp_move(0, col);
    disp_write_char(sign);
    disp_write_dec(value);

    if(value == 0)
    {
        disp_write_char(' ');
        disp_write_char(' ');
    }
}

void show_vote_uart(character_t sign, number_t value)
{
    uart_write(sign);
    uart_write_dec(value);

    if(value < 100)
        uart_write(' ');

    if(value < 10)
        uart_write(' ');
}

void show_all_votes_uart()
{
    const memory * m = mem_get();

    show_vote_uart(SignPlus, m->plus);
    uart_write(' ');
    show_vote_uart(SignMinus, m->minus);
    uart_write(' ');
    show_vote_uart(SignEgal, m->egal);
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
    show_vote_disp(ColPlus, SignPlus, m->plus);
    show_vote_disp(ColMinus, SignMinus, m->minus);
    show_vote_disp(ColEgal, SignEgal, m->egal);
    show_all_votes_uart();
    disp_clear_line(1, 1);
}

void add_vote(uint8_t col, character_t sign, number_t value)
{
    disp_move(1, 0);
    disp_write_char(0xF3);
    show_vote_disp(col, sign, value);
    show_all_votes_uart();
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
        pressed p = btn_click();

        if(was_error)
            disp_clear_line(1, 3);

        was_error = 0;

        switch(p)
        {
            case VotedPlus:
                add_vote(ColPlus, SignPlus, mem_get()->plus);
                break;

            case VotedMinus:
                add_vote(ColMinus, SignMinus, mem_get()->minus);
                break;

            case VotedEgal:
                add_vote(ColEgal, SignEgal, mem_get()->egal);
                break;

            case No:
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
