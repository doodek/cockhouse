#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// basis for start and end of the door open window
// (hour<<8)|mins
#define BASIS_START 0x0600
#define BASIS_END 0x2000

void debug() {
        PORTB &= ~(1<<PB0);
        _delay_ms(200);
        PORTB |= (1<<PB0);
        _delay_ms(200);
}

#include "i2c.c"

// Two limiting switches
// Bottom | Top
// MSB 1  | 0 LSB
typedef enum doorState {
  NONE = 0, // both switches are open
  OPEN = 1, // top switch is closed, bottom is open
  CLOSE = 2, // bottom switch is open, top is closed
  BLOCKED = 3 // both switches are closed
} doorState;

unsigned char registers[8];

// Hard codes the date in the RTC
void setupDate() {
    writeRegister(6, 0x22); // year, (20)22
    writeRegister(5, 0x03); // month, 03 - March
    writeRegister(4, 0x31); // day, 31th
    writeRegister(3, 4); // day of week, Thursday
    writeRegister(2, 0x19); // hour, 19
    writeRegister(1, 0x20); // minute, 20
    writeRegister(0, 0x30); // second, 30
}

int readDate() {
  readRegisters(registers);
  return ((registers[2]<<8) | registers[1]);
}

unsigned char getTimeShift() {
  return 0;
}

doorState readLimitSwitches() {
  return NONE;
}

doorState shouldDoor() {
  int d = readDate();
  if ((BASIS_START+getTimeShift()) < d && d < (BASIS_END+getTimeShift())) // FIXME: make this correct
    return OPEN;
  return CLOSE;
}

void checkDoor() {
  doorState should = shouldDoor();
  doorState actual = readLimitSwitches();
  if (should != actual) {
    if (actual == NONE || actual == BLOCKED) {
      // fuckup, fix somehow
    } else {
      // open/close the door
    }
  }
  // everything ok
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
