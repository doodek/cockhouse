MCU = atmega8a

.PHONY = flash

a.out: main.c i2c.c
	avr-gcc -mmcu=$(MCU) main.c -o a.out -O3

a.hex: a.out
	avr-objcopy -O ihex a.out a.hex

flash: a.hex
	avrdude -p atmega8a  -c stk500v2 -U flash:w:a.hex:i -P /dev/ttyUSB0