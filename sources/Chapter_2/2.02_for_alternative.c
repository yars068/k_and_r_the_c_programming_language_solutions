#include <stdio.h>
#include <limits.h>
#define BUFSIZE 1024U

/* Lesson 2.2. Rewrite function get_line() using alternative conditions */

int get_line(unsigned char buf[], unsigned int lim, const char msg[]) {
  unsigned int i = 0;
  unsigned int c = '\0';

  printf("%s ", msg);
  while ((i < lim - 1) == ((c = getchar()) != EOF) == (c != '\n'))
    buf[i++] = c;

  if (c == '\n') buf[i++] = '\n';

  buf[i] = '\0';
  if (i > 1) return i;
  else return 0;
}

int main(void) {
  unsigned char buf[BUFSIZE] = {'\0'};
  unsigned int len = 0;
  unsigned const char message[] = "Type something:";
  
  while ((len = get_line(buf, BUFSIZE, message)) > 0) {
    printf("Your input is %s\n", buf);
  }
  return 0;
}
