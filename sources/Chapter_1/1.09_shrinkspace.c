#include <stdio.h>

/* Write the program that will copy the input stream into 
   output stream, replacing the spaces repeated multiple
   times to a single one */

int main() {
  int c, ns;
  c = ns = 0;
  while ((c = getchar()) != EOF) {
    if (c != ' ') {
      putchar(c);
      ns = 0;
    }
    if (ns == 0 && c == ' ') {
      ++ns;
      putchar(c);
    }
    if (ns > 1 && c == ' ') ++ns;
  }
}

