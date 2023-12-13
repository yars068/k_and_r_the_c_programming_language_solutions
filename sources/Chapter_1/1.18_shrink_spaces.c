#include <stdio.h>
#define MAXLEN 1000

/* Write the program that will replace the sequences of spaces and tabstops
   with a single space and remove the empty lines */

int get_line(char line[], int lim) {
  int c, i;
  printf("Type something:\n");
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c !='\n'; ++i)
    line[i] = c;
  if (c == '\n') {
    line[i] = c;
    ++i;
  }
  line[i] = '\0';
  return i;
}

int more_than_one(char line[], int len, int start) {
  int i, count;
  count = 0;
  i = start;

  while ((line[i] == ' ' || line[i] == '\t') && i < len) {
    ++count;
    ++i;
  }
  if (count >= 1) return count;
  else return 0;
}

int replace(char buf[], int len, int start, int count) {
  char result[MAXLEN];
  int i, j;
  i = j = 0;

  for (i = 0; i < len; ++i) {
    if (i < start || i >= (start + count)) {
      result[j] = buf[i];
      ++j;
    }
    if (i == start) {
      result[j] = ' ';
      ++j;
    }
  }
  for (i = 0; i < j; ++i) buf[i] = result[i];
  buf[i] = '\n';
  ++i;
  buf[i] = '\0';
  /* return the new line length */
  return i;
}

int main() {
  int i, len, count;
  char buf[MAXLEN];
  i = len = count = 0;

  for (i=0; i < MAXLEN; ++i) buf[i] = 0;
  /* Empty line is 1 in length, so, just drop it */
  while ((len = get_line(buf, MAXLEN)) > 1) {
    for (i = 0; i < len; ++i) {
      if (buf[i] == ' ' || buf[i] == '\t') {
        if ((count = more_than_one(buf, len, i)) > 1)
          len = replace(buf, len, i, count);
      }
    }
    if (len > 1) printf("%s", buf);
  }
  return 0;
}
