#include "displayer.h"
#include "utils.h"

const uint8_t ctrl_address = 0x3f;

void disp_init()
{
    // Prescaler == 1 (by default) ; When TWBR == 152, then SCL frequency == 25 kHz
    i2c_init(152U);
}

void disp_send()
{
    bcd dg = code_dec(134U);

    i2c_start(ctrl_address, I2C_Write);
    i2c_write(dg.hundreds);
    i2c_write(dg.tens);
    i2c_write(dg.ones);
    i2c_stop();
}
