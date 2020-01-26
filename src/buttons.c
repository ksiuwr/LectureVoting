#include "buttons.h"
#include <avr/io.h>
#include <util/delay.h>
#include "memory.h"

#define BTN_DDR DDRB
#define BTN_PORT PORTB
#define BTN_PIN PINB

#define RESET_PIN PB0
#define PLUS_PIN PB1
#define MINUS_PIN PB2
#define EGAL_PIN PB3

const uint8_t Mask = (1 << PLUS_PIN) | (1 << MINUS_PIN) | (1 << EGAL_PIN) | (1 << RESET_PIN);

void btn_init()
{
    BTN_DDR &= ~Mask;  // set DDR on button pins to input
    BTN_PORT |= Mask;  // set PORT on buttons pins to pullup
}

void btn_pressed()
{
    uint8_t pressed_mask = ~BTN_PIN & Mask;
}
