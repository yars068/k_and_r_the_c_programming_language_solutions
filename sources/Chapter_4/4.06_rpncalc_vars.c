#include <stdio.h>
#include <math.h>   /* fmod(), pow(), sin(), exp() here. When compiling, you  */
                    /* need to specifiy the linker -lm flag on the commandline */
#include <stdlib.h> /* atof() defined in this header file */
#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define VARSET '1'  /* Have the name of variable */

/* Lesson 4.5. Add support for library functions like sin(), exp(), and pow() */
/* See math.h */

int getop (char []);
void push (double);
double pop (void);
void reset(char []);
double list(void);

double getvar(void);
void setvar(char, double);
void unsetvars(void);
void listvars(void);

/* reverse Polish calculator */
int main (void) {
  int type;
  double op1, op2;
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
      case '/':
        op2 = pop();
        if (op2 != 0.0)
          push (pop() / op2);
        else
          printf("Error: division by zero\n");
        break;
      case '%':
        op2 = pop();
        if (op2 != 0.0)
          push(fmod(pop(), op2)); /* switched to fmod() instead of using a '%' itself */
        else
          printf("Error: division by zero\n");
        break;
      case 'm': /* simplest way to add support for negative numbers */
        push(-pop());     /* is using another symbol for unary '-' operation */
        break;
      case 'l': /* print the top of stack */
        list();
        break;
      case 'd': /* duplicate */
        op2 = pop();
        push(op2);
        push(op2);
        break;
      case 'i': /* swap (interchange) operands */
        op2 = pop();
        op1 = pop();
        push(op2);
        push(op1);
        break;
      case 'c': /* clear stack */
        printf("stack cleared\n");
        reset(s);
        break;
      case '^': /* pow() */
        op2 = pop();
        push(pow(pop(), op2));
        break;
      case 'e': /* exp() */
        push(exp(pop()));
        break;
      case '~': /* sin() */
        push(sin(pop()));
        break;
      case 'g':
        op2 = getvar();
        printf("last variable contain %g\n", op2);        
        push(op2);
        break;
      case VARSET:
        printf("debug: s contain \"%s\"\n", s);
        setvar(s[0], pop());
        break;
      case 'u':
        unsetvars();
        break;
      case 'v':
        listvars();
        break;
      case 'x': /* exit */
        return EXIT_SUCCESS;
        break;
      case '\n':
        printf("\t=%.8g\n", (op2 = pop()));
        push(op2); /* preserve stack to be not empty */
        break;
      default:
        printf("Error: unknown operation: \"%s\"\n", s);
        break;
    }
  }
  return 0;
}

#define MAXNAM 26    /* max count of variable names */
#include <ctype.h>
double vars[MAXNAM];
int var_id = 0;      /* index, evaluated as 'N' - 'A' */

double getvar(void) {
  if (var_id != 0) {
    var_id--;
    return vars['A' + var_id];
  }
  else if (vars['A' + var_id] == 0.0)
    printf("getvar: variable \'%c\' not defined\n", 'A' + var_id);
}

void setvar(char name, double n) {
  if (var_id < MAXNAM) {
    printf("setvar: defined variable \'%c\' with value %g\n", name, n);
    vars['A' + var_id++] = n;
  }
  else
    printf("setvar: cannot set variable \'%c\': no free names left\n", name);
}

void unsetvars(void) {
  while (var_id >= 0)
    vars['A' + var_id--] = 0.0;

  printf("unsetvar: variables destroyed\n");
  var_id = 0;
}

void listvars(void) {
  printf("Defined variables are:\n");
  for (int i = 0; i < var_id; ++i)
    if (vars['A' + i] != 0.0)
      printf("Name: \'%c\', value is: %g\n", ('A' + i), vars['A' + i]);
}

#define MAXVAL 100 /* maximum of stack depth */
int sp = 0; /* stack pointer: next free position */
double val[MAXVAL]; /* this is stack */

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
    //printf( "pop: error: stack is empty\n");
    return 0.0;
  }
}

double list(void) {
  if (sp > 0) {
    printf("stack contains %d elements\n", sp);
    return val[sp];
  }
  else {
    printf("list: error: stack is empty\n");
    return 0.0;
  }
}

#include <ctype.h>
int getch(void);
void ungetch(int);

/* getop: get the next operator or operand */
int getop(char s[]) {
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t' );

  s[1] = '\0';
  if (isupper(c)) return VARSET;
  if (!isdigit(c) && c != '.')
    return c; /* not a number */

  i = 0;
  if (isdigit(c)) /* accumulate the integer part */
  while (isdigit(s[++i] = c = getch()));

  if (c == '.') /* accumulate the fractional part */
    while (isdigit(s[++i] = c = getch()));

  s[i] = '\0';
  if (c != EOF)
    ungetch(c);

  return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in the buffer */

int getch(void) { /* get a (possibly pushed back) character */

  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int с) { /* push character back on input */

  if (bufp >= BUFSIZE)
    printf ("ungetch: too many characters\n");
  else
    buf[bufp++] = с;
}

void reset(char s[]) { /* clear all, s[] is local array, so it is a parameter for this function */
  int i = 0;
  while (sp >= 0) val[sp--] = 0.0;
  while (bufp >= 0) buf[bufp--] = '\0';
  while (i <= MAXOP) s[i++] = '\0';
  sp = 0;
  bufp = 0;
}
