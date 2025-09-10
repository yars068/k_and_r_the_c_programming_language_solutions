#include <stdio.h>

#define BUFSIZE 1024
#define FOLDLEN 72

/* Lesson 1.22. Write a program to "fold" the lines longer than n (80 by default) */
/* symbols into two or more shorter lines */

int fold(char buf[], int len, int fold_len);
int get_line(char buf[], int lim);

int main(void) {
  char buf[BUFSIZE];
  int len = 0;
  int pos = 0;

  /* initialize array buf */
  for (pos = 0; pos < BUFSIZE; ++pos) buf[pos] = '\0';

  printf("Type something:\n");
  while ((len = get_line(buf, BUFSIZE)) > 0) {
    if (fold(buf, len, FOLDLEN) > 0) {
      printf("\nFolded text:\n%s\n", buf);
      return 0; /* Success. Operating system expects 0 in this case, otherwise -- non-null */
    }
    else {
      printf("Can\'t fold\n");
      return 1;
    }
  }
  return 0;
}

/* fold: fold input lines longer than fold_len characters into two or more shorter lines */
int fold(char buf[], int len, int fold_len) {
  char s1[BUFSIZE] = { '\0' };
  char s2[BUFSIZE] = { '\0' };
  int bi = 0; /* index for buf */
  int s1i = 0; /* index for first temporary buffer */
  int s2i = 0; /* index for second temporary buffer */

  if (len <= fold_len) return 0; /* too small line */

  /* copy the part of line before buf[fold_len] */
  while (s1i < fold_len) s1[s1i++] = buf[bi++];

  /* then, find position to fold before fold_len */
  while (s1i != 0 && s1[s1i] != ' ' && s1[s1i] != '\t')
    s1[s1i--] = '\0';

  if (s1i == 0) return 0; /* we returned to begiinig of line, cannot fold */
  else {
    s1[s1i] = '\n'; /* to fold, just insert a newline, then go to next element of array */
    bi = s1i + 1; /* copy the rest of line to another buffer */
    while (bi < BUFSIZE && buf[bi] != '\0') s2[s2i++] = buf[bi++];

    fold(s2, s2i, fold_len); /* fold recursively the right part of original string */
  }

  /* Now, concatenate the result from both temporary buffers */
  for (s1i = 0; s1i < BUFSIZE && s1[s1i] != '\0'; s1i++)
    buf[s1i] = s1[s1i];

  for (s2i = 0; s2i < BUFSIZE && s2[s2i] != '\0'; s2i++)
    buf[s1i++] = s2[s2i];

  buf[s1i] = '\0';

  return s1i; /* Inside the C program, non-null means true, 0 -- false */
}

/* get_line: store a string to input buffer */
int get_line(char s[], int lim) {
  int c; /* no sense to initialize this variable, because it will be overwritten */
  int len = 0;

  while (len < lim - 1 && (c = getchar()) != EOF && c != '\n')
    s[len++] = c;

  if (c == '\n') s[len++] = c;
  s[len] = '\0';
  return len;
}
