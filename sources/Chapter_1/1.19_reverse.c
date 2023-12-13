#include <stdio.h>
#define MAXLEN 1000

/* Write a function reverse(s), that does a reversion the string */

int get_line(char line[], int  lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;

  if (c == '\n') {
    line[i] = c;
    ++i;
  }
  line[i] = '\0';
  return i;
}

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

int main() {
  char line[MAXLEN];
  int len;
  while ((len = get_line(line, MAXLEN)) > 0) {
    reverse(line, len);
    printf("Reversed: %s", line);
  }
}
