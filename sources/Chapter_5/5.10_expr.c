#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXARGS 10
#define NO_ARGS 1

/* Lesson 5.10. Write the program expr, which evaluates a expression in the */
/* reverse polish notation, where every operator or operand is a separate command line argument */

/* NOTE: The shell will perform a pathname expansion, so we need to shield, */
/* in particular, the asterisk. This done by adding a '\' before it. */
/* Alternatively, just place these special-meaning characters to a quotes */

void push(double number);
double pop(void);
void eval(char op);

int main(int argc, char *argv[]) {

  if (argc == NO_ARGS) { /* If argc == 1 then no arguments left */
    printf("Error: no arguments specified. At least three arguments required.\n");
    return EXIT_FAILURE;
  }

  if (argc >= MAXARGS) {
    printf("Error: too many arguments. Do not exceed 10.\n");
    return EXIT_FAILURE;
  }

  ++argv; /* skip argv[0], because it is a program name */
  argc--;

  while (*argv) {
    if (isdigit(**argv))
      push(atof(*argv));
    else eval(**argv);

    argc--;
    *++argv;
  }

  printf("Result: %.2f\n", pop());
  return EXIT_SUCCESS;
}

void eval(char op) {
  double tmp = 0;

  switch (op) {
    case '+':
      push(pop() + pop());
      break;
    case '-':
      tmp = pop();
      push(tmp - pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '/':
      if (tmp = pop())
        push(pop() / tmp);
      else {
        printf("Error: division by zero\n");
        exit(EXIT_FAILURE);
      }
      break;
    case '%':
      if (tmp = pop())
        push((int)pop() % (int)tmp);
      else {
        printf("Error: unable to get remainder: division by zero\n");
      }
      break;
    default:
      printf("Error: unknown operation\n");
      exit(EXIT_FAILURE);
      break;
  }
}

static double stack[MAXARGS] = { 0 };
static int sp = 0;

void push(double number) {
  if (sp < MAXARGS)
    stack[sp++] = number;
  else {
    printf("push: error: stack is full\n");
    exit(EXIT_FAILURE);
  }
}

double pop(void) {
  if (sp)
    return stack[--sp];
  else {
    printf("pop: error: stack is emty\n");
    exit(EXIT_FAILURE);
  }
}
