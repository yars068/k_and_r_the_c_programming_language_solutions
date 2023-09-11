#include <stdio.h>
#define SHIFT 26
#define ALPHA 52
#define NO_SHIFT 0
#define DO_SHIFT 1

/* Write the program that will print the histogram of frequency of occurence
   of characters */

int main() {
  int digits[10], letters[ALPHA], lines, punct, spaces, math, others;
  int brackets, i, j, shift, do_shift, start, end;
  char c;

  for (i = 0; i < 10; ++i) digits[i] = 0;
  for (i = 0; i < ALPHA; ++i) letters[i] = 0;
  lines = punct = spaces = math = others = brackets =  0;

  while ((c = getchar()) != EOF) {
    if (c >= '0' && c <= '9') ++digits[c - '0'];
    else if (c >= 'a' && c <= 'z') ++letters[c - 'a'];
    else if (c >= 'A' && c <= 'Z') ++letters[SHIFT + (c - 'A')];
    else if (c == ' ' || c == '\t') ++spaces;
    else if (c == '`' || c == '_') ++punct;
    else if (c == ':' || c == ';') ++punct;
    else if (c == '!' || c == '?') ++punct;
    else if (c == '"' || c == '\'') ++punct;
    else if (c == '.' || c == ',')  ++punct;
    else if (c == '(' || c == ')') ++brackets;
    else if (c == '[' || c == ']') ++brackets;
    else if (c == '{' || c == '}') ++brackets;
    else if (c == '*' || c == '/') ++math;
    else if (c == '+' || c == '-') ++math;
    else if (c == '>' || c == '<') ++math;
    else if (c == '=' || c == '|') ++math;
    else if (c == '\n') ++lines;
    else ++others;
  }

  printf("Letters:\n");
  /* Здесь можно было обойтись без лишних переменных и именованных констант,
     просто повторив два раз цикл for i... Но мы не ищем легких путей :) */
  do_shift = NO_SHIFT;
   while (do_shift <= DO_SHIFT) {
    if (do_shift == DO_SHIFT) {
      start = 'A';
      end = 'Z';
      shift = SHIFT;
    }
    else {
      start = 'a';
      end = 'z';
      shift = NO_SHIFT;
    }
    for (i = start; i <= end; ++i) {
      printf("\'%c\': ", i);
      for (j = 0; j < letters[shift + (i - start)]; ++j) putchar('+');
      putchar('\n');
    }
    ++do_shift;
  }

  printf("Digits:\n");
  for (i = 0; i <= 9; ++i) {
    printf("\'%d\': ", i);
    for (j = 0; j < digits[i]; ++j) putchar('+');
  putchar('\n');
  }
  printf("Punctuation: ");
  for (i = 0; i < punct; ++i) putchar('+');
  putchar('\n');

  printf("Spaces: ");
  for (i = 0; i < spaces; ++i) putchar('+');
  putchar('\n');

  printf("Mathematics: ");
  for (i = 0; i < math; ++i) putchar('+');
  putchar('\n');

  printf("Brackets: ");
  for (i = 0; i < brackets; ++i) putchar('+');
  putchar('\n');

  printf("Others: ");
  for (i = 0; i < others; ++i) putchar('+');
  putchar('\n');

  printf("Lines: ");
  for (i = 0; i < lines; ++i) putchar('+');
  putchar('\n');
}
