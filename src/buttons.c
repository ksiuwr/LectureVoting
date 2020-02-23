#include "buttons.h"
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define BTN_DDR DDRB
#define BTN_PORT PORTB
#define BTN_PIN PINB

#define RESET_DDR DDRD
#define RESET_PORT PORTD
#define RESET_PIN PIND

#define PLUS_PINOUT PB0
#define EGAL_PINOUT PB1
#define MINUS_PINOUT PB2
#define RESET_PINOUT PD7

const uint8_t VotesMask = (1 << PLUS_PINOUT) | (1 << EGAL_PINOUT) | (1 << MINUS_PINOUT);
const uint8_t ResetMask = (1 << RESET_PINOUT);

pressed btn_handle_(uint8_t button_pin)
{
    uint8_t was_multiple = 0;

    while(~BTN_PIN & VotesMask)
    {
        if((~BTN_PIN & VotesMask) != (1 << button_pin))
            return Multiple;

        _delay_us(200);
    }

    switch(button_pin)
    {
        case PLUS_PINOUT:
            return VotedPlus;

        case EGAL_PINOUT:
            return VotedEgal;

        case MINUS_PINOUT:
            return VotedMinus;

        default:
            return Multiple;
    }
}

void btn_init()
{
    /*
     * set DDR on button pins to input
     * set PORT on buttons pins to pullup
     */

    BTN_DDR &= ~VotesMask;
    BTN_PORT |= VotesMask;

    RESET_DDR &= ~ResetMask;
    RESET_PORT |= ResetMask;
}

pressed btn_click()
{
    if(RESET_PIN & ResetMask)
        return Resetting;

    switch(~BTN_PIN & VotesMask)
    {
        case 0:
            return No;

        case 1 << PLUS_PINOUT:
            return btn_handle_(PLUS_PINOUT);

        case 1 << EGAL_PINOUT:
            return btn_handle_(EGAL_PINOUT);

        case 1 << MINUS_PINOUT:
            return btn_handle_(MINUS_PINOUT);

        default:
            return Multiple;
    }
}
