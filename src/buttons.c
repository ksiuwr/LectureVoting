#include "buttons.h"
#include <avr/io.h>
#include <util/delay.h>

#define BTN_DDR DDRB
#define BTN_PORT PORTB
#define BTN_PIN PINB

#define RESET_PIN PB0
#define PLUS_PIN PB1
#define MINUS_PIN PB2
#define EGAL_PIN PB3

const int Mask = (1 << PLUS_PIN) | (1 << MINUS_PIN) | (1 << EGAL_PIN) | (1 << RESET_PIN);
int Pressed = 0;

void btn_init()
{
    BTN_DDR &= ~(1 << PLUS_PIN) & ~(1 << MINUS_PIN) & ~(1 << EGAL_PIN) & ~(1 << RESET_PIN);
    BTN_PORT |= (1 << PLUS_PIN) | (1 << MINUS_PIN) | (1 << EGAL_PIN) | (1 << RESET_PIN);
}

void btn_click()
{
    switch(~BTN_PIN & Mask)
    {
        case 0:
            Pressed = 0;
            break;

        case 1 << PLUS_PIN:
            if(~Pressed & (1 << PLUS_PIN))
            {
                Pressed = (1 << PLUS_PIN);
                mem_increment(Plus);
            }
            break;

        case 1 << MINUS_PIN:
            if(~Pressed & (1 << MINUS_PIN))
            {
                Pressed = (1 << MINUS_PIN);
                mem_increment(Minus);
            }
            break;

        case 1 << EGAL_PIN:
            if(~Pressed & (1 << EGAL_PIN))
            {
                Pressed = (1 << EGAL_PIN);
                mem_increment(Egal);
            }
            break;

        case 1 << RESET_PIN:
            if(~Pressed & (1 << RESET_PIN))
            {
                Pressed = (1 << RESET_PIN);
                mem_init();
            }
            break;

        default:
            Pressed = 0;
    }
}
