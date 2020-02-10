#ifndef BUTTONS_H_
#define BUTTONS_H_

typedef enum
{
    VotedPlus = 0,
    VotedMinus = 1,
    VotedEgal = 2,
    No = 5,
    Resetting = 6,
    Multiple = 7
} pressed;

void btn_init();
pressed btn_click();

#endif
