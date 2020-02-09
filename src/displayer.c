#include "displayer.h"
#include <util/delay.h>
#include "converter.h"
#include "utils.h"

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

typedef enum
{
    Command = 0,
    Data = 1
} reg_select;

void disp_send_4_(uint8_t half_bit, reg_select rs)
{
    uint8_t data = ((half_bit << 4) | BT_FLAG) & ~RW_FLAG;

    data = rs ? (data | RS_FLAG) : (data & ~RS_FLAG);
    i2c_write(data | E_FLAG);
    _delay_us(5);
    i2c_write(data & ~E_FLAG);
    _delay_us(50);
}

inline void disp_send_8_(uint8_t cmd, reg_select rs)
{
    disp_send_4_(cmd >> 4, rs);
    disp_send_4_(cmd & 0x0F, rs);
}

void disp_init()
{
    // Prescaler == 1 (by default) ; When TWBR == 72, then SCL frequency == 100 kHz
    i2c_init(72U);
    i2c_start(CONVERTER, I2C_Write);
    disp_send_4_(0x00, Command);
    _delay_ms(50);
    disp_send_4_(0x03, Command);
    _delay_ms(5);
    disp_send_4_(0x03, Command);
    _delay_us(200);
    disp_send_4_(0x03, Command);
    _delay_us(200);
    disp_send_4_(0x02, Command);  // 4 bit sending
    disp_send_8_(0x28, Command);  // 4 bit sending, 2 display lines, 5x8 dots
    disp_send_8_(0x08, Command);  // display off, cursor off, blinking off
    disp_clear_all();
    disp_send_8_(0x06, Command);  // moving cursor right
    disp_send_8_(0x0C, Command);  // display on, cursor off, blinking off
}

void disp_end()
{
    disp_clear_all();
    disp_send_8_(0x08, Command);  // display off, cursor off, blinking off
    i2c_stop();
}

void disp_clear_all()
{
    disp_send_8_(0x01, Command);
    _delay_ms(2);
}

void disp_move(uint8_t row, uint8_t col)
{
    uint8_t lines[2] = {0x00, 0x40};

    disp_send_8_((0x80 | lines[row]) + col, Command);
}

void disp_clear_line(uint8_t line, uint8_t max_cols)
{
    disp_move(line, 0);
    max_cols = max_cols >= 16 ? 16 : max_cols;

    for(uint8_t i = 0; i < max_cols; ++i)
        disp_write_char(' ');
}

void disp_write_char(uint8_t character)
{
    disp_send_8_(character, Data);
}

void disp_write_dec(uint8_t number)
{
    digits dg = code_dec(number);

    if(dg.hundreds != '0')
        disp_send_8_(dg.hundreds, Data);

    if(dg.hundreds != '0' || dg.tens != '0')
        disp_send_8_(dg.tens, Data);

    disp_send_8_(dg.ones, Data);
}

void disp_write_hex(uint8_t number)
{
    digits dg = code_hex(number);

    disp_send_8_(dg.hundreds, Data);  // always 'x'

    if(dg.tens != '0')
        disp_send_8_(dg.tens, Data);

    disp_send_8_(dg.ones, Data);
}
