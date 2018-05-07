/**
 * This code is mostly borrowed from here:
 * https://gist.github.com/adnbr/2439125
 * Used to count the number of milliseconds that have passed since boot
*/
#include<avr/interrupt.h>
#include<util/atomic.h>

#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) /8)

volatile unsigned long timer1;
/**
 * On fire of timer1 interrupt, increment counter
*/
ISR(TIMER1_COMPA_vect){
  timer1++;
}
/**
 * Return number of milliseconds since boot
*/
unsigned long millis() {
  unsigned long now;

  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    now = timer1;
  }

  return now;
}
/**
 * Set up registers for clock to function, and enable interrupts
*/
void init() {
  TCCR1B |= (1 << WGM12) | (1 << CS11);

  OCR1AH = (CTC_MATCH_OVERFLOW >> 8);
  OCR1AL = (CTC_MATCH_OVERFLOW);

  TIMSK1 |= (1 << OCIE1A);

  sei();
}
