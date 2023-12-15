#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "../include/custom_functions.h"
#define BUFSIZE 66 /* 8 bits per byte, 8 bytes total plus a '\n' and '\0' */ 

/* dec2bin: transform a decimal integer to binary form */

unsigned power(const unsigned base, unsigned n) {
  unsigned p = 1;

  while (n > 0) {
    p *= base;
    --n;
  }
  return p;
}

int dtob(long divisible, unsigned char res[]) {
const unsigned long base = 2; /* base of bynary number system */
unsigned long remainder = 0;
int len, n;

  for (n = 0; n < BUFSIZE; n++) res[n] = '\0'; /* reset */

  for (n = 0; (power(base, n) < divisible); n++);
  if (divisible < power(base, n)) len = n - 1;
  else len = n;

  while (divisible) {
    remainder = divisible % base;
    divisible /= base;
    if (remainder) res[len] = '1';
    else res[len] = '0';
    len--;
  }

  return len; /* 1 if success, otherwise 0 */
}

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
    if (dtob(number, buf))
      printf("Binary number is %s\n", buf);

    number = 0;
    j = 0;
  }
  return 0;
}
