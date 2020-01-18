#include "memory.h"

int counts[3] = {0, 0, 0};

void mem_init()
{
    counts[Plus] = 0;
    counts[Minus] = 0;
    counts[Egal] = 0;
}

void mem_increment(vote v)
{
    ++counts[v];
}

int mem_total()
{
    return counts[Plus] + counts[Minus] + counts[Egal];
}
