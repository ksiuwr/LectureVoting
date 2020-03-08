# LectureVoting
![Release](https://img.shields.io/github/v/release/ksiuwr/LectureVoting?style=plastic)
![License](https://img.shields.io/github/license/ksiuwr/LectureVoting?style=plastic)

Simple automated voting system for lectures

## About
LectureVoting is a tool designed for collecting listener's votes on presented lecture. It is based on Atmega328p microcontroller that may be found on Arduino boards. It contains of three vote buttons ("yes", "no", "don't care"), a reset button (clears votes result) and a displayer. Voting results are shown live on the displayer and optionally send via UART to an associated computer. One can see them through `minicom` tool:

```sh
minicom -D /dev/ttyACM0 -b 9600
```

If more than one button is pressed at one moment, an error symbol `_|_` is shown and no votes are counted.

The infinity symbol in the displayer informs that no votes will be counted at this moment due to results update.

-----

## Components reference

### Atmega / Arduino pinouts
+ PB0 / D8  - "yes" vote button
+ PB1 / D9 - "don't care" vote button
+ PB2 / D10  - "no" vote button
+ PD7 / D7 - reset button
+ PC4 / A4 - displayer data (SDA)
+ PC5 / A5 - displayer clock (SCL)

### Datasheets (see `doc` directory)
+ Arduino with Atmega328p microcontroller
+ HD44780 liquid crystal displayer
+ I2C converter for displayer based on PCF8574 or PCF8574A

-----

## Dependencies

### Standard build & run
Build process:
+ Linux-based operating system
+ AVR compilation utils: GCC AVR, AVR libc, AVRDude \
  *((APT packages `gcc-avr`, `binutils-avr`, `avr-libc`, `avrdude`))*
+ GNU Make \
  *((APT package `make`))*

-----

## How to build?
LectureVoting can be built using **GNU Make**.

Possible Make targets are:
+ `make`, `make all` - compile source files
+ `make clean` - remove additional build files
+ `make refresh` - remove additional build files & compile source files

## How to deploy?
First check if Arduino is connected via USB and `/dev/ttyACM0` is open. Then simply run `make install` command if sources have already been compiled. But when sources should be compiled before, then run `make reinstall` command.
