#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 25

/* Lesson 5.6. Rewrite lesson 2.3 using poiters */
/* Lesson 2.3. Write function htol() which fransform a hexadecimal */
/* numbers to an integer */

int get_line(char *, int);
int htol(char *, long *);

int main(void) {
  enum state { YES = 0, NO };
  char buf[BUFSIZE];
  int len = NO;
  long res;
  long *res_p = &res;

  while (len) {
    printf("Enter hexadecimal number: ");
    if (len = get_line(buf, BUFSIZE)) {
      if (htol(buf, res_p))
        printf("Hexadecimal number %.*s is decimal %ld\n", len -1, buf, res);

      else
        printf("Seems your input is not a hexadecimal number\n");

      while (len) buf[len--] = '\0';
      res = 0;
    }
  }
  return YES;
}

/* htol: convert the hexadecimal character represented number to a decimal long int number */
int htol(char *buf, long *res) {
  enum state { FAIL = 0, SUCCESS };
  char *start = buf;
  long mul = 1; /* 16^0 = 1 */
  const int base = 16;

  while (*buf != '\n') buf++; /* go to the end of line (important, check for newline, not '\0') */
  buf--;
  while ((buf - start) >= 0) {
    char c = tolower(*buf);
    if (c >= 'a' && c <= 'f')
      *res += (0xA + (c - 'a')) * mul;

    else if (c >= '0' && c <= '9')
      *res += (c - '0') * mul;

    else if (c == 'x' || c == 'X') buf--;
    else return FAIL;
    mul *= base;
    buf--;
  }
  return SUCCESS;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  *buf = '\0';
  return buf - start;
}
