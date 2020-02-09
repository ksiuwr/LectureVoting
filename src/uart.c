#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include "utils.h"

void uart_init()
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= 1 << U2X0;  // use double speed
#else
    UCSR0A &= ~(1 << U2X0);  // do not use double speed
#endif

    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);  // enable transmitter and receiver
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);  // 8 bits data
    UCSR0C &= ~(1 << UMSEL01) & ~(1 << UMSEL00) & ~(1 << USBS0);  // asynchronous & 1 bit stop
}

uint8_t uart_read()
{
    while(~UCSR0A & (1 << RXC0))
    {
        _delay_ms(100);
    }

    return UDR0;
}

void uart_write(uint8_t data)
{
    while(~UCSR0A & (1 << UDRE0))
    {
        _delay_ms(100);
    }

    UDR0 = data;

    while(~UCSR0A & (1 << TXC0))
    {
        _delay_ms(100);
    }
}

void uart_write_dec(uint8_t number)
{
    digits dg = code_dec(number);

    if(dg.hundreds != '0')
        uart_write(dg.hundreds);

    if(dg.hundreds != '0' || dg.tens != '0')
        uart_write(dg.tens);

    uart_write(dg.ones);
}

void uart_write_hex(uint8_t number)
{
    digits dg = code_hex(number);

    uart_write(dg.hundreds);

    if(dg.tens != '0')
        uart_write(dg.tens);

    uart_write(dg.ones);
}
