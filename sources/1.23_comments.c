#include <stdio.h>
#define BUFSIZE 1000
#define TRUE 1
#define FALSE 0
#define NOTHING -1
#define DBLSLA "//"
#define SLASTR "/*"
#define ASTRSLA "*/"

/* Write a program to remove all comments from a C porogram */

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

int findstr(char what[2], char where[]) {
  int match = FALSE;
  int pos, i, result;
  int prev = 0;

  for (i = 0; i <= 2; ++i) {
    if (prev == 0) pos = 0;
    else {
      pos = prev + 1;
      match = FALSE;
      result = prev;
    }
    while (match == FALSE && where[pos] != '\0') {
      if (where[pos] == what[i]) {
        prev = pos;
        match = TRUE;
      }
      ++pos;
    }
  }
  if (match == TRUE) return result;
  return NOTHING;
}

void copy(char from[], char to[], int len) {
  int i = 0;

  while (i < len && (to[i] = from[i]) != '\0') ++i;
  if (to[i] != '\0') to[i] = '\0';
}

int main(void) {
  char buf[BUFSIZE] = {'\0'};
  char res[BUFSIZE] = {'\0'};
  int res_len, res_pos, flag, pos, end, len;
  res_len = res_pos = end = 0;

  while ((len = get_line(buf, BUFSIZE)) > 0) {
    for (pos = 0; pos < len; ++pos) res[pos] = 0;
    if ((end = findstr(DBLSLA, buf)) == NOTHING) copy(buf, res, len);
    else if ((end = findstr(SLASTR, buf)) != NOTHING) {
      copy(buf, res, end);
      flag = TRUE;
    }
    else if ((end = findstr(ASTRSLA, buf)) != NOTHING && flag == TRUE)
      flag = FALSE;
    else if ((end = findstr(ASTRSLA, buf)) == NOTHING && flag == TRUE)
      flag = TRUE;
    else if (flag == TRUE && 
  }
  printf("Result: %s\n", res);
  return 0;
}
