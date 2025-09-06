#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLINES 5000
#define DEFLINES 10

/* Lesson 5.13. Write program tail, which prints the last n lines of its input. */
/* By default, n is 10, and it should be possible to change via command line argument */

char *lineptr[MAXLINES]; /* pointers to strings */
int readlines(char **, int);
void writelines(char **, int);

int main(int argc, char *argv[]) {
  enum {NO, YES};
  int nlast = DEFLINES;
  int nlines = 0;
  int quiet = NO;

  while (--argc > 0 && **++argv == '-') {
    int n = 0;
    while (*(*argv)++) {
      switch (**argv) {
        case '0':case '1':case '2':case '3':case '4':
        case '5':case '6':case '7':case '8':case '9':
            if (isdigit(**argv)) n = n * 10 + **argv - '0';
            nlast = n;
          break;
        case 'q':
          quiet = YES;
          break;
        default:
          if (**argv) {
            printf("Unknown argument\n");
            return EXIT_FAILURE;
          }
          break;
      }
    }
  }
    if (!quiet) printf("Type text, then press Ctrl+D\n");
    if (((nlines = readlines(lineptr, MAXLINES)) >= 0) && nlines >= nlast) {
      writelines(lineptr + (nlines - nlast), nlast);
    }
    else if (nlines < nlast || nlast > nlines)
        writelines(lineptr, nlines);
    else if (nlines > MAXLINES) {
      printf("Too many strings\n");
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

/* writelines: print the lines */
void writelines(char **lineptr, int nlines) {
  while (nlines-- > 0)
    printf( "%s\n", *lineptr++);
}

#define MAXLEN 1000 /* string length limit */
int get_line(char *, int);
char *alloc(int);

/* readlines: read the lines, version 1 */
int readlines(char **lineptr, int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL) return -1;
    else {
      line[len-1] = '\0'; /* remove the '\n' character */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  if (!lim) return EOF; /* buffer is full */
  *buf = '\0';
  return buf - start;
}

#define ALLOCSIZE 10000 /* count of space total */
static char allocbuf[ALLOCSIZE]; /* buffer for alloc */
static char *allocp = allocbuf; /* pointer to the free space */

/* alloc: returns the poitner to next free position */
char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n; /* space enough */
    return allocp - n; /* old р */
  }
  else return 0; /* no space */
}

/* afree: free the space pointed by р */
void afree(char *p) {
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
  allocp = p;
}
