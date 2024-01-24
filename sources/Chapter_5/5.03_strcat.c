#include <stdio.h>
#define BUFSIZE 1000

/* Lesson 5.3. Write function strcat(), using pointers */

int str_cat(char *, char *);
int get_line(char *, int);

int main(void) {
  char s1[BUFSIZE], s2[BUFSIZE], res[BUFSIZE];
  int len, len2, len_res;

  printf("Enter first string: ");
  if (len = get_line(s1, BUFSIZE)) {
    printf("Enter second string: ");
    if (len2 = get_line(s2, BUFSIZE)) {
      if (len_res = str_cat(s1, s2)) {
        printf("Concatenated string: \"%.*s\", total length is %d\n", len_res - 1, s1, len_res);
      }
    }
  }
  return 0;
}

int str_cat(char *src, char *str) {
  int len = 0;

  while (*src) {
    len++; /* count the length, going to the end of line */
    src++; /* to concatenate, trailing '\0' should be overwritten */
  }

  while (*src++ = *str++)
    len++;

  return len;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  int len = 0;

  while (lim-- && (buf[len] = getchar()) != EOF && buf[len++] != '\n');
  /* it is possible to use the index, instead of pointer. Here is useful. */
  buf[len] = '\0';
  return len;
}
