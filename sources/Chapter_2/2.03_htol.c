#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define BUFSIZE 1024U

/* Lesson 2.3. Write function htol() which fransform a hexadecimal */
/* numbers to an integer */

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

long int htol(unsigned char buf[]) {
  long int ret = 0;
  long int i;
  unsigned short c;
  int len = 0;
  int mul = 1; /* 16^0 = 1 */

  while (!isspace(buf[len++])); /* count the length */
  for (i = len; i >= 0; --i) {
    c = tolower(buf[i]);
    if (isxdigit(c)) {
      if (isdigit(c))
        ret += (c - '0') * mul;
      else if (isxdigit(c))
        ret += ((c - 'a') + 10) * mul;
      mul *= 16;
    }
    else if (i >= 0) continue;
    else return EOF;
  }
  return ret;
}


int main(void) {
  unsigned char buf[BUFSIZE] = { '\0' };
  int len;
  long int res = 0;
  const unsigned char message[] = "Input hexadecimal number: ";

  while ((len = get_line(buf, BUFSIZE, message)) != EOF) {
    if ((res = htol(buf)) != EOF)
      printf("decimal number is %d\n", res);
    else printf("Illegal input. Try again.\n");
  }
  return EXIT_SUCCESS;
}
