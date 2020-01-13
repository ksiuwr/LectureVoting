#include "memory.h"

int counts[3] = {0, 0, 0};

void reset()
{
    counts[Plus] = 0;
    counts[Minus] = 0;
    counts[Egal] = 0;
}

void increment(vote v)
{
    ++counts[v];
}

int total()
{
    return counts[Plus] + counts[Minus] + counts[Egal];
}
