#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdint.h>

typedef enum
{
    No = 0,
    Voted = 1,
    Resetting = 2,
    Multiple = 3
} pressed;

void btn_init();
pressed btn_click();

#endif
