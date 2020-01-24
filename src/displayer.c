#include "displayer.h"
#include <util/delay.h>
#include "utils.h"

#define CTRL_ADDRESS 0x3F

/* DATA FORMAT REFERENCE:
 *  P7 | P6 | P5 | P4 | P3 | P2 | P1 | P0
 * ----+----+----+----+----+----+----+----
 *  D7 | D6 | D6 | D4 | BT | E  | RW | RS
 *
 * D7, D6, D5, D4 - send data (half bit)
 * BT - backlight flag (1 / 0)
 * E - enable flag (1 / 0)
 * RW - read (1) / write (0)
 * RS - data (1) / command (0)
 */

#define RS_FLAG 0x01
#define RW_FLAG 0x02
#define E_FLAG 0x04
#define BT_FLAG 0x08

void disp_send_i2c_(uint8_t data)
{
    i2c_start(CTRL_ADDRESS, I2C_Write);
    i2c_write(data | E_FLAG);
    _delay_us(5);
    i2c_write(data & ~E_FLAG);
    _delay_us(50);
    i2c_stop();
}

void disp_init()
{
    // Prescaler == 1 (by default) ; When TWBR == 152, then SCL frequency == 25 kHz
    i2c_init(152U);
}

void disp_send_command(uint8_t cmd)
{
    uint8_t upper_data = ((cmd & 0xF0) | BT_FLAG) & ~(RW_FLAG | RS_FLAG);
    uint8_t lower_data = (((cmd & 0x0F) << 4) | BT_FLAG) & ~(RW_FLAG | RS_FLAG);

    disp_send_i2c_(upper_data);
    disp_send_i2c_(lower_data);
}

void disp_send_data(uint8_t data)
{
    uint8_t upper_data = ((data & 0xF0) | BT_FLAG | RS_FLAG) & ~RW_FLAG;
    uint8_t lower_data = (((data & 0x0F) << 4) | BT_FLAG | RS_FLAG) & ~RW_FLAG;

    disp_send_i2c_(upper_data);
    disp_send_i2c_(lower_data);
}
