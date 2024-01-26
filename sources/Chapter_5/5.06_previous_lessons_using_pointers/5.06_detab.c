#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 1024

/* Lesson 5.6. Rewrite lesson 1.20 using pointers */
/* Lesson 1.20. Write the program 'detab', that replaces a tabulations 
   with a needed number of spaces */

int get_line(char *, int);
int get_space_count(char *, const char *);

int main(void) {
  enum state { YES = 0, NO };
  int len = NO;
  char buf[BUFSIZE]; char res[BUFSIZE];
  char *bp = buf, *res_p = res;

  while (len) {
    printf("Enter a string: \n");
    if (len = get_line(buf, BUFSIZE)) {
      while (*bp) {
        while (!isblank(*bp)) *res_p++ = *bp++; /* skip while not a tab */
        if (*bp == '\t') {
          int space_num = get_space_count(res, res_p);
          while (space_num--) *res_p++ = ' ';
        }
        bp++;
      }
    }
    printf("Result:\n%.*s\n", res_p - res, res);
    while (bp - buf) *bp-- = '\0'; /* clear buffers */
    while (res_p - res) *res_p-- = '\0';
  }
  return 0;
}

#ifndef TABSTOP
#define TABSTOP 8
#endif
/* get_space_cont: returns the number of spaces needed to replace a tab */
int get_space_count(char *start, const char *current) {
  int tab_pos = 0;
  int tab_num = 0;
  int space_count;

  while (tab_pos <= (current - start)) {
    tab_pos = tab_num * TABSTOP;
    space_count = tab_pos - (current - start);
    ++tab_num;
  }
  return space_count;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  *buf = '\0';
  return buf - start;
}
