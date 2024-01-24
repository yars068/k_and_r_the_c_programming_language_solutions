#include <stdio.h>
#define BUFSIZE 100

/* Lesson 5.5. Write a realization of library function strncpy() */

void strn_cpy(char *, char *, int);
int get_line(char *, int);

int main(void) {
  enum state { NO = 0, YES };
  char buf[BUFSIZE];
  char res[BUFSIZE];
  int state = YES;
  int len = 0;

  while (state) {
    printf("Enter string: ");
    if (len = get_line(buf, BUFSIZE)) {
      strn_cpy(res, buf, len - 1);
      printf("Result is: \"%s\"\n", res);
    }
    else state = NO;
  }
  return 0;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  int len = 0;

  while (lim-- && (buf[len] = getchar()) != EOF && buf[len++] != '\n');
  /* it is possible to use the index, instead of pointer. Here is useful. */
  buf[len] = '\0';
  return len;
}

void zeroe(char *, int);

/* strn_cpy: copy at most sz characters from string src into character sequence dst */
void strn_cpy(char *dst, char *src, int sz) {
  zeroe(dst, sz);
  while (sz--) *dst++ = *src++;
}

/* zeroe: fill at most sz characters in character sequence buf with zeroes */
void zeroe(char *buf, int sz) {
  while (sz--) *buf++ = '\0';
}
