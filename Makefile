ATMEGA = atmega328p
PROGRAMMER = arduino
CLOCK = 16000000UL
BAUDRATE = 9600
BAUDPROG = 115200
PORT = /dev/ttyACM0

SRC = src
BIN = bin
BUILD = build
OBJECTS = $(wildcard $(BUILD)/*.o)

AVRCC = avr-gcc -DF_CPU=$(CLOCK) -DBAUD=$(BAUDRATE) -mmcu=$(ATMEGA) -Os
AVRDUDE = avrdude -v -p $(ATMEGA) -c $(PROGRAMMER) -P $(PORT) -b $(BAUDPROG)
AVROBJCOPY = avr-objcopy -j .text -j .data

all : prepare $(BIN)/lecture_voting.hex

clean :
	rm -rf $(BUILD) $(BIN)

refresh : clean all

prepare :
	mkdir -p $(BUILD) $(BIN)

install : all
	$(AVRDUDE) -U flash:w:$(BIN)/lecture_voting.hex:a

$(BUILD)/%.o : $(SRC)/%.c
	$(AVRCC) -c $< -o $@

$(BIN)/lecture_voting.elf : $(OBJECTS)
	$(AVRCC) $^ -o $@

$(BIN)/%.hex : $(BIN)/%.elf
	$(AVROBJCOPY) -O ihex $< $@
