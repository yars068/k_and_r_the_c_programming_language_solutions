#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#define BUFSIZE 1024
#define DIGITS 10
#define ALPHA 26
#define VAR 0

/* Lesson 5.6. Rewrite lesson 1.14, using pointers */
/* Lesson 1.14. Write the program that will print the histogram */
/* of frequency of occurence of characters */

int get_line(char *, int);
double percent(int *, int, int);
char *histo(double, char *);
void clear_text(char *);
void clear_int(int *, int);

int main(void) {
  enum state { YES, NO };
  char buf[BUFSIZE], hstgrm[BUFSIZE];
  char *bp = buf;
  int digits[DIGITS] = { 0 }, upper[ALPHA] = { 0 }, lower[ALPHA] = { 0 };
  int brackets = 0, lines = 0, math = 0, punct = 0, spaces = 0, others = 0;
  int sizes[] = { DIGITS, ALPHA, ALPHA, VAR,       VAR,    VAR,   VAR,    VAR,     VAR,     VAR  };
  int *vars[] = { digits, upper, lower, &brackets, &lines, &math, &punct, &spaces, &others, NULL };
  const char *names[] = { "digits", "upper", "lower", "brackets", "lines", "math", "punct", "spaces", "others", "" };
  int idx = 0;
  int len = NO;
  double percentage = 0;

  while (len != EOF && len) {
    printf("Type something: ");
    if (len = get_line(bp, BUFSIZE)) {
      while (*bp) {
        if (isdigit(*bp)) digits[*bp - '0']++;
        else if (isupper(*bp)) upper[*bp - 'A']++;
        else if (islower(*bp)) lower[*bp - 'a']++;
        else if (isblank(*bp)) ++spaces;
        else if (*bp == '`' || *bp == '_') ++punct;
        else if (*bp == ':' || *bp == ';') ++punct;
        else if (*bp == '`' || *bp == '_') ++punct;
        else if (*bp == ':' || *bp == ';') ++punct;
        else if (*bp == '!' || *bp == '?') ++punct;
        else if (*bp == '"' || *bp == '\'') ++punct;
        else if (*bp == '.' || *bp == ',')  ++punct;
        else if (*bp == '(' || *bp == ')') ++brackets;
        else if (*bp == '[' || *bp == ']') ++brackets;
        else if (*bp == '{' || *bp == '}') ++brackets;
        else if (*bp == '*' || *bp == '/') ++math;
        else if (*bp == '+' || *bp == '-') ++math;
        else if (*bp == '>' || *bp == '<') ++math;
        else if (*bp == '=' || *bp == '|') ++math;
        else if (*bp == '\n') ++lines;
        else ++others;

        bp++;

      }
      printf("characters total: %d\n", len);
      idx = 0;
      while (*(vars + idx) != NULL) {
        percentage = percent(*(vars + idx), *(sizes + idx), len);
        printf("%10s: %4.2g: %s\n", *(names + idx), percentage, histo(percentage, hstgrm));
        idx++;
      }

      clear_text(bp); /* reset buffers and variables */
      for (idx = 0; *(vars + idx) != NULL; idx++) clear_int(*(vars + idx), *(sizes + idx));
    }
  }
  if (!len) putchar('\n');
  return 0;
}

char *histo(double pt, char *buf) {
  const double maxlen = 20, percent = 100; /* maximum characters for 100% */
  int i = 0, count = (int) (pt * maxlen) / percent;
  clear_text (buf);
  while (i < count) *(buf + i++) = '+';
  return buf;
}

double percent(int *val, int sz, int count) {
  const int percent = 100; /* 100% */
  int idx = 0, total = 0;

  do {
    total += *(val + idx);
    idx++;
  }
  while (idx < sz);

  return (double) (total / (double) count) * percent;
}

void clear_text(char *buf) {
  while (*buf) *buf++ = '\0';
}

void clear_int(int *var, int sz) {
  int i = 0;
  while (i < sz) *(var + i++) = 0;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  if (!lim) return EOF; /* buffer is full */
  *buf = '\0';
  return buf - start;
}
