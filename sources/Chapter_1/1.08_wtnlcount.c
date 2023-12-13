#include <stdio.h>

/* Write a program that will count the 
   spacebars, tabulations and new-lines */

int main() {
  int c, ns, nt, nl;
  c = ns = nt = nl = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ') ++ns;
    if (c =='\t') ++nt;
    if (c =='\n') ++nl;
  }
  printf("Spaces: %d, tabs: %d, newlines: %d\n", ns, nt, nl);
}

