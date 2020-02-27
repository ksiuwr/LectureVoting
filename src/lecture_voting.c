#include <stdint.h>
#include <util/delay.h>
#include "buttons.h"
#include "displayer.h"
#include "memory.h"
#include "show_displayer.h"
#include "types.h"
#include "uart.h"

int main()
{
    uint8_t was_error = 0;

    mem_init();
    uart_init();
    btn_init();
    disp_init();
    show_disp_all();

    while(1)
    {
        switch(btn_click())
        {
            case VotedPlus:
                if(!was_error)
                {
                    mem_inc_plus();
                    show_disp_vote(PlacePlus, mem_get()->plus);
                }

                break;

            case VotedEgal:
                if(!was_error)
                {
                    mem_inc_egal();
                    show_disp_vote(PlaceEgal, mem_get()->egal);
                }

                break;

            case VotedMinus:
                if(!was_error)
                {
                    mem_inc_minus();
                    show_disp_vote(PlaceMinus, mem_get()->minus);
                }

                break;

            case No:
                if(was_error)
                    disp_clear_line(1, 3);

                was_error = 0;
                break;

            case Resetting:
                was_error = 0;
                mem_init();
                disp_clear_all();
                show_disp_all();
                break;

            case Multiple:
                was_error = 1;
                show_disp_error();
                break;

            default:
                break;
        }

        _delay_ms(200);
    }

    disp_end();

    return 0;
}
