#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define BUFSIZE 1024U
#define NOTHING -1

/* Lesson 4.1. Write function strindex(s, t) which finds the */
/* first trailing match of string t in string s */

int strindex(char s[], char t[]);
int strindex_trailing(char s[], char t[]);
int get_line(char buf[], int lim, const char msg[]);

int main(void) {
  const char msg1[] = "Enter string where you want to find: ";
  const char msg2[] = "Enter what you want to find: ";
  char where[BUFSIZE] = { '\0' };
  char what[BUFSIZE] = { '\0' };
  int len_where = 0;
  int len_what = 0;
  int res = NOTHING;

  if (len_where = get_line(where, BUFSIZE, msg1));
  else return EXIT_FAILURE;
  if (len_what = get_line(what, BUFSIZE, msg2));
  else return EXIT_FAILURE;
  if ((res = strindex_trailing(where, what)) > 0) /* length consider a '\n', so reduce it by 1 to suppress */
    printf("Position of \"%.*s\" in \"%.*s\" is %d\n", (len_what - 1), what, (len_where - 1), where, res);
  else {
    printf("No match found\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/* strindex: find the position in s where t occurs */
int strindex(char s[], char t[]) {
  int i, j, k;
  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++);

   if (k > 0 && t[k] == '\0') return i;
  }
  return -1;
}

/* strindex_trailing: find the position in s where t occurs, starting from ending of s */
int strindex_trailing(char s[], char t[]) {
  int idx_s = 0;
  int idx_t = 0;
  int j;

  while (s[idx_s] != '\0') idx_s++; /* count the lengths */
  while (t[idx_t] != '\0') idx_t++;

  printf("Lengths: s is %d, t is %d\n", idx_s, idx_t);

  while (idx_s >= 0) {
    if (s[idx_s] >= 0)
      for (j = idx_s; idx_t >= 0 && s[j] == t[idx_t]; j--, idx_t--);
    idx_s--;

    if (idx_t == 0 && t[idx_t] != '\0') return idx_s;
  }
  return NOTHING;
}

/* get_line: store the input stream to array buf */
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
