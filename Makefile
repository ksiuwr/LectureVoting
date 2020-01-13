ATMEGA = atmega328p
PROGRAMMER = arduino
CLOCK = 16000000UL
BAUDRATE = 9600
BAUDPROG = 115200
PORT = /dev/ttyACM0

BIN = bin
BUILD = build
INC = include
SRC = src

SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(addprefix $(BUILD)/,$(notdir $(SOURCES:.c=.o)))
ELF_FILE = $(BIN)/lecture_voting.elf
HEX_FILE = $(BIN)/lecture_voting.hex

AVRCC = avr-gcc -I$(INC) -DF_CPU=$(CLOCK) -DBAUD=$(BAUDRATE) -mmcu=$(ATMEGA) -Os
AVRDUDE = avrdude -v -p $(ATMEGA) -c $(PROGRAMMER) -P $(PORT) -b $(BAUDPROG)
AVROBJCOPY = avr-objcopy -j .text -j .data

.PHONY : all clean dirs install refresh

all : dirs $(HEX_FILE)

clean :
	rm -rf $(BUILD) $(BIN)

refresh : clean all

dirs :
	mkdir -p $(BUILD) $(BIN)

install : all
	$(AVRDUDE) -U flash:w:$(HEX_FILE):a

$(BUILD)/%.o : $(SRC)/%.c
	$(AVRCC) -c $< -o $@

$(ELF_FILE) : $(OBJECTS)
	$(AVRCC) $^ -o $@

$(HEX_FILE) : $(ELF_FILE)
	$(AVROBJCOPY) -O ihex $< $@
