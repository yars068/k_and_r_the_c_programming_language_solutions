#include <stdio.h>
#include <string.h>
#define BUFSIZE 100

/* Lesson 5.6. Rewrite lesson 4.12 using pointers */
/* Lesson 4.12. Write a program that will print the string in */
/* in reversed direction. Use recursion. */

void reverse(char *);
int get_line(char *, int);

int main(void) {
  char buf[BUFSIZE];
  int len;

  while (len = get_line(buf, BUFSIZE)) {
    printf("Your input: \"%.*s\", len = %d\n", strcspn(buf, "\n"), buf, len);
    reverse(buf);
    printf("Reversed input: \"%.*s\"\n", strcspn(buf, "\n"), buf);
  }
  return 0;
}

/* reverse: revert the string s, recursive version */
void reverse(char *buf) {
  static int i = 0;
  static int j = 0;

  if (*(buf + i) != '\n' && *buf) {
    char tmp = *(buf + i++);
    reverse(buf);
    *(buf + j++) = tmp;
  }
}

/* get_line: store the input stream to array buf */
int get_line(char buf[], int lim) {
  int c = '\0';
  int i = 0;
  
  while (lim-- && ((c = getchar()) != EOF) && c != '\n')
    buf[i++] = c;

  if (c == '\n') buf[i++] = '\n';

  buf[i] = '\0';
  return i;
}

