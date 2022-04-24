#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define read1(r, o) ((r >> o) & 1)

#define CONFIG_PUB ((1<<PB0) | (1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5))
#define CONFIG_PUD ((1<<PD7) | (1<<PD6) | (1<<PD5))

// basis for start and end of the door open window
// (hour<<8)|mins
#define BASIS_START 0x0600
#define BASIS_END 0x2000

void debug() {
  //  PORTB &= ~(1<<PB0);
  //  _delay_ms(200);
  //  PORTB |= (1<<PB0);
  //  _delay_ms(200);
}

#include "i2c.c"

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


int main(){

  // watchdog

  
  DDRC |= (1<<PC5) | (1<<PC4); // I2C RTC

  // Setup Input Pullup on Config DIPs
  PORTB |= CONFIG_PUB;
  PORTD |= CONFIG_PUD;

  // save offsets in minutes, [-105, 105]
  const static signed char time_start_offset =
    (read1(PINB, PB0) != 0) ? -1 : 1) *
    (read1(PIND, PD7) * 15 + read1(PIND, PD6) * 30 + read1(PIND, PD5) * 60));

  const static signed char time_end_offset =
    (read1(PINB, PB2) != 0) ? -1 : 1) *
    (read1(PINB, PB3) * 15 + read1(PINB, PB4) * 30 + read1(PINB, PB5) * 60));

  // Remove Pullup on Config (Hi-Z)
  PORTB &= ~CONFIG_PUB;
  PORTD &= ~CONFIG_PUD;

  TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024
  TIMSK |= (1 << TOIE1); // enable overflow interrupt

  _delay_ms(300);

  sei();

  while(1) {}
}

ISR(TIMER1_OVF_vect) {
  debug();
}
