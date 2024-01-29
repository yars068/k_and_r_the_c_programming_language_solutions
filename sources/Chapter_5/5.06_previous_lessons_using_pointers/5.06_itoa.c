#include <stdio.h>
#define BUFSIZE 26

/* Lesson 5.6. Rewrite the lesson 3.4 using pointers */
/* Lesson 3.4. Explain why this function cannot handle the greatest negative */
/* number? The answer: when comparing n < 0 to determine the sign, becomes a type owerflow. */

void itoa_original(int, char[]);
void reverse(char *);
char *itoa(int *, char *);
int getint(int *);
void reset(char *);

int main(void) {
  char buf[BUFSIZE];
  enum logic { NO, YES };
  int state = YES;
  int n = 0;
  int *pn = &n;

  while (state != EOF) {
    *pn = 0;
    reset(buf);
    printf("Enter a number: ");
    if (((state = getint(pn)) != EOF) && state) {
      printf("Your number in text form: \"%s\"\n", itoa(pn, buf));
    }
    else if (state == NO) printf("This is not a number\n");
  }
  putchar('\n');
  return NO; /* In UNIX, returned 0 means that no errors occured */
}

/* original version of itoa: transform a number to its character representation */
void itoa_original (int n, char s[]) {
  int i, sign;

  if ((sign = n) < 0)
    n = -n;

  i = 0;
  do
   s[i++] = n % 10 + '0';
  while ((n /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';

  s[i] = '\0';
  reverse(s);
}

/* reverse: return the string in reverse direction, version that uses pointers */
void reverse(char *buf) {
  char *fub = buf;
  char tmp;

  while (*buf != '\n') buf++; /* go to end of string */

  while ((buf - fub) > 0 && buf--) {
    tmp = *buf;
    *buf = *fub;
    *fub++ = tmp;
  }
}

#ifndef _LIBC_LIMITS_H_
#  include <limits.h>
#endif

static int i = 0;
/* itoa: transform an integer to character form */
char *itoa (int *n, char *s) {
  void itoch(int, char *);
  enum yesno { NO, YES };
  int base = 10;
  int max = NO;

  i = 0;
  if ((*n + 1) == (INT_MIN + 1)) {
    *(s + i++) = '-';
    *n = -(*n + 1);
    max = YES;
  }
  else if (*n < 0) {
    *(s + i++) = '-';
    *n = -(*n);
  }

  itoch(*n, s);
  if (max) {
    *(s + (i - 1)) = (*n % base + '0') + 1; /* correct the last digit when n == INT_MIN */
  }

  *(s + i) = '\0';
  return s;
}

void itoch(int num, char *s) {
  int base = 10;
  extern int i;

  if (num) {
    itoch(num / base, s);
    *(s + i++) = (num % base) + '0';
  }
}

#ifndef _CTYPE_H
#  include <ctype.h>
#endif

#define NOT_NUMBER 0
#define NUMBER 1

/* getint: transform character stream to an integer number */
int getint(int *res) {
  enum yesno { NO, YES };
  int base = 10;
  int sign = NO;
  char c;

  *res = 0;
  while (((c = getchar()) != EOF) && c != '\n') {
    if (!isdigit(c) && c != '-' && c != '+') return NOT_NUMBER;
    if (c == '-' && sign) return NOT_NUMBER;
    else if (c == '-' && !sign) sign = YES;
    else if (isdigit(c)) *res = *res * base + c - '0';
  }
  if (sign) *res = -(*res);
  if (c == EOF) return EOF;
  return NUMBER;
}

void reset(char *buf) {
  while (*buf) *buf++ = '\0';
}
