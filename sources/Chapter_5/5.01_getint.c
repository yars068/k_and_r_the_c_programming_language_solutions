#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 25

/* Lesson 5.1. As written, getint() treats a '+' or '-' not followed by a digit as a valid representaion */
/* of zero. Fix it to push such a character back on the input. */

int getint(int *pn);

int main(void) {
  int state;
  int *bufptr;
  int buf;
  bufptr = &buf;

  while ((state = getint(bufptr)) != EOF) {
    if (state) printf("Your input is \"%d\"\n", buf);
    else printf("This is not a number\n");
}
  return 0;
}

int getch(void);
void ungetch(int);

#define NOT_NUMBER 0
/* getint(): get next integer from input into *pn */
int getint(int *pn) {
  int c, sign;

  while (isspace(c = getch())); /* skip whitespaces */

  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return NOT_NUMBER;
  }

  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') c = getch();
  if (!isdigit(c)) ungetch(c);
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');

  *pn *= sign;
  if (c != EOF) ungetch(c);
  return c;
}

#ifndef BUFSIZE
#define BUFSIZE 100
#endif
char buf[BUFSIZE]; /* buffer for getch() and ungetch() */
int bufp = 0; /* next free position in the buffer */

/* getch(): get a (possibly pushed back) character */
int getch(void) {
  int c;
  return (buf[bufp] > 0) ? buf[--bufp] : getchar();
}

/* ungetch(): push character back on input */
void ungetch(int с) {

  if (bufp >= BUFSIZE)
    printf ("ungetch: too many characters\n");
  else
    buf[bufp++] = с;
}
