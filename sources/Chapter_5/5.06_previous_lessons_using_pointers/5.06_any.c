#include <stdio.h>
#define BUFSIZE 1024

/* Lesson 5.6. Rewrite lesson 2.5 using pointers */
/* Lesson 2.5. Write function any(s1, s2) that returns the 
   first position number of s1 matched to any of character in s2,
   or -1 if no match */

int any(char *, char *);
int get_line(char *, int);

int main(void) {
  char s1[BUFSIZE];
  char s2[BUFSIZE];
  int len, len2, pos;

  printf("Enter the string: ");
  len = get_line(s1, BUFSIZE);
  if (len > 1) {
    printf("Enter the pattern: ");
    len2 = get_line(s2, BUFSIZE);
  }
  if (len > 1 && len2 && (pos = any(s1, s2)) >= 0)
    printf("First match is \'%c\' at position %d\n", *(s1 + pos), pos);
  else printf("\nNo match found\n");
}

/* any: find the first position of s1 that matches the any character from s2 */
int any(char *s1, char *s2) {
  const int none = -1;
  int idx1 = 0;

  while (*(s1 + idx1)) {
    int idx2 = 0;
    while (*(s2 + idx2)) {
      if (*(s1 + idx1) == *(s2 + idx2))
        return idx1;
      idx2++;
    }
    idx1++;
  }
  return none;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  *buf = '\0';
  return buf - start;
}
