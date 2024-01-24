#include <stdio.h>
#define BUFSIZE 100
#define FIRST 5

int get_line(char *, int);
int strn_cmp(char *, char *, int);
int main(void) {
  char s1[BUFSIZE], s2[BUFSIZE];
  int len, len2, res;

  printf("Enter first string: ");
  if (len = get_line(s1, BUFSIZE)) {
    printf("Enter second string: ");
    if (len2 = get_line(s2, BUFSIZE)) {
      res = strn_cmp(s1, s2, FIRST);
      printf("Comparation result: first %d characters in %s\n", FIRST, (res < 0) ? "first string less than in second" : 
        (res == 0) ? "both strings are equivalent" : "first string greater than in second");
    }
  }
  return 0;
}

/* strn_cmp: compare at most sz characters, returns < 0 when s < t */
/* 0 when s == t, and > 0 when s > t */
int strn_cmp(char *s, char *t, int sz) {

  for ( ; sz && (*s == *t); s++, t++, sz--)
    if (*s == '\0')
      return 0;
  return *s - *t;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  int len = 0;

  while (lim-- && (buf[len] = getchar()) != EOF && buf[len++] != '\n');
  /* it is possible to use the index, instead of pointer. Here is useful. */
  buf[len] = '\0';
  return len;
}
