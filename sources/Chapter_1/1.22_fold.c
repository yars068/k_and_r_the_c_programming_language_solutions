#include <stdio.h>
#define BUFSIZE 1000
#define MAXLEN 20

/* Write a program to "fold" the lines longer than n symbols into two or
more shorter lines */

int get_line(char s[], int lim) {
  int c, len;
  c = len = 0;
  printf("Type something:\n");
  while (len < lim - 1 && (c = getchar()) != EOF && c != '\n')
    s[len++] = c;

  if (c == '\n') s[len++] = c;
  s[len] = '\0';
  return len;
}

int main(void) {
  char buf[BUFSIZE];
  int len, pos;
  len = pos = 0;
  for (pos = 0; pos < BUFSIZE; ++pos) buf[pos] = 0;

  while ((len = get_line(buf, BUFSIZE)) > 0) {
    if (len >= BUFSIZE - 1) {
      printf("\nToo long line\n");
      break;
    }
    if (len > MAXLEN) {
      for (pos = MAXLEN; pos >= 0; --pos) {
        if (buf[pos] == ' ' || buf[pos] == '\t') break;
        else if (pos == 0) {
          printf("\nCan\'t fold this line\n");
          break;
        }
      }
      if (buf[pos - 1] != ' ' || buf[pos - 1] != '\t') buf[pos] = '\n';
    }
    printf("Result:\n%s\n", buf);
  }
}
