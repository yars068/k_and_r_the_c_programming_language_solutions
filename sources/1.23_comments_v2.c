#include <stdio.h>
#define BUFSIZE 1000
#define NOTHING -1
#define OPEN 1
#define CLOSED 0

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

int findstr(char what, char buf[], int len, int start) {
  int i = start;
  while (i < len && buf[i] != what) ++i;
  if (i = len) return NOTHING;
  else return i;
}

int main(void) {
  char buf[BUFSIZE], res[BUFSIZE];
  int len, next, pos, prev, status;
  for (pos = 0; pos <= BUFSIZE; ++pos) buf[pos] = res[pos] = '\0';
  len = status = 0;
  next = prev = NOTHING;

  while ((len = get_line(buf, BUFSIZE)) > 0) {
    if (prev != NOTHING) {
      if (qoute == OPEN && comment == OPEN) {
        comment = CLOSED;
        next = findstr("\"", buf, len, prev);
      }
    }
    else prev
  }
}
