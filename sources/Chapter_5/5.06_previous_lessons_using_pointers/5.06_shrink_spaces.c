#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

/* Lesson 5.06. Rewrite lesson 1.18 using pointers */
/* Lesson 1.18 Write the program that will replace the sequences of spaces and tabstops
   with a single space and remove the empty lines */

int get_line(char *, int);
void shift(char *, char *);

int main(void) {
  enum state {YES = 0, NO};
  int len = NO;
  char buf[BUFSIZE];
  char *bp = buf;

  while (len) {
    printf("Enter a string: ");
    if (len = get_line(buf, BUFSIZE)) {
      while (*bp) {
        while (!isblank(*bp)) bp++; /* find first blank (a space or a tab) character */
        if (isblank(*bp)) {
          if (*bp == '\t') *bp = ' '; /* replace a tab with space */
          char *tmp = bp++;
          while (isblank(*tmp)) tmp++;
          if (len -= (tmp - bp)) {
            shift(bp, tmp);
            bp -= (tmp - bp);
          }
        }
        bp++;
      }
    }
    printf("Result: \"%.*s\"\n", len - 1, buf);
    while (bp != buf) *bp-- = '\0'; /* clear buffer */
  }
  return 0;
}

/* shift: shift the buffer contents by end - start positions */
void shift(char *start, char *end) {
  char *begin = start;
  while (*start++ = *end++);
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  *buf = '\0';
  return buf - start;
}
