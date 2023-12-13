#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 1024U
#define FALSE -1

/* Lesson 3.2. Write a function escape(s, t), which while copying text /*
/* from s to t transform the escape sequences '\t' and '\n' to be visible */
/* Write a function for a backward transformation */

int escape(const char src[], char tgt[]) { /* WARNING! array overflow possible! */
  unsigned i = 0;
  unsigned j = 0;

  while (src[i] != '\0' && i < BUFSIZE && j < BUFSIZE) {
    switch (src[i]) {         /* Nowadays, the escape sequences becomes */
      default: {              /* to not use for text formatting, so, I guess, */
        tgt[j++] = src[i];    /* only '\t' and '\n' will be enough. */
        ++i;
        break;
      }
      case '\t': {
        tgt[j++] = '\\';
        tgt[j++] = 't';
        i++;
        break;
      }
      case '\n': {
        tgt[j++] = '\\';
        tgt[j++] = 'n';
        i++;
        break;
      }
    }
  }
  tgt[j] = '\0';
  if (i == j) return 0; /* no substitutions made or buffer overflow */
  else return j;
}

int unescape(char src[], char tgt[]) {
  unsigned i = 0;
  unsigned j = 0;
  unsigned state = FALSE;

  while (src[i] != '\0' && i < BUFSIZE) {
    switch (src[i]) {
      case '\\': {
          state = i;
        break;
      }
      case 't': {
        if (state != FALSE && src[state] == '\\') {
          tgt[j++] = '\t';
          state = FALSE;
        }
        else if (state == FALSE) {
          tgt[j++] = src[i];
        }
        break;
      }
      case 'n': {
        if (state != FALSE && src[state] == '\\') {
          tgt[j++] = '\n';
          state = FALSE;
        }
        else if (state == FALSE) {
          tgt[j++] = src[i];
        }
        break;
    }
      default: {
        tgt[j++] = src[i];
        break;
      }
    }
    i++;
  }

  tgt[j] = '\0';
  return j;
}

int get_line(unsigned char buf[], unsigned lim, const unsigned char msg[]) {
  int i = 0;
  char c = '\0';

  printf("%s ", msg);
  while (i < lim - 1 && ((c = getchar()) != EOF) && c != '\n')
    buf[i++] = c;

  if (c == '\n') buf[i++] = '\n';

  buf[i] = '\0';
  return i;
}

int main(void) {
  const unsigned char msg[] = "Enter a string:";
  unsigned char buf[BUFSIZE];
  unsigned char res[BUFSIZE];
  unsigned len = 0;
  
  while (len = get_line(buf, BUFSIZE, msg)) {
    printf("Result is:\n");
    if (escape(buf, res))
      printf("Escape sequences   screended:\n\"%s\"\n", res);

    while (len != 0) buf[len--] = '\0'; /* reset buffer */
    if (unescape(res, buf))
      printf("Escape sequences unscreended:\n\"%s\"\n", buf);
  }
}
