#include "memory.h"

int counts[3] = {0, 0, 0};

void reset()
{
    counts[PLUS] = 0;
    counts[MINUS] = 0;
    counts[EGAL] = 0;
}

void increment(int index)
{
    ++counts[index];
}

int total()
{
    return counts[PLUS] + counts[MINUS] + counts[EGAL];
}
