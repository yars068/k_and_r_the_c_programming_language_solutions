#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define BUFSIZE 25

/* Lesson 3.5. Write a function itob(n, s, b) that transform a number n */
/* into a string s that represents a number by the base b */

void reverse(char s[], int length) {
  char buf[BUFSIZE];
  int i, j;
  i = 0;
  j = length;

  while (j >= 0) {
    if (s[j] != '\n'&& s[j] != '\0') buf[i++] = s[j];
    --j;
  }

  for (i = 0; s[i] != '\0'; ++i) s[i] = buf[i];
}

int chartodig(char buf[], int res[], int len) {
  enum status { FAIL = 0, SUCCESS };
  const int base = 10;
  int i, mul = 1; /* base^0 = 1 */
  int state = FAIL;

  res[0] = 0; /* a little hack */
  for (i = len; i >= 0; --i)
    if (isdigit(buf[i])) {
      res[0] += (buf[i] - '0') * mul;
      mul *= base;
      state = SUCCESS;
    }
    else state = FAIL;

  return state;
}

int get_line(char buf[], int lim, const char msg[]) {
  int i = 0;
  char c = '\0';

  printf("%s ", msg);
  while (i < lim - 1 && ((c = getchar()) != EOF) && c != '\n')
    buf[i++] = c;

  if (c == '\n') buf[i++] = '\n';

  buf[i] = '\0';
  return i;
}

int itob(int n, char result[], int base) {
  int len = 0;
  int remainder;

  for (len = 0; len <= BUFSIZE; len++) result[len] = '\0'; /*reset buffer */

  for (len = 0; n > 0; n /= base, len++) {
    remainder = n % base;
    if (remainder >= base) result[len] = remainder + 'a' - 10;
    else result[len] = remainder + '0';
  }
  reverse(result, len);
  return len;
}

int main(void) {
  const char msg[] = "Enter a decimal number: ";
  int base = 10;
  char buf[BUFSIZE] = { '\0' };
  int number[1]; /* a little hack */
  int len = 0;
  int ret = EXIT_SUCCESS;

  if (len = get_line(buf, BUFSIZE, msg)) {
    if (chartodig(buf, number, len)) {
      if (itob(number[0], buf, base)) printf("Result: \'%s\'\n", buf);
    }
    else {
      printf("Wrong input!\n");
      ret = EXIT_FAILURE;
    }
  }
  return ret;
}
