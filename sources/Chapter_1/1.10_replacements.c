#include <stdio.h>

/* Write the program that will copy the typed symbols to the output 
   stream replacing the tabstops to \t, the backspaces to \b and
   every backslashes to \\. It will makes all these symbols visible */

int main() {
  int c;
  while ((c = getchar()) != EOF) {
    if (c == '\t' || c == '\b' || c == '\\') {
      putchar('\\');
      if (c == '\t') putchar('t');
      if (c == '\b') putchar('b');
      if (c == '\\') putchar('\\');
    }
    else putchar(c);
  }
}
