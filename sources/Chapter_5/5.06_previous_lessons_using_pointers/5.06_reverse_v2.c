#include <stdio.h>
#define BUFSIZE 100

/* Lesson 5.6. Rewrite lesson 1.19 using pointers, version 2 */
/* Lesson 1.19. Write a function reverse(s), that does a reversion the string */

void reverse(char *);
int get_line(char *, int);

int main(void) {
  enum state { YES = 0, NO };
  int end = NO;
  char buf[BUFSIZE];
  int len;

  while (end) {
    printf("Enter string to reverse: ");
    if (len = get_line(buf, BUFSIZE)) {
      reverse(buf);
      printf("Reversed: \"%.*s\"\n", len - 1, buf);
    }
    else end = YES;
  }
  return 0;
}

/* reverse: return the string in reverse direction, version that uses pointers */
void reverse(char *buf) {
  char *fub = buf;
  char tmp;

  while (*buf != '\n') buf++; /* go to end of string */

  while ((buf - fub) > 0 && buf--) {
    tmp = *buf;
    *buf = *fub;
    *fub++ = tmp;
  }
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  *buf = '\0';
  return buf - start;
}
