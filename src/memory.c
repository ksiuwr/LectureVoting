#include "memory.h"

memory counts = {0, 0, 0};

void mem_init()
{
    counts.plus = 0;
    counts.minus = 0;
    counts.egal = 0;
}

void mem_inc_plus()
{
    ++counts.plus;
}

void mem_inc_minus()
{
    ++counts.minus;
}

void mem_inc_egal()
{
    ++counts.egal;
}
