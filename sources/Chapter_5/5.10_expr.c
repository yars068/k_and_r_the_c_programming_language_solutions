#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXARGS 10

/* Lesson 5.10. Write the program expr, which evaluates a expression in the */
/* reverse polish notation, where every operator or operand is a separate command line argument */

/* NOTE: The shell will perform a pathname expansion, so we need to shield, */
/* in particular, the asterisk. This done by adding a '\' before it. */
/* Another way is placing all the parameters on the command line to a double quotes */
/* and then process them as a regular character string. But this leads program to be */
/* slightly complicated ;) */

int main(int argc, char *argv[]) {
  const int next = 1;
  int i = 0;
  int vals[MAXARGS];
  char **start;

  while (--argc > 0) {
    if (isdigit(**argv) && i < MAXARGS) {
      *(vals + i++) = atoi((*argv));
      start = argv;
    }
    else if (i > MAXARGS) {
      printf("Too many arguments\n");
      return EXIT_FAILURE;
    }
    *++argv;
  }
  i = 1;
  while (argv != start) {
    if (**argv == '+') *vals += *(vals + i);
    else if (**argv == '-') *vals -= *(vals + i);
    else if (**argv == '*') *vals *= *(vals + i);
    else if (**argv == '/') *vals /= *(vals + i);
    else if (**argv == '%') *vals %= *(vals + i);
    else {
      printf("Unknown operator\n");
      return EXIT_FAILURE;
    }
    *--argv;
    i++;
  }
  printf("Result: %d\n", *vals);
  return EXIT_SUCCESS;
}
