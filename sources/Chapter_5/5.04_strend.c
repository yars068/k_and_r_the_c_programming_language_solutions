#include <stdio.h>
#define BUFSIZE 1000

/* Lesson 5.4. Write function strend(str, sub) that returns 1 */
/* if sub is present at end of str, and 0, if not. */

int strend(char *, char *);
int get_line(char *, int);

int main(void) {
  char buf[BUFSIZE], sub[BUFSIZE];
  int len_str, len_sub;
  
  printf("Enter the string: ");
  if (len_str = get_line(buf, BUFSIZE)) {
    printf("Enter a substring: ");
    if (len_sub = get_line(sub, BUFSIZE))
      if (strend(buf, sub))
        printf("\"%.*s\" is at end of \"%.*s\"\n", len_sub - 1, sub, len_str - 1, buf);
      else
        printf("No match found\n");
  }
}

int strend(char *str, char *sub) {
  enum state { FALSE = 0, TRUE };
  int status = TRUE;
  char *s, *t;

  s = str;
  t = sub;

  while (*str++);
  while (*sub++);

  while ((sub - t) && (str - s)) {
    if (*sub-- == *str--) status = TRUE;
    else status = FALSE;
  }
  return status;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  int len = 0;

  while (lim-- && (buf[len] = getchar()) != EOF && buf[len++] != '\n');
  /* it is possible to use the index, instead of pointer. Here is useful. */
  buf[len] = '\0';
  return len;
}
