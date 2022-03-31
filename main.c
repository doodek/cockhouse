#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void debug() {
        PORTB &= ~(1<<PB0);
        _delay_ms(200);
        PORTB |= (1<<PB0);
        _delay_ms(200);
}

#include "i2c.c"

unsigned char registers[8];

void setupDate() {
    writeRegister(6, 0x22); // year
    writeRegister(5, 0x03); // month
    writeRegister(4, 0x31); // day
    writeRegister(3, 4); // day of week
    writeRegister(2, 0x19); // hour
    writeRegister(1, 0x20); // minute
    writeRegister(0, 0x30); // second
}

void checkDoor() {
}

int main(){

    // watchdog


    DDRB |= (1<<PB0);
    DDRC |= (1<<PC5) | (1<<PC4);
    DDRD |= (1<<PD1);

    PORTB |= (1<<PB0);

    TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024
    TIMSK |= (1 << TOIE1); // enable overflow interrupt

    _delay_ms(300);

    UCSRB |=	(1<<RXEN)	|	(1<<RXCIE)	|	(1<<TXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);  //Packet 8b

    checkDoor();

    sei();

    while(1) {
        //readRegisters(registers);   

        //PORTB ^= (1<<PB0);
        //_delay_ms(500);
    }

}

ISR(TIMER1_OVF_vect) {
    debug();
    checkDoor();
}
