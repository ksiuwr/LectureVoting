#include "displayer.h"

const uint8_t ctrl_address = 0x38;

void disp_init()
{
    /*
    Prescaler == 1 (by default)
    When TWBR == 152, then SCL frequency == 25 kHz
    */

    i2c_init(152U);
}

void disp_send(const memory * m)
{
    uint8_t total = m->plus + m->minus + m->egal;

    i2c_start_write(ctrl_address);
    i2c_transmit(m->plus);
    i2c_transmit(m->minus);
    i2c_transmit(m->egal);
    i2c_transmit(total);
    i2c_stop();
}
