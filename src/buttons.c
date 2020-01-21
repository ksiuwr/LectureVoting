#include "buttons.h"
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define BTN_DDR DDRB
#define BTN_PORT PORTB
#define BTN_PIN PINB

#define RESET_PIN PB0
#define PLUS_PIN PB1
#define MINUS_PIN PB2
#define EGAL_PIN PB3

const uint8_t Mask = (1 << PLUS_PIN) | (1 << MINUS_PIN) | (1 << EGAL_PIN) | (1 << RESET_PIN);
uint8_t Pressed = 0;

void btn_init()
{
    BTN_DDR &= ~Mask;  // set DDR on button pins to input
    BTN_PORT |= Mask;  // set PORT on buttons to pullup
}

void btn_click()
{
    switch(~BTN_PIN & Mask)
    {
        // nothing clicked
        case 0:
            Pressed = 0;
            break;

        // only PLUS clicked
        case 1 << PLUS_PIN:
            if(~Pressed & (1 << PLUS_PIN))
            {
                Pressed = 1 << PLUS_PIN;
                mem_inc_plus();
            }
            break;

        // only MINUS clicked
        case 1 << MINUS_PIN:
            if(~Pressed & (1 << MINUS_PIN))
            {
                Pressed = 1 << MINUS_PIN;
                mem_inc_minus();
            }
            break;

        // only EGAL clicked
        case 1 << EGAL_PIN:
            if(~Pressed & (1 << EGAL_PIN))
            {
                Pressed = 1 << EGAL_PIN;
                mem_inc_egal();
            }
            break;

        // only RESET clicked
        case 1 << RESET_PIN:
            if(~Pressed & (1 << RESET_PIN))
            {
                Pressed = 1 << RESET_PIN;
                mem_init();
            }
            break;

        // multiple buttons clicked
        default:
            Pressed = Mask;
            break;
    }
}
