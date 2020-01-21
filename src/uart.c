#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>

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

uint8_t uart_read_8()
{
    while((UCSR0A & (1 << RXC0)) == 0)
    {
        _delay_us(100);
    }

    return UDR0;
}

void uart_write_8(uint8_t data)
{
    while((UCSR0A & (1 << UDRE0)) == 0)
    {
        _delay_us(100);
    }

    UDR0 = data;

    while((UCSR0A & (1 << TXC0)) == 0)
    {
        _delay_us(100);
    }
}
