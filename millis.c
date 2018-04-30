/**
 * This code is mostly borrowed from here:
 * https://gist.github.com/adnbr/2439125
 * Used to count the number of milliseconds that have passed since boot
*/
#include<avr/interrupt.h>
#include<util/atomic.h>

volatile unsigned long timer1;
long millis_since;
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
