#include <stdio.h>
#define BUFSIZE 100

/* Lesson 5.6. Rewrite lesson 1.19 using pointers, version 1 */
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
  char *pos = buf;
  char res[BUFSIZE];
  int i = 0;

  while (*buf != '\n') buf++; /* go to end of string */

  while (buf - pos && buf--) res[i++] = *buf;

  i = 0;
  while (*buf != '\n') *buf++ = res[i++];
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  int len = 0;

  while (lim-- && (buf[len] = getchar()) != EOF && buf[len++] != '\n');
  /* it is possible to use the index, instead of pointer. Here is useful. */
  buf[len] = '\0';
  return len;
}
