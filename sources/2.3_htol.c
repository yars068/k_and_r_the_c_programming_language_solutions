#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "../include/custom_functions.h"

#define BUFSIZE 1024U

/* Lesson 2.3. Write function htol() which fransform a hexadecimal */
/* numbers to an integer */

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
