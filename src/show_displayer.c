#include "show_displayer.h"
#include "memory.h"

const vote_place PlacePlus = {.column = 0, .sign = SIGN_PLUS};
const vote_place PlaceEgal = {.column = 5, .sign = SIGN_EGAL};
const vote_place PlaceMinus = {.column = 10, .sign = SIGN_MINUS};

void show_vote_(vote_place place, number_t value)
{
    disp_move(0, place.column);
    disp_write_char(place.sign);
    disp_write_dec(value);

    if(value == 0)
    {
        disp_write_char(' ');
        disp_write_char(' ');
    }
}

void show_disp_vote(vote_place place, number_t value)
{
    disp_move(1, 0);
    disp_write_char(SignWaiting);
    show_vote_(place, value);
    disp_clear_line(1, 1);
}

void show_disp_all()
{
    const memory * m = mem_get();

    disp_move(1, 0);
    disp_write_char(SignWaiting);
    show_vote_(PlacePlus, m->plus);
    show_vote_(PlaceEgal, m->egal);
    show_vote_(PlaceMinus, m->minus);
    disp_clear_line(1, 1);
}

void show_disp_error()
{
    disp_move(1, 0);
    disp_write_char(SignError[0]);
    disp_write_char(SignError[1]);
    disp_write_char(SignError[2]);
}
