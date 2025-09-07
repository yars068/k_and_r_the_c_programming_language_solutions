#include <stdio.h>

#define BUFSIZE 1024
#define FOLDLEN 72

/* Lesson 1.22. Write a program to "fold" the lines longer than n (80 by default) */
/* symbols into two or more shorter lines */

int fold(char buf[], int bufsize, int len, int fold_len);
int get_line(char buf[], int lim);

int main(void) {
  char buf[BUFSIZE];
  int len = 0;
  int pos = 0;

  /* initialize array buf */
  for (pos = 0; pos < BUFSIZE; ++pos) buf[pos] = '\0';

  printf("Type something:\n");
  while ((len = get_line(buf, BUFSIZE)) > 0) {
    if (fold(buf, BUFSIZE, len, FOLDLEN) > 0) {
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

int fold(char buf[], int bufsize, int len, int fold_len) {
  char tmp[BUFSIZE] = { '\0' };
  int bi = 0; /* index for buf */
  int ti = 0; /* index for tmp */

  if (len <= fold_len) return 0; /* too small line */

  /* copy the part of line before buf[maxlen] */
  while (ti <= fold_len && buf[bi] != '\0') tmp[ti++] = buf[bi++];

  /* then, find position to fold before maxlen */
  while (ti != 0 && tmp[ti] != ' ' && tmp[ti] != '\t') {
    ti--;
  }

  if (ti == 0) return 0; /* we returned to begiinig of line, cannot fold */
  else {
    tmp[ti++] = '\n'; /* insert a newline, then go to next element of array */
    bi = ti; /* copy the rest of line */
    while (bi < bufsize && buf[bi] != '\0') tmp[ti++] = buf[bi++];
  }

  /* Now, clear the input buffer, then copy the result from temporary buffer */
  for (ti = 0; ti < bufsize && tmp[ti] != '\0'; ti++)
    buf[ti] = tmp[ti];

  buf[ti] = '\0';

  return bufsize - ti; /* Inside the C program, non-null means true, 0 -- false */
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
