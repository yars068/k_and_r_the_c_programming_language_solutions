#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#define BUFSIZE 100
#define MAXOP 100

/* Lesson 4.10. Write program that realize the reverse Polish notation calculator */
/* using get_line() */
/* To compile, use -lm option at command-line (math.h requirement) */

int get_line(char [], int);
char oneof(char, char []);
void reset(char []);
void push(double);
double pop(void);
double eval(double, double, char);

int main(void) {
  enum boolean {NO = 0, YES};
  char have_sign = NO;
  char operators[] = "*/%+-";
  char text[BUFSIZE] = {'\0'};
  char buf[BUFSIZE] = {'\0'};
  char op;
  double val = 0.0, val2 = 0.0;
  int i = 0, j = 0;

  while (get_line(buf, BUFSIZE)) {
    for (i = 0; buf[i] != '\n'; i++) {
      if (i && isdigit(buf[i]) && buf[i - 1] == '-')
        have_sign = YES;

      if (isdigit(buf[i]) || buf[i] == '.') {
        for (j = 0; isdigit(buf[i]) || buf[i] == '.'; j++)
          text[j] = (buf[i++]);

        text[j] = '\0'; /* append the terminating byte */
        if (j) {
          val = atof(text);
          if (have_sign) {
            val = -val;
            have_sign = NO;
          }
          push(val);
          reset(text);
          j = 0;
        }
      }
      if (i && buf[i - 1] == ' ' && (buf[i + 1] == ' ' || buf[i + 1] == '\n') 
          && (op = oneof(buf[i], operators))) {
        val2 = pop();
        val = pop();
        push(eval(val, val2, op));
      }
    }

    if (buf[i] == '\n') {
      printf("= %g\n", pop());
      while (i) buf[i--] = '\0';
    }
  }

  return 0;
}

/* get_line: store the input stream to array buf */
int get_line(char buf[], int lim) {
  int c = '\0';
  int i = 0;
  
  while (lim-- && ((c = getchar()) != EOF) && c != '\n')
    buf[i++] = c;

  if (c == '\n') buf[i++] = '\n';

  buf[i] = '\0';
  return i;
}

/* oneof: return non-zero when ch is in ops */
char oneof(char ch, char ops[]) {
  int i;
  for (i = 0; ops[i] != '\0' && ops[i] != ch; i++);
  if (ops[i] == ch) return ch;
  else return 0;
}

/* reset: fill the specified array with '\0' */
void reset(char buf[]) {
  int i;
  for (i = 0; buf[i] != '\0' && i < BUFSIZE; ++i) buf[i] = '\0';
}

/* stack and its pointer */
double val[MAXOP];
int sp = 0;

/* push: push the value in the stack */
void push(double v) {
  if (sp < MAXOP) val[sp++] = v;
}

/* pop: get the value from stack */
double pop(void) {
  double v = 0.0;
  if (sp >= 0) v = val[--sp];
  return v;
}

/* eval: arithmetic operations */
double eval(double arg1, double arg2, char op) {
  double res = 0.0;
  switch (op) {
    case '*':
      res = arg1 * arg2;
      break;
    case '/':
      if (arg2 != 0.0) res = arg1 / arg2;
      break;
    case '%':
      if (arg2 != 0.0) res = fmod(arg1, arg2);
      break;
    case '+':
      res = arg1 + arg2;
      break;
    case '-':
      res = arg1 - arg2;
      break;
    default:
      return 0.0;
      break;
  }
  return res;
}

