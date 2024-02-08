#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 1024

/* Lesson 5.6. Rewrite the program from lesson 1.23 */
/* Lesson 1.23. Write a program that removes the comments from the C program */
/* Comments do not nest */

int ask_line(char *, int, char *);
int get_line(char *, int);
char *substrf(char *, char *);
char *substrl(char *, char *);
int shift(char *, char *);
void clear(char *);

int main(void) {
  char *dbgtxt[] = { "NONE", "SINGLE_QUOTE", "DOUBLE_QUOTE", "STRING_COMMENT", "INLINE_BEGIN", "INLINE_END", NULL };
  enum { NONE, SINGLE_QUOTE, DOUBLE_QUOTE, STRING_COMMENT, INLINE_BEGIN, INLINE_END};
  char buf[BUFSIZE];
  char *msg = "Enter text: ";
  char *patterns[] = { "", "\'" , "\"", "//", "/*", "*/", NULL };
  const int ptsz = 2; /* maximal pattern size (i.e., its length) */
  char *start, *end;
  int len, lineno = 0;
  int state = NONE;

  while ((len = get_line(buf, BUFSIZE)) != EOF && len) {
    for (char *bp = buf; *bp; *bp++) {
      if ((start = substrf(buf, *(patterns + SINGLE_QUOTE))) != NULL) {
        bp += start - buf;
        fprintf(stderr, "line %d: starting \"%s\" at pos %d\n", lineno, *(dbgtxt + SINGLE_QUOTE), start - buf);
        if ((end = substrl(buf, *(patterns + SINGLE_QUOTE))) != NULL) {
          fprintf(stderr, "line %d: ending \"%s\" at pos %d\n", lineno, *(dbgtxt + SINGLE_QUOTE), end - buf);
          fprintf(stderr, "line %d is: %s\n", lineno, buf);
          bp += end - buf;
        }
      }
      else if ((start = substrf(buf, *(patterns + DOUBLE_QUOTE))) != NULL) {
        bp += start - buf;
        fprintf(stderr, "line %d: starting \"%s\" at pos %d\n", lineno, *(dbgtxt + DOUBLE_QUOTE), start - buf);
        if ((end = substrl(buf, *(patterns + DOUBLE_QUOTE))) != NULL) {
          fprintf(stderr, "line %d: ending \"%s\" at pos %d\n", lineno, *(dbgtxt + DOUBLE_QUOTE), end - buf);
          fprintf(stderr, "line %d is: %s\n", lineno, buf);
          bp += end - buf;
        }
      }
      else if ((start = substrf(buf, *(patterns + STRING_COMMENT))) != NULL) {
        bp += start - buf;
        len = shift(start, (buf + len - 1));
        fprintf(stderr, "line %d: starting \"%s\" at pos %d\n", lineno, *(dbgtxt + STRING_COMMENT), start - buf);
        fprintf(stderr, "line %d is: %s\n", lineno, buf);
      }
      else if ((start = substrf(buf, *(patterns + INLINE_BEGIN))) != NULL) {
        bp += start - buf;
        //FIXME: shift() on separate lines;
        fprintf(stderr, "line %d: starting \"%s\" at pos %d\n", lineno, *(dbgtxt + INLINE_BEGIN), start - buf);
        fprintf(stderr, "line %d is: %s\n", lineno, buf);
        if ((end = substrl(buf, *(patterns + INLINE_END))) != NULL) {
          fprintf(stderr, "line %d: ending \"%s\" at pos %d\n", lineno, *(dbgtxt + INLINE_END), end - buf);
          fprintf(stderr, "line %d is: %s\n", lineno, buf);
          bp += end - buf;
          len = shift(start, end + 1);
        }
      }
    }
    fprintf(stderr, "line %d: length is: %d\n", lineno, len);
    lineno++;
    //printf("==== Result: ====\n%s\n", buf);
    if (len) printf("%s", buf);
    clear(buf);
  }
  putchar('\n');
  return EXIT_SUCCESS;
}

/* substr: return a pointer to first position in s, where p occurs, or NULL if no occurence */
char *substrf(char *s, char *p) {
  char *res = NULL;
  int i;

  while (*s) {
    if (*s == *p) {
      if (res == NULL) res = s;
      for (i = 0; *s && *(p + i) && *s == *(p + i); i++, s++);

      if (i > 0 && !*(p + i)) return res;
      else res = NULL;
    }
    s++;
  }
  return NULL;
}

/* substrl: return a pointer to last position in s, where p occurs, or NULL if no occurence */
char *substrl(char *s, char *p) {
  int i;

  while (*s) {
    if (*s == *p) {
      for (i = 0; *s && *(p + i) && *s == *(p + i); i++) s++;

      if (i > 0 && !*(p + i)) return s;
    }
    s++;
  }
  return NULL;
}

/* shift: move characters from right to left, starting from start */
int shift(char *start, char *end) {
  while (*start++ = *end++);
  return end - start;
}

void clear(char *buf) {
  while (*buf++ = '\0');
}

int ask_line(char *buf, int lim, char *msg) {
  printf("%s", msg);
  return get_line(buf, lim);
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  if (!lim) return EOF; /* buffer is full */
  *buf = '\0';
  return buf - start;
}
