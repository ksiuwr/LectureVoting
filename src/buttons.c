#include "buttons.h"
#include <avr/io.h>
#include <util/delay.h>

#define BTN_DDR DDRB
#define BTN_PORT PORTB
#define BTN_PIN PINB

#define PLUS_PIN PB0
#define MINUS_PIN PB1
#define EGAL_PIN PB2
#define RESET_PIN PB4

const uint8_t Mask = (1 << PLUS_PIN) | (1 << MINUS_PIN) | (1 << EGAL_PIN) | (1 << RESET_PIN);

pressed btn_release_(uint8_t button_pin)
{
    switch(button_pin)
    {
        case PLUS_PIN:
            mem_inc_plus();
            return VotedPlus;

        case MINUS_PIN:
            mem_inc_minus();
            return VotedMinus;

        case EGAL_PIN:
            mem_inc_egal();
            return VotedEgal;

        case RESET_PIN:
            mem_init();
            return Resetting;

        default:
            return Multiple;
    }
}

pressed btn_handle_(uint8_t button_pin)
{
    uint8_t was_multiple = 0;

    while(~BTN_PIN & Mask)
    {
        if((~BTN_PIN & Mask) != (1 << button_pin))
        {
            was_multiple = 1;
            break;
        }

        _delay_us(200);
    }

    return was_multiple ? Multiple : btn_release_(button_pin);
}

void btn_init()
{
    BTN_DDR &= ~Mask;  // set DDR on button pins to input
    BTN_PORT |= Mask;  // set PORT on buttons pins to pullup
}

pressed btn_click()
{
    switch(~BTN_PIN & Mask)
    {
        case 0:
            return No;

        case 1 << PLUS_PIN:
            return btn_handle_(PLUS_PIN);

        case 1 << MINUS_PIN:
            return btn_handle_(MINUS_PIN);

        case 1 << EGAL_PIN:
            return btn_handle_(EGAL_PIN);

        case 1 << RESET_PIN:
            return btn_handle_(RESET_PIN);

        default:
            return Multiple;
    }
}
