#include <stdio.h>
#define BUFSIZE 1024

/* Lesson 5.6. Rewrite lesson 2.4 using pointers */
/* Lesson 2.4. Remove all characters from string s1 that given in string s2 */

int get_line(char *, int);
int squeeze(char *, char *);

int main(void) {
  char s1[BUFSIZE];
  char s2[BUFSIZE];
  int len, len2;

  printf("Enter the string: ");
  len = get_line(s1, BUFSIZE);
  if (len > 1) {
    printf("Enter the pattern to squeeze: ");
    len2 = get_line(s2, BUFSIZE);
  }
  if (len > 1 && len2 && squeeze(s1, s2))
    printf("Result: \"%.*s\"\n", len - 1, s1);
  else printf("\nNothing to do\n");
}

/* squeeze: remove all characters in s1 that given in s2 */
int squeeze(char *s1, char *s2) {
  enum state { NO, YES };
  int idx1 = 0;
  int flag = NO;

  while (*(s1 + idx1)) {
    int idx2 = 0;
    while (*(s2 + idx2)) {
      if (*(s1 + idx1) == *(s2 + idx2)) {
        int i = idx1;
        flag = YES;
        while (*(s1 + i) = *(s1 + (i + 1))) i++;
      }
      else *(s1 + idx1) = *(s1 + idx1);
      idx2++;
    }
    idx1++;
  }
  return flag;
}


/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  *buf = '\0';
  return buf - start;
}
