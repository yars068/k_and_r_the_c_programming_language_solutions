#include <stdio.h>
#define BUFSIZE 24

/* Lesson 5.6. Rewrite lesson 4.2 using pointers */
/* Lesson 4.2. Modify the function atof() to work with numbers like 123.456e-1, */
/* possible with a sign */

double atof(const char *);
int get_line(char *, int);

int main(void) {
  double num = 0.0;
  char buf[BUFSIZE] = { '\0' };
  char *bp = buf;
  int len = 0;
  printf("Enter a number: ");
  if (len = get_line(bp, BUFSIZE)) {
    num = atof(bp);
    printf("Result of transformation (normalized form): \"%.*s\" to double %1.3e\n", (len - 1), buf, num);
    printf("Result of transformation (decimal form): \"%.*s\" to double %g\n", (len - 1), buf, num);
  }

  return 0;
}

#ifndef _CTYPE_H
#include <ctype.h>
#endif
/* atof: transform text represented floating-point number to number itself */
double atof(const char *buf) {
  enum status { NO = 0, YES };
  double base = 10.0;
  double power = 1.0;
  double res = 0.0;
  int have_dot = NO;
  int have_exp = NO;
  int exp = 0;
  int m_sign, e_sign;

  while (isspace(*buf)) buf++; /* skip leading delimiters */

  m_sign = (*buf == '-') ? -1 : 1;
  if (*buf == '+' || *buf == '-') buf++; /* skip the sign symbol */
  
  while (*buf) {
    if (isdigit(*buf)) {
      res = res * base + (*buf - '0');
      if (have_dot) power *= base;
    }
    else if (*buf == '.' && !have_dot)
      have_dot = YES;

    else if (*buf == 'e' || *buf == 'E') {
      have_exp = YES;
      buf++; /* skip the exponent sign */
      break;
    }
    buf++;
  }

  e_sign = (*buf == '-') ? -1 : 1;
  if (*buf == '+' || *buf == '-') buf++; /* skip the sign symbol */

  while (have_exp && *buf)
    if (isdigit(*buf)) exp = exp * base + (*buf++ - '0');

  res = m_sign * res / power;

  for (int i = 0; have_exp && i < exp; ++i) {
    if (e_sign > 0) base = 10.0;
    else base = 1.0 / 10.0;
    res *= base;
  }

  return res;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  *buf = '\0';
  return buf - start;
}
