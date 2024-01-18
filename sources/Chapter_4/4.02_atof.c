#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

/* Lesson 4.2. Modify the function atof() to allow working with numbers like 123.456e-1, */
/* possible with a sign */
double atof_orig(const unsigned char s[]);
double atof(const unsigned char s[]);
int get_line(char buf[], int lim, const unsigned char msg[]);


int main(void) {
  double num = 0.0;
  //unsigned char buf[] = "1.524e2";
  unsigned char buf[BUFSIZE] = { '\0' };
  int len = 0;
  //double atof(const unsigned char s[]);

  if (len = get_line(buf, BUFSIZE, "Enter a real number:")) {
    num = atof(buf);
    printf("Result of transformation (normalized form): \"%.*s\" to double %1.3e\n", (len - 1), buf, num);
    printf("Result of transformation (decimal form): \"%.*s\" to double %g\n", (len - 1), buf, num);
  }

  return 0;
}

double atof(const unsigned char s[]) {
  enum status { NO = 0, YES };
  double base = 10.0;
  double res, power = 1.0;
  int have_dot = NO;
  int have_exp = NO;
  int exp = 0;
  int i, m_sign, e_sign;

  for (i = 0; isspace(s[i]); i++); /* skip leading delimiters */

  m_sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') i++; /* skip the sign symbol */
  
  for (res = 0.0; s[i] != '\n' && s[i] != '\0'; i++) {
    if (isdigit(s[i])) {
      res = res * base + (s[i] - '0');
      if (have_dot) power *= base;
    }
    else if (s[i] == '.' && !have_dot)
      have_dot = YES;

    else if (s[i] == 'e' || s[i] == 'E') {
      have_exp = YES;
      i++; /* skip exponent sign */
      break;
    }
  }

  e_sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') i++; /* skip the sign symbol */

  while (have_exp && s[i] != '\n' && s[i] != '\0') {
    if (isdigit(s[i])) exp = exp * base + s[i] - '0';
    i++;
  }

  res = m_sign * res / power;

  for (i = 0; have_exp && i < exp; ++i) {
    if (e_sign > 0) base = 10.0;
    else base = 1.0 / 10.0;
    res *= base;
  }

  return res;
}

/* get_line: store the input stream to array buf */
int get_line(char buf[], int lim, const unsigned char msg[]) {
  int i = 0;
  unsigned char c;

  printf("%s ", msg);
  while (i < lim-- && ((c = getchar()) != EOF) && c != '\n')
    buf[i++] = c;

  if (c == '\n') buf[i++] = '\n';

  buf[i] = '\0';
  return i;
}

/* atof-orig: transform the string s to a number type of double */
double atof_orig (const unsigned char s[]) {
  double val, power;
  int i, sign;

  for (i = 0; isspace (s[i]); i++); /* ignore leading delimiters */

  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') i++; /* skip the sign symbol */

  for (val = 0.0; isdigit (s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if (s[i] == '.') i++; /* skip the decimal dot */

  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }

  return sign * val / power;
}
