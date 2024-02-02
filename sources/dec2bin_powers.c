#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 66 /* 8 bits per byte, 8 bytes total plus a '\n' and '\0' */ 
#include "../include/my_functions.h"

/* dec2bin: translate decimal integer to binary */

int get_line(char [], int, const char []);
int get_power(const unsigned, long);
int dtob(long, char []);

int main(void) {
  const unsigned char msg[] = "Enter decimal number:";
  unsigned char buf[BUFSIZE] = {'\0'};
  long number = 0;
  unsigned len = 0;
  int i, j = 0;

  while (len = get_line(buf, BUFSIZE, msg)) {
    for (i = len; i >= 0; --i) {
      if (isdigit(buf[i]))
        number += power(10, i) * (buf[j++] - '0');
    }
    printf("Decimal number is: %d\n", number);
    if (dtob(number, buf) >= 0)
      printf("Binary number is %s\n", buf);

    number = 0; /* reset */
    j = 0;
  }
  return 0;
}

/* get_power: determine most closer power of number */
int get_power(const unsigned base, long number) {
  int n = 32;
  long p = 0;

  for (n = 32; n > 0 && (p = power(base, n)) > number; --n);

  return n;
}

/* dtob: transform the decimal integer to an its binary character representation */
int dtob(long number, char res[]) {
  const unsigned base = 2;
  long sub = number;
  int n_max = 0;
  int n = 0;
  
  for (n = 0; n < BUFSIZE; n++) res[n] = '\0'; /* reset */

  n_max = get_power(base, number);
  for (n = n_max; n >= 0; --n) {
    res[n] = '0';
  }
  n = 0;
  while (sub > 0) {
    if ((n = get_power(base, sub)) >= 0)
       res[n] = '1';

    sub -= power(base, n);
  }

  reverse(res, n_max);
  return n_max;
}
