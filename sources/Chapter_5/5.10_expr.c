#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXARGS 10

/* Lesson 5.10. Write the program expr, which evaluates a reverse polish expression, where */
/* every operator or operand is a separate command line argument */

int main(int argc, char *argv[]) {
  const int next = 1;
  int idx = 0;
  int vars[MAXARGS];

  while (--argc > 0) {
    if (isdigit(**argv) && idx < MAXARGS) *(vars + idx++) = atoi((*argv));
    else if (idx > MAXARGS) {
      printf("Too many arguments\n");
      return EXIT_FAILURE;
    }
    *++argv;
  }
  if (**argv == '+') *vars += *(vars + next);
  else if (**argv == '-') *vars -= *(vars + next);
  else if (**argv == '*') *vars *= *(vars + next);
  else if (**argv == '/') *vars /= *(vars + next);
  else if (**argv == '%') *vars %= *(vars + next);
  else {
    printf("Unknown operator\n");
    return EXIT_FAILURE;
  }
  printf("Result: %d\n", *vars);
  return EXIT_SUCCESS;
}
