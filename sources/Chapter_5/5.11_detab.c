#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1024
#define TABSIZE 8

/* Lesson 5.11. Modify the programs entab and detab (see lessons 1.20 and 1.21) */
/* to accept a list of tab stops as arguments. Use the default tab settings /* 
/* if there are no arguments */

int ask_line(char *buf, int lim, char *msg);
int get_line(char *buf, int lim);
int detab(char *buf);
int entab(char *buf);

int main(int argc, char *argv[]) {
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

/* get_count_spaces: return count of spaces to first non-space character */
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

/* ask_line: print a question to user and store the answer */
int ask_line(char *buf, int lim, char *msg) {

  printf("%s", msg);
  return get_line(buf, lim);
}
