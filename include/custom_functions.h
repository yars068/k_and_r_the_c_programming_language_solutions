#ifndef _CTYPE_H
#include <ctype.h>
#endif
#ifndef _STDIO_H
#include <stdio.h>
#endif

unsigned power(const unsigned base, unsigned n) {
  unsigned p = 1;

  while (n > 0) {
    p *= base;
    --n;
  }
  return p;
}

void reverse(char s[], int length) {
  char buf[length];
  int i, j;
  i = 0;
  j = length;
  while (s[i] != '\0' && j >= 0) {
    if (s[i] != '\n') buf[i] = s[j];
    ++i;
    --j;
  }

  for (i = 0; s[i] != '\0'; ++i) s[i] = buf[i];
}

int chartodig(char buf[], int len) {
  int mul = 1;
  int i, res = 0;
  int ret = -1;
  
  for (i = len; i >= 0; --i) {
    if (buf[i] >= '0' && buf[i] <= '9') {
      res += (buf[i] - '0') * mul;
      mul *= 10;
      ret = 0;
    }
  }
  if (ret == -1) return ret;
  else return res;
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
