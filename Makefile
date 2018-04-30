PORT := /dev/ttyUSB0
MODEL := atmega328p
PROG := arduino
RATE := 115200
OUT := compiled
SOURCEDIR := .

SRC_FILES := $(shell find $(SOURCEDIR) -name '*.c')
OBJ_FILES=$(SRC_FILES:.c=.o)

backup:
	avrdude -F -V -c $(PROG) -p $(MODEL) -P $(PORT) -b $(RATE) -U flash:r:flash_backup.hex:i
restore:
	avrdude -F -V -c $(PROG) -p $(MODEL) -P $(PORT) -b $(RATE) -U flash:w:flash_backup.hex

flash: copy
	avrdude -F -V -c $(PROG) -p $(MODEL) -P $(PORT) -b $(RATE) -U flash:w:$(OUT).hex

compile: $(OBJ_FILES)
link: compile
	avr-gcc -mmcu=$(MODEL) $(OBJ_FILES) -o $(OUT)
copy: link
	avr-objcopy -O ihex -R .eeprom $(OUT) $(OUT).hex

clean: 
	rm *.o
	rm $(OUT)*

%.o:%.c # Compile all source files
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MODEL) -c $< -o $@
