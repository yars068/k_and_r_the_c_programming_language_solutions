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
int shrink(char *, char *);
void clear(char *);

int main(void) {
  enum { NONE, SINGLE_QUOTE, DOUBLE_QUOTE, STRING_BEGIN, INLINE_BEGIN, INLINE_END};
  char buf[BUFSIZE];
  char *msg = "Enter text: ";
  char *patterns[] = { "", "\'" , "\"", "//", "/*", "*/", NULL };
  const int ptsz = 2; /* maximal pattern size (i.e., its length) */
  char *start, *end;
  int len, lineno = 0;
  int state = NONE;

  while ((len = get_line(buf, BUFSIZE)) != EOF && len) {
    for (char *bp = buf; *bp; *bp++) {
      char *quote = NULL;
      char *comment = NULL;
      int i, j;
      for (i = SINGLE_QUOTE; i <= DOUBLE_QUOTE && (quote = substrf(bp, *(patterns + i))) == NULL; i++);

      for (j = STRING_BEGIN; j <= INLINE_BEGIN && (comment = substrf(bp, *(patterns + j))) == NULL; j++);

      if ((quote != NULL) && (comment != NULL) && (comment < quote)) {
        if (j == STRING_BEGIN) {
          bp += comment - buf;
          len = shrink(bp, buf + len);
        }
        else if ((j == INLINE_BEGIN) && (end = substrl(comment, *(patterns + INLINE_END))) != NULL) {
          bp += end - buf;
          len = shrink(bp, end);
        }
      }
      else if ((quote != NULL) && (end = substrl(quote, *(patterns + i))) != NULL) bp += end - buf;
      if ((comment != NULL) && (j == STRING_BEGIN)) {
        bp += comment - buf;
        len = shrink(bp, buf + len);
      }
      else if ((j == INLINE_BEGIN) && (end = substrl(comment, *(patterns + INLINE_END))) != NULL) {
        bp += end - buf;
        len = shrink(bp, end);
      }
      if (comment == NULL && quote == NULL) bp += len;
    }
    lineno++;
    // printf("==== Result: ====\n%s\n", buf);
    if (len) printf("%s", buf);
    clear(buf);
  }
  //putchar('\n');
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

/* shrink: shrink the part of the line starting from start */
int shrink(char *start, char *end) {
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
