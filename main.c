#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h> 

#define read1(r, o) ((r >> o) & 1)

#define CONFIG_PUB ((1<<PB0) | (1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5))
#define CONFIG_PUD ((1<<PD7) | (1<<PD6) | (1<<PD5))

// Basic time of opening and closing, that get offset
#define TIME_OPEN 7*60
#define TIME_CLOSE 19*60
#define CUTOFF_CURRENT 0
#define TICKS_MAX 1000

void debug() {
  //  PORTB &= ~(1<<PB0);
  //  _delay_ms(200);
  //  PORTB |= (1<<PB0);
  //  _delay_ms(200);
}

#include "i2c.c"

unsigned char registers[8];
signed char time_open_offset;
signed char time_close_offset;
char ticker;
int ticks_since_change;

void watchdogEnable() {
  wdt_reset();
  WDTCR |= (1<<WDP2) | (1<<WDP1) | (1<<WDP0) | (1<<WDE);
}

void watchdogDisable() {
  wdt_reset();
  WDTCR |= (1<<WDE) | (1<<WDCE);
  WDTCR = 0;
}

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

// Converts the weird notation of RTC into manageable base-10
char convertRTC10(char d) {
  return (d & 0xf) + (d & 0xf0) * 10;
}

// Reads the current time from RTC and returns minutes from midnight
int readDate() {
  readRegisters(registers);
  return (convertRTC10(registers[2]) * 60 + convertRTC10(registers[1]));
}

int getTemperature() {}
int getMotorCurrent() {}
char isOverheating() {
  return 0;//(getTemperature() > SAFE_TEMP) || (getMotorCurrent() > SAFE_CURRENT);
}

typedef enum direction {
  STOP,
  OPEN,
  CLOSE
} direction;

direction current_direction = STOP;

typedef enum failure {
  NONE,
  BLOCKED,
  LIMIT_FAILURE,
  MOTOR_FAILURE,
  TOO_LONG
} failure;

void setDirection(direction dir) {
  ticks_since_change = 0;
  current_direction = dir;

  if(current_direction == OPEN){
    PORTB &= ~(1<<PB6);
    PORTD |= (1<<PD2);
  } else if (current_direction == CLOSE){
    PORTD &= ~(1<<PD2);
    PORTB |= (1<<PB6);
  } else {
    PORTB &= ~(1<<PB6);
    PORTD &= ~(1<<PD2);
  }

}

void setOverride(char t) {}

void motorHandler() {
  static char current_failure = NONE;

  wdt_reset();
  int now = readDate();
  wdt_reset();
  direction wanted_dir = CLOSE;
  if (now > (TIME_OPEN + time_open_offset) &&
      now < (TIME_CLOSE + time_close_offset)) {
    // Open window in effect
    wanted_dir = OPEN;
  } else {
    wanted_dir = CLOSE;
  }

  if (isOverheating()) {
    setDirection(STOP); // immediately stop if safety is breached
    current_failure = BLOCKED;
    return;
  }

  wdt_reset();

  if (current_failure == BLOCKED && !isOverheating()) {
    setDirection(!wanted_dir); // try to slack a bit and then rewind
    _delay_ms(50);
    setDirection(wanted_dir);
    _delay_ms(50);
    setDirection(STOP);
    current_failure = NONE;
  }

  wdt_reset();

  if (current_failure == LIMIT_FAILURE) {
    if (ticks_since_change > TICKS_MAX) {
      setDirection(STOP);
    }

    if (wanted_dir != current_direction) {
      setDirection(wanted_dir);
      _delay_ms(1);
      if (getMotorCurrent() < CUTOFF_CURRENT) {
	      //current_failure = MOTOR_FAILURE;
      } 
    }
    
    return;
  }

  wdt_reset();
  watchdogDisable();

  if (ticks_since_change > TICKS_MAX && getMotorCurrent() > CUTOFF_CURRENT) {
    while(1);
    setDirection(STOP);
    current_failure = TOO_LONG;
  }

  if (current_direction != wanted_dir) {
    setDirection(wanted_dir);
    _delay_ms(100);
    if (getMotorCurrent() < CUTOFF_CURRENT) {
      current_failure = LIMIT_FAILURE;

      setOverride(1);
      _delay_ms(5000);
      if (getMotorCurrent() < CUTOFF_CURRENT) {
	current_failure = MOTOR_FAILURE;
      }
    }
  }
}

int main(){

  // watchdog

  // FIXME: Outputs for the motor direction set
  DDRC |= (1<<PC5) | (1<<PC4); // I2C RTC
  
  //###BLOCKOUT 
  DDRD  |=  (1<<PD2)   //fwd--enable
  //    |   (1<<PD3)   //fwd--override
        |   (1<<PD4);  //L293D-enable set out

  DDRB  |=  (1<<PB6);  //back-enable
  //    |   (1<<PB7);  //back-override


  PORTD |= (1<<PD4);   //L293D enable set high
  //###BLOCKOUT

  // Setup Input Pullup on Config DIPs
  PORTB |= CONFIG_PUB;
  PORTD |= CONFIG_PUD;

  // save offsets in minutes, [-105, 105]
  time_open_offset =
    ((read1(PINB, PB0) != 0) ? -1 : 1) *
    (read1(PIND, PD7) * 15 + read1(PIND, PD6) * 30 + read1(PIND, PD5) * 60);

  time_close_offset =
    ((read1(PINB, PB2) != 0) ? -1 : 1) *
    (read1(PINB, PB3) * 15 + read1(PINB, PB4) * 30 + read1(PINB, PB5) * 60);

  // Remove Pullup on Config (Hi-Z)
  PORTB &= ~CONFIG_PUB;
  PORTD &= ~CONFIG_PUD;

  TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024
  TIMSK |= (1 << TOIE1); // enable overflow interrupt

  _delay_ms(300);

  sei();

  while(1) {
    while(ticker != 0) {}
    watchdogEnable();
    ticker = 1;

    motorHandler();
    watchdogDisable();
  }
}

// Consider changing to Timer2 for power saving 
ISR(TIMER1_OVF_vect) {
  debug();
  ticker--;
  ticks_since_change++;
}
