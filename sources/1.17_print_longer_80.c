#include <stdio.h>
#define MAXLEN 1000

/* Write the program that will print strings longer than 80 symbols */

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

int main() {
  char buf[MAXLEN];
  int len;
  while ((len = get_line(buf, MAXLEN)) > 0) {
    if (len > 80) printf("This line is longer than 80:\n%s\n", buf);
  }
  return 0;
}
