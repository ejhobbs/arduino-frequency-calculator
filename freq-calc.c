#include <avr/io.h>
#include "millis.h"

void setFreq(unsigned long *freq, unsigned long *count);

int main (void) {
  unsigned long now = millis();
  unsigned long freq = 0;
  unsigned long count = 0;
  DDRB = 0x00; // Set all 'B' ports to input
  while(1) {
    /* Pin 12 high? */
    if (PINB & (1<<PINB4)){
      count++;
    }
    /* 1s since last frequency check? */
    if((millis() - now) > 1000){
      setFreq(&freq, &count);
    }
  }
}

/**
 * If frequency is 0, set it to current value
 * Otherwise, add it to current and divide by two
 * will build up an avg over time and ideally level the
 * value out a bit
*/
void setFreq(unsigned long *freq, unsigned long *count){
  if(*freq != 0){
    *freq = (*freq+*count)/2;
  } else {
    *freq = *count;
  }
}
