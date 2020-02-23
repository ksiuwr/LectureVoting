#include "memory.h"

memory counts = {.plus = 0, .egal = 0, .minus = 0};

const memory * mem_get()
{
    return &counts;
}

void mem_init()
{
    counts.plus = 0;
    counts.egal = 0;
    counts.minus = 0;
}

void mem_inc_plus()
{
    counts.plus = (counts.plus + 1) % 1000;
}

void mem_inc_egal()
{
    counts.egal = (counts.egal + 1) % 1000;
}

void mem_inc_minus()
{
    counts.minus = (counts.minus + 1) % 1000;
}
