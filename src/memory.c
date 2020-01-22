#include "memory.h"

static memory counts = {0, 0, 0};

const memory * mem_get()
{
    return &counts;
}

void mem_init()
{
    counts.plus = 0;
    counts.minus = 0;
    counts.egal = 0;
}
void mem_increment(vote v)
{
    switch(v)
    {
        case Plus:
            ++counts.plus;
            break;

        case Minus:
            ++counts.minus;
            break;

        case Egal:
            ++counts.egal;
            break;
    }
}

uint8_t mem_sign(vote v)
{
    switch(v)
    {
        case Plus:
            return +'+';

        case Minus:
            return +'-';

        case Egal:
            return +'?';
    }
}
