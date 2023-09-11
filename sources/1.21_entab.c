#include <stdio.h>
#define MAXLEN 1000
#define TABSTOP_SIZE 8

/* Write a program 'entab', that does a replace sequences of blanks to a
   minimal number of blanks and tab stops, keep the view of printed
   text unchanged */

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

int get_num_to_next_tab(int current_pos) {
  int space_count, tab_number, tab_pos;
  space_count = tab_number = tab_pos = 0;

  while (tab_pos <= current_pos ) {
    tab_pos = tab_number * TABSTOP_SIZE;
    space_count = tab_pos - current_pos;
    ++tab_number;
  }
  return space_count;
}

int get_count(char buf[], int pos, char what) {
  int i = 0;
  while (buf[pos++] == what) ++i;
  return i;
}

int main(void) {
  char buf[MAXLEN], res[MAXLEN];
  int len, pos, res_pos, spaces, num_to_next_tab;
  for (pos = 0; pos < MAXLEN; ++pos) buf[pos] = res[pos] = 0;
  len = pos = res_pos = spaces = num_to_next_tab = 0;

  while ((len = get_line(buf, MAXLEN)) > 0) {
    res_pos = 0;
    for (pos = 0; pos < MAXLEN; ++pos) res[pos] = 0;
    for (pos = 0; pos < len; ++pos) {
      if (buf[pos] == ' ') {
        spaces = get_count(buf, pos, ' ');
        num_to_next_tab = get_num_to_next_tab(pos);
        if (spaces > 1 && (spaces >= num_to_next_tab)) {
          res[res_pos++] = '\t';
          pos = pos + spaces - 1; /* на будущее, += делает то же самое */
        }
        else res[res_pos++] = buf[pos];
      }
      else res[res_pos++] = buf[pos];
    }
    res[res_pos] = '\0';
    printf("Result:\n%s\n", res);
  }
}

