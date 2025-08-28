#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLEN 1000
#define TABSIZE 8

/* Lesson 5.6 Rewrite lesson 1.21 using pointers */
/* Write a program 'entab', that replace sequences of blanks to a
   minimal number of blanks and tab stops, keep the view of printed
   text unchanged */

int get_line(char *buf, int lim);
int ask_line(char *buf, int lim, char *msg);
int entab(char *buf, int tabsize);

int main(void) {
  char buf[MAXLEN] = { '\0' };
  char *msg = "Type someting:\n";

  while (ask_line(buf, MAXLEN, msg)) {
    if (entab(buf, TABSIZE))
      printf("Result:\n%s\n", buf);
    else {
      printf("Error can\'t entab this, exiting\n");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

/* entab: replace sequences of spaces by proper number of tabstops and spaces, */
/* keeping input looks unchanged */
#define SPACE ' '
#define TAB '\t'
int get_count_spaces(char *buf);

int entab(char *buf, int tabsize) {
  char tmpbuf[MAXLEN] = { '\0' };
  char *tmp = tmpbuf;

  /* First, copy input buffer to local buffer and clear input buffer */
  for (int i = 0; *(tmp + i) = *(buf + i); i++) *(buf + i) = '\0';

  char *start = tmp;
  /* Then, entab it */
  while (*tmp) {
    int num_spaces = 0;
    if (*tmp != SPACE) *buf++ = *tmp++;
    else {
      num_spaces = get_count_spaces(tmp);
      tmp += num_spaces;
      while (num_spaces) {
        if (num_spaces > tabsize) {
          *buf++ = TAB;
          num_spaces -= tabsize;
        }
        else if (num_spaces > tabsize / 2) {
          *buf++ = TAB;
          num_spaces -= tabsize / 2;
        }
        else {
          *buf++ = SPACE;
          num_spaces--;
        }
      }
    }
  }

  return tmp - start;
}

/* get_count-spaces: return count of spaces to first non-space character */
int get_count_spaces(char *buf) {
  int i = 0;
  while (*buf++ == SPACE) i++;

  return i;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *tmp = buf;

  while (lim-- && (*tmp = getchar()) != EOF && *tmp++ != '\n');
  *tmp++ = '\0';
  return tmp - buf;
}

int ask_line(char *buf, int lim, char *msg) {

  printf("%s", msg);
  return get_line(buf, lim);
}
