#ifndef _STDIO_H
#  include <stdio.h>
#endif

/* power: raises a number to a power */
long power(const unsigned base, int n) {
  long p = 1;

  while (n > 0) {
    p *= base;
    --n;
  }
  return p;
}

#ifndef BUFSIZE
#  define BUFSIZE 1024
#endif

/* reverse: revert the string s */
void reverse(char s[], int length) {
  char buf[BUFSIZE];
  int i, j;
  i = 0;
  j = length;

  while (j >= 0) {
    if (s[j] != '\n' && s[j] != '\0') buf[i++] = s[j];
    --j;
  }

  for (i = 0; s[i] != '\0'; ++i) s[i] = buf[i];
}

#ifndef _STDLIB_H
#define _CUSTOM_ATOI_H 1
/* atoi: transform a character representation of integer number to number itself */
int atoi(char buf[], int len) {
  int mul = 1;
  int i, res = 0;

  for (i = len; i >= 0; --i) {
    if (buf[i] >= '0' && buf[i] <= '9') {
      res += (buf[i] - '0') * mul;
      mul *= 10;
    }
  }
  return res;
}
#endif

#ifdef _HAVE_ASK_LINE_H
int get_line(char [], int);
/* ask_line: ask the user to input text data */
int ask_line(char buf[], int lim, char msg[]) {
  printf("%s", msg);
  return get_line(buf, lim);
}
#endif

/* get_line: store the input stream to array buf */
#ifndef _HAVE_ASK_LINE_H
int get_line(char buf[], int lim, char msg[]) {
#endif
#ifdef _HAVE_ASK_LINE_H
int get_line(char buf[], int lim) {
#endif
  int i = 0;
  char c = '\0';
#ifndef _HAVE_ASK_LINE_H
  printf("%s ", msg);
#endif
  while (i < lim - 1 && ((c = getchar()) != EOF) && c != '\n')
    buf[i++] = c;

  if (c == '\n') buf[i++] = '\n';

  buf[i] = '\0';
  return i;
}

#ifndef _CTYPE_H
#  include <ctype.h>
#endif

/* htol: transform hexadecimal number in the character form to a number with type lond int */
long int htol(unsigned char buf[]) {
  const int base = 16; /* = 2^4 */
  long int ret = 0;
  long int i;
  unsigned short c;
  int len = 0;
  int mul = 1; /* 16^0 = 1 */

  while (!isspace(buf[len++])); /* count the length */
  for (i = len; i >= 0; --i) {
    c = tolower(buf[i]);
    printf("c= %c (%d)\n", c, c);
    if (isxdigit(c)) {

      if (isdigit(c))
        ret += (c - '0') * mul;

      else if (isxdigit(c))
        ret += ((c - 'a') + 10) * mul;

      mul *= base;
    }
    else if (i >= 0) continue;
    else return EOF;
  }
  return ret;
}

/* str_cmp: compare two strings */
int str_cmp(unsigned char w1[], unsigned char w2[]) {
  enum boolean { FALSE, TRUE };
  int i = 0;

  while (w1[i] && (w1[i] == w2[i])) i++;
  if (w1[i] == w2[i]) return TRUE;

  return FALSE;
}

/* fact: calculate factorial */
int fact(int n) {
  int ret = 1;

    if (n == 0) ret = 1;
    else ret = n * (fact(n - 1));

  return ret;
}

/* get_power: determine most closer power of number */
int get_power(const unsigned base, long number) {
  int n = 32;
  long p = 0;

  for (n = 32; n > 0 && (p = power(base, n)) > number; --n);

  return n;
}

/* dtob: transform a decimal integer to binary character form */
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
