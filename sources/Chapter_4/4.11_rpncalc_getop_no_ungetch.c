#include <stdio.h>
#include <stdlib.h> /* atof() defined in this header file */
#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

/* Lesson 4.3. Modify this calculator: add the modulus (%) */
/* operator and provisions to negative numbers */

int getop (char []);
void push (double);
double pop (void);

/* reverse Polish calculator */
int main (void) {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop (s)) != EOF) {
    switch (type) {
      case NUMBER:
        push (atof (s));
        break;
      case '+':
        push (pop() + pop());
        break;
      case '*':
        push (pop() * pop());
        break;
      case '-':
        op2 = pop();
        push (pop() - op2);
        break;
      case '/' :
        op2 = pop();
        if (op2 != 0.0)
          push (pop() / op2);
        else
          printf("Error: division by zero\n");
        break;
      case '%':
        op2 = pop();
        if (op2 != 0.0)
          push((int)pop() % (int)op2);
        else
          printf("Error: division by zero\n");
        break;
      case 'm': /* simplest way to add support for negative */
        push(-pop());  /* numbers is using another symbol for unary '-' operation */
        break;
      case '\n' :
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("Error: unknown operation %c\n", type);
        break;
    }
  }
  return 0;
}

#define MAXVAL 100 /* maximum of stack depth */
int sp = 0; /* stack pointer: next free position */
double val[ MAXVAL ]; /* this is stack */

/* push: push the value f into a stack */
void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
   printf( "push: cannot push the \'%g\': stack is full\n", f);
}

/* pop: pop and return the value from the top of stack */
double pop(void) {

  if (sp > 0)
    return val[--sp];
  else {
    printf( "pop: error: stack is empty\n");
    return 0.0;
  }
}

#include <ctype.h>

/* getop: get the next operator or operand */
int getop(char s[]) {
  static int buf = EOF;
  int i, c;

  while ((s[0] = c = (buf != EOF && buf != '\n') ? buf : getchar()) == ' ' || c == '\t' )
    buf = EOF;

  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c; /* not a number */

  i = 0;
  if (isdigit(c)) /* accumulate the integer part */
  while (isdigit(s[++i] = c = getchar()));

  if (c == '.') /* accumulate the fractional part */
    while (isdigit(s[++i] = c = getchar()));

  s[i] = '\0';
  if (c != EOF)
    buf = c;
  else 
    buf = EOF;

  return NUMBER;
}
