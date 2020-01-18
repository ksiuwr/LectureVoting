#ifndef _MEMORY_H_
#define _MEMORY_H_

typedef enum
{
    Plus = 0,
    Minus = 1,
    Egal = 2
} vote;

void mem_init();
void mem_increment(vote v);
int mem_total();

#endif
