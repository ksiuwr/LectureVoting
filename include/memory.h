#ifndef _MEMORY_H_
#define _MEMORY_H_

typedef enum
{
    Plus = 0,
    Minus = 1,
    Egal = 2
} vote;

void reset();
void increment(vote v);
int total();

#endif
