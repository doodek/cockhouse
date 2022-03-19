#include <avr/io.h>
#include <util/delay.h>

#include "i2c.c"

unsigned char registers[8];

int main(){
    DDRB |= (1<<PB0);
    DDRC |= (1<<PC5) | (1<<PC4);
    DDRD |= (1<<PD1);

    PORTB |= (1<<PB0);

    UCSRB |=	(1<<RXEN)	|	(1<<RXCIE)	|	(1<<TXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);  //Packet 8b
	
    readRegisters(registers);

    while(1) {
        readRegisters(registers);
        for (int i=0; i<8; i++) {
            while ( !( UCSRA & (1<<UDRE)) );  
            UDR = registers[i];
        }       

        PORTB ^= (1<<PB0);
        _delay_ms(500);
    }

}