#include <stdio.h>
#define TABSTOP_SIZE 8
#define MAXLEN 1000

/* Write a program 'detab', that replaces a tabulations with a needed number
   of spaces */

int get_line(char buf[]) {
  int c, i;
  i = 0;
  printf("Type something:\n");
  while (i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n')
    buf[i++] = c;

  if (c == '\n') buf[i++] = c;
  buf[i] = '\0';
  return i;
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

int main(void) {
  char buf[MAXLEN], result[MAXLEN];
  int i, len, pos, res_pos, space_count;
  i = len = pos = res_pos = space_count = 0;

  while ((len = get_line(buf)) > 0) {
    pos = res_pos = 0;
    for (pos = 0; pos < MAXLEN; ++pos) result[pos] = 0;
    while (pos < len) {
      if (buf[pos] == '\t') {
        space_count = get_num_to_next_tab(res_pos);
        for (i = 0; i < space_count; ++i)
          result[res_pos++] = ' ';
      }
      else result[res_pos++] = buf[pos];
      ++pos;
    }
    printf("Result:\n%s\n", result);
  }
  return 0;
}
