#include <util/delay.h>
#include "buttons.h"
#include "memory.h"
#include "uart.h"

int main()
{
    mem_init();
    btn_init();
    uart_init();

    while(1)
    {
        /* TODO: code */
    }

    return 0;
}
