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
  enum { SINGLE_QUOTE, DOUBLE_QUOTE, STRING_COMMENT, INLINE_BEGIN, INLINE_END};
  enum { NO, YES };
  char buf[BUFSIZE];
  char *bp;
  char *msg = "Enter text: ";
  char *patterns[] = { "\'" , "\"", "//", "/*", "*/", NULL };
  const int ptsz = 2; /* maximal pattern size (i.e., its length) */
  char *start, *end;
  char *bufend;
  int len;
  int comment = NO;
  int quote = NO;

  while ((len = get_line(buf, BUFSIZE)) != EOF && len) {
    bp = buf;
    bufend = buf + len;
    while (*bp && len) {
      for (int i = SINGLE_QUOTE; *buf && i <= INLINE_END; i++) {
        if (quote != SINGLE_QUOTE && (start = substrf(bp, *(patterns + i))) != NULL && i == SINGLE_QUOTE) {
          quote = SINGLE_QUOTE;
          bp = start;
          fprintf(stderr, "processing \"%s\", len = %d, quote = YES, bp points to buf[%d] = \'%c\'\n", buf, len, start - buf, *start);
        }
        if (quote == SINGLE_QUOTE && (end = substrl(bp, *(patterns + i))) != NULL && i == SINGLE_QUOTE) {
          quote = NO;
          bp = end;
          fprintf(stderr, "processing \"%s\", len = %d, quote = NO, bp points to buf[%d] = \'%c\'\n", buf, len, end - buf, *end);
        }
        if (quote != DOUBLE_QUOTE && (start = substrf(bp, *(patterns + i))) != NULL && i == DOUBLE_QUOTE) {
          quote = DOUBLE_QUOTE;
          bp = start;
          fprintf(stderr, "processing \"%s\", len = %d, quote = YES, bp points to buf[%d] = \'%c\'\n", buf, len, start - buf, *start);
        }
        if (quote == DOUBLE_QUOTE && (end = substrl(bp, *(patterns + i))) != NULL && i == DOUBLE_QUOTE) {
          quote = NO;
          bp = end;
          fprintf(stderr, "processing \"%s\", len = %d, quote = NO, bp points to buf[%d] = \'%c\'\n", buf, len, end - buf, *end);
        }
        if (!quote && (start = substrf(bp, *(patterns + i))) != NULL && i == STRING_COMMENT) {
          len -= shift(start, bufend);
          bp = start;
          comment = STRING_COMMENT;
        }
        if (comment != STRING_COMMENT && !quote && (start = substrf(bp, *(patterns + i))) != NULL && i == INLINE_BEGIN) {
          if ((end = substrl(start + ptsz, *(patterns + (i = INLINE_END)))) != NULL) {
            comment = NO;
            len -= shift(start, end);
            bp = end;
          }
          else if (comment != INLINE_END && end == NULL) {
            comment = INLINE_END;
            len -= shift(start, bufend);
            bp = start;
          }
        }
        if (len && !quote && comment == INLINE_END && (end = substrl(buf, *(patterns + (i = INLINE_END)))) != NULL) {
          comment = NO;
          len -= shift(bp, end);
          bp = end;
        }
        if (*bp && quote) bp++;
      }
    }
    //printf("==== Result: ====\n%s\n", buf);
    printf("%s", buf);
    clear(buf);
    quote = NO;
    if (comment == STRING_COMMENT) comment = NO;
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
