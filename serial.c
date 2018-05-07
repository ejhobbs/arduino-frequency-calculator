#include<avr/io.h>
#include <stdio.h>
#include<util/setbaud.h>
/**
 * Setup of UART ready for communication
 */
void uart_init(void) {
  /* Set Speed */
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

/* If double speed has been enabled */
#if USE_2X
  UCSR0A |= _BV(U2X0);
#else
  UCSR0A &= ~(_BV(U2X0));
#endif

  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
  UCSR0B = _BV(RXEN0) | _BV(TXEN0); /* enable rx & tx */
}
/**
 * Get char from uart
 */
char uart_getchar(FILE *stream) {
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}
/**
 * Put char into uart
 */
void uart_putchar(char c, FILE *stream) {
  if( c == '\n'){
    uart_putchar('\r', stream); /* convert newline */
  }
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
}
