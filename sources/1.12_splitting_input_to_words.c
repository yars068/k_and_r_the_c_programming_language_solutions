#include <stdio.h>

/* Write a program that will split the output stream to a words, every one 
   on the new line */

int main(void) {
  int c;
  while ((c=getchar()) != EOF) {
    /* We will ignore the '\n' delimiter because this does a new line 
    already, so it will avoid the duplicate newlines (blank lines) */
    if (c == ' ' || c == '\t')
      putchar('\n');
    else
      putchar(c);
  }
}
