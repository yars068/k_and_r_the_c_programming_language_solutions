#include <stdio.h>
#include <limits.h>
#define BUFSIZE 12

/* Lesson 4.12. Write recursive version of itoa() */

int itoa(int number, char buf[]);

int main(void) {
  char buf[BUFSIZE] = { '\0' };
  int i, len;
  int numbers[] = { 20, 1, 380, -10, INT_MIN, INT_MAX, 0 };

  for (i = 0; numbers[i] != 0; ++i) {
    if (len = itoa(numbers[i], buf))
      printf("Number %d transformed to text: \"%.*s\", len is %d\n", numbers[i], len, buf, len);
  }

  return 0;
}

#ifndef _LIMITS_H
#include <limits.h>
#endif
void dtoa(int, char []);
static int i = 0;

/* itoa: transform the number to a text representation, recursive version */
int itoa(int number, char buf[]) {
  enum state { NO = 0, YES };
  extern int i;
  int is_max = NO;
  int sign = NO;
  int len;

  for (i = 0; i < BUFSIZE; i++) buf[i] = '\0'; /* reset */

  i = 0;
  if (number > 0) sign = NO;
  else if (number + 1 == INT_MIN + 1) {
    sign = YES;
    number = -(number += 1);
    is_max = YES;
  }
  else {
    sign = YES;
    number = -number;
  }
  if (sign) buf[i++] = '-';
  
  dtoa(number, buf);
  if (is_max && sign) /* Correct the last digit, when transforming INT_MIN */
    buf[i] = (number % 10) + 1 + '0';

  return i;

}

/* dtoa: transform digit to is character representation */
void dtoa(int number, char buf[]) {
  extern int i;

  if (number > 0) {
    dtoa(number / 10, buf);
    buf[i++] = number % 10 + '0';
  }
}
