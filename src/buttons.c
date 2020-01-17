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

int Pressed = 0;

void init_buttons()
{
    BTN_DDR &= ~(1 << PLUS_PIN) & ~(1 << MINUS_PIN) & ~(1 << EGAL_PIN) & ~(1 << RESET_PIN);
    BTN_PORT |= (1 << PLUS_PIN) | (1 << MINUS_PIN) | (1 << EGAL_PIN) | (1 << RESET_PIN);
}

void on_plus()
{
    if(~BTN_PIN & (1 << PLUS_PIN))
    {
        if(~Pressed & (1 << PLUS_PIN))
        {
            Pressed |= (1 << PLUS_PIN);
            /* code here */
        }
    }
    else
    {
        Pressed &= ~(1 << PLUS_PIN);
    }
}

void on_minus()
{
    if(~BTN_PIN & (1 << MINUS_PIN))
    {
        if(~Pressed & (1 << MINUS_PIN))
        {
            Pressed |= (1 << MINUS_PIN);
            /* code here */
        }
    }
    else
    {
        Pressed &= ~(1 << MINUS_PIN);
    }
}

void on_egal()
{
    if(~BTN_PIN & (1 << EGAL_PIN))
    {
        if(~Pressed & (1 << EGAL_PIN))
        {
            Pressed |= (1 << EGAL_PIN);
            /* code here */
        }
    }
    else
    {
        Pressed &= ~(1 << EGAL_PIN);
    }
}

void on_reset()
{
    if(~BTN_PIN & (1 << RESET_PIN))
    {
        if(~Pressed & (1 << RESET_PIN))
        {
            Pressed |= (1 << RESET_PIN);
            /* code here */
        }
    }
    else
    {
        Pressed &= ~(1 << RESET_PIN);
    }
}
