#include <stdio.h>

/* Lesson 5.2. Write getfloat(), the floating-point analog of getint(). */
/* What type does getfloat return as its function value? */
/* Answer: Returning type is integer used to indicate the status of the function: */
/* positive return means getfloat() received a number, negative indicates end of input, */
/* and null value indicates that getfloat() received a non-numeric input */

int getfloat(double *);

int main(void) {
  int state;
  double *dblptr;
  double val;
  dblptr = &val;

  while (state != EOF) {
    printf("Enter a number: ");
    if ((state = getfloat(dblptr)) != EOF) printf("You entered %g\n", val);
    else printf("This is not a number\n");
  }
  return 0;
}

int getch(void);
void ungetch(int);

#ifndef _CTYPE_H
#include <ctype.h>
#endif
#define NOT_NUMBER 0
/* getfloat(): get the floating-point number */
int getfloat(double *pn) {
  enum state { NO, YES };
  int c, sign;
  int dot = NO;
  double fr = 0;
  double base = 10;

  while (isspace(c = getch())); /* skip whitespaces */

  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
    ungetch(c);
    return NOT_NUMBER;
  }

  if (c == '+' || c == '-' || c == '.') c = getch();
  sign = (c == '-') ? -1 : 1;

  if (!isdigit(c) && c != '.') ungetch(c);
 
  for (*pn = 0; isdigit(c); c = getch()) {
    *pn = base * *pn + (c - '0');
  }
  printf("c = %c\n", c);
  if (c == '.') {
    dot = YES;
    fr = 0;
    while (isdigit(c = getch())) {
      printf("fr: c=%c\n", c);
      //if (isdigit(c)) {
        fr = fr + (fr + (c - '0')) / base;
        base *= base;
      //}
      //else dot = NO;
      printf("fr = %g\n", fr);
    }
  }
  *pn += fr;
  *pn *= sign;
  if (c != EOF) ungetch(c);
  return c;
}

/* one-character-sized buffer for getch() and ungetch() */
int buf = EOF;

/* getch(): get a (possibly pushed back) character */
int getch(void) {
  int c;

  if (buf != EOF) {
    c = buf;
    buf = EOF;
  }
  else
    c = getchar();
  return c;
}

/* ungetch(): push character back on input */
void ungetch(int c) {
  buf = c;
}
