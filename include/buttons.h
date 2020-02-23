#ifndef BUTTONS_H_
#define BUTTONS_H_

typedef enum
{
    VotedPlus = 0,
    VotedEgal = 1,
    VotedMinus = 2,
    No = 5,
    Resetting = 6,
    Multiple = 7
} pressed;

void btn_init();
pressed btn_click();

#endif
