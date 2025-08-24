#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFSIZE 1024U

/* Lesson 5.6. Rewrite the programs from the previous exercises, using pointers */

/* Lesson 3.2. Write a function escape(s, t), which while copying text /*
/* from s to t transform the escape sequences '\t' and '\n' to be visible */
/* Write a function for a backward transformation */

int get_line(char *buf, int lim);
int escape(char *s, char *t);
int unescape(char *s, char *t);
void clean(char *buf, int lim);

int main(void) {
  enum { FALSE, TRUE };
  char src[BUFSIZE] = { 0 };
  char target[BUFSIZE] = { 0 };
  int try = FALSE;

    printf("Enter text contains a newlines and tabulations:\n");
    if (get_line(src, BUFSIZE)) {
      /* First, escape(): */
      if (escape(src, target))
        printf("Escaped text: \n\"%s\"\n", target);
      else {
        printf("Error occured while escaping. Exiting.\n");
        return EXIT_FAILURE;
      }
      /* Then, unescape(). Before we start, clear the buffer */
      clean(src, BUFSIZE);

      if (unescape(target, src)) {
        printf("Unescaped text: \n\"%s\"\n", src);
      }
      else {
        printf("Error occured while unescaping. Exiting.\n");
        return EXIT_FAILURE;
      }
    }

  return EXIT_SUCCESS;
}

int escape(char *s, char *t) {
  int len = 0;

  do {
    switch (*s) {
      default: 
       *t++ = *s;
       len++;
       break;
      case ('\n'):
        *t++ = '\\';
        *t++ = 'n';
        len += 2;
        break;
      case ('\t'):
        *t++ = '\\';
        *t++ = 't';
        len += 2;
        break;
    }
  } while (*s++);

  return len;
}

int unescape(char *s, char *t) {
  int len = 0;

  while (*s) {
    if (*s != '\\') {
      *(t++) = *(s++);
      len++;
    }
    if (*s == '\\' && *(s + 1) == 't') {
      *(t++) = '\t';
      s += 2;
      len++;
    }
    else if (*s =='\\' && *(s + 1) == 'n') {
      *(t++) = '\n';
      s += 2;
      len++;
    }
  }
  return len;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *tmp = buf;

  while (lim-- && (*tmp = getchar()) != EOF && *tmp++ != '\n');
  *tmp++ = '\0';
  return tmp - buf;
}

void clean(char *buf, int lim) {
  while (lim-- && *buf)
    *buf++ = '\0';
}
