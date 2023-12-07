#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

void reverse(char s[], int length) {
  char buf[length];
  int i, j;
  i = 0;
  j = length - 2; // because string is in 'hello\n\0' format
  while (i <= length - 2 && j >= 0) {
    buf[i] = s[j];
    ++i;
    --j;
  }
  buf[length - 1] = '\n';
  buf[length] = '\0';
  for (i = 0; i < length; ++i) s[i] = buf[i];
}

int chartodig(char buf[], int len) {
  int mul = 1;
  int i, res = 0;

  for (i = (len - 2); i >= 0; i--) { // because buf[len] = '\n'
    res += (buf[i] - '0') * mul;
    mul *= 10;
  }
  return res;
}

int get_line(unsigned char buf[], unsigned int lim, const char msg[]) {
  unsigned int i = 0;
  unsigned short int c = '\0';

  printf("%s ", msg);
  while ((i < lim - 1) && ((c = getchar()) != EOF) && (c != '\n'))
    buf[i++] = c;

  if (c == '\n') buf[i++] = '\n';

  buf[i] = '\0';
  return i;
}

long int htol(unsigned char buf[]) {
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

      mul *= 16;
    }
    else if (i >= 0) continue;
    else return EOF;
  }
  return ret;
}
