#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define BUFSIZE 1000
#define DEFTABSZ 8

int get_line(char *, int);

int main(int argc, char **argv) {
  enum { UNKNOWN, LETTER, DIGIT };
  int c, tabsz = DEFTABSZ;
  char buf[BUFSIZE];

  while (--argc > 0 && **++argv == '-') {
    while (c = *++(*argv)) {
      int arg, n = 0;
      arg = (isalpha(c)) ? LETTER : (isdigit(c)) ? DIGIT : UNKNOWN;
      switch (arg) {
        case DIGIT:
          while (isdigit(**argv))
            n = n * 10 + **argv++ - '0';
          break;
        case LETTER:
          if (c == 'n' && n != 0) tabsz = n;
          break;
        case UNKNOWN:default:
          if (argc) {
            printf("Unknown argument\n");
            return EXIT_FAILURE;
          }
          break;
      }
    }
  }
  printf("setting tabsize to %d\n", tabsz);

  return EXIT_SUCCESS;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  if (!lim) return EOF; /* buffer is full */
  *buf = '\0';
  return buf - start;
}
