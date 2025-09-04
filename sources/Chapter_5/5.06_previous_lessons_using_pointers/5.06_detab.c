#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

/* Lesson 5.6. Rewrite lesson 1.20 using pointers */
/* Lesson 1.20. Write the program 'detab', that replaces a tabulations */
/* with a proper number of spaces */

int ask_line(char *buf, int lim, char *msg);
int get_line(char *buf, int lim);
int detab(char *buf);

int main(void) {
  char buf[BUFSIZE];
  char *msg = "Enter a string to detabbing:\n";
  int len = 0;

  while(ask_line(buf, BUFSIZE, msg)) {
    if (detab(buf))
      printf("Detabbed text:\n%s", buf);

    else {
      printf("Unable to detab it, exiting\n");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

#define TAB '\t'
#define SPACE ' '

int eval_space_count(char *buf, char *start);

/* detab: replace a tabstops by proper count of spaces */
int detab(char *buf) {
  char tmpbuf[BUFSIZE] = { '\0' };
  char *tmp = tmpbuf;
  char *start = buf;
  int len = 0;

  /* Save input buffer to a local buffer, and clear it */
  for (int i = 0; *(tmp + i) = *(buf + i); i++) 
    *(buf + i) = '\0';

  while (*tmp) {
    if (*tmp != TAB) {
      *buf++ = *tmp++;
      len++;
    }
    else {
      int spaces = eval_space_count(buf, start);
      while (spaces--) {
        *buf++ = SPACE;
        len++;
      }
      *tmp++; /* skip current position, because here is a tabstop */
    }
  }
  return len;
}

#define TABSIZE 8

/* eval_space_count: returns the number of spaces needed to fill the current tabstop */
int eval_space_count(char *buf, char *start) {
  return (buf - start) ? (TABSIZE - (buf - start) % TABSIZE) % TABSIZE : TABSIZE;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *tmp = buf;

  while (lim-- && (*tmp = getchar()) != EOF && *tmp++ != '\n');
  *tmp++ = '\0';
  return tmp - buf;
}

/* ask_line: ask the question to user */
int ask_line(char *buf, int lim, char *msg) {

  printf("%s", msg);
  return get_line(buf, lim);
}
