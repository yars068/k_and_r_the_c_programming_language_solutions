#include <stdio.h>

/* Lesson 4.7 Write a routine ungets(s) that will push back the entire string onto input */

int ungets(unsigned char []);
int get_line_buffered(unsigned char [], unsigned lim);

#define MAXLEN 100
unsigned char line[MAXLEN]; /* will push here */

int main(void) {
  unsigned char res[MAXLEN];
  unsigned len = 0;

  printf("Enter a string:\n");
  if (len = get_line_buffered(line, MAXLEN))
      printf("You entered: %.*s\n", ungets(res) - 1, res);
}

void ungetch(int); /* let's ungetch() and clear() to be visible for get_line_buffered() */

/* get_line_buffered(): store the string also into a buffer */
int get_line_buffered(unsigned char buf[], unsigned lim) {
  unsigned char c;
  unsigned len = 0;

  while (lim-- && (c = getchar()) != EOF && c != '\n') {
    buf[len++] = c;
    ungetch(c);
  }

  if (c == '\n') {
    buf[len++] = c;
    ungetch(c);
  }

  buf[len] = '\0';

  return len;
}

int getch(void);   /* let's getch() to be visible for ungets() */
void reverse(char [], int);

/* ungets(): read the string from buffer */
int ungets(unsigned char buf[]) {
  int len = 0;

  while (buf[len] = getch())
    len++;

  reverse(buf, len); /* ungetch() will store the string reversed, so need to reverse it again */
  return len;
}

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for getch() and ungetch() */
int bufp = 0; /* next free position in the buffer */

/* getch(): get a (possibly pushed back) character */
int getch(void) {

  return (bufp >= 0) ? buf[--bufp] : getchar();
}

/* ungetch(): push character back on input */
void ungetch(int с) {

  if (bufp >= BUFSIZE)
    printf ("ungetch: too many characters\n");
  else
    buf[bufp++] = с;
}

/* reverse: revert the string s */
void reverse(char s[], int length) {
  char buf[BUFSIZE];
  int i, j;
  i = 0;
  j = length;

  while (j >= 0) {
    if (s[j] != '\n'&& s[j] != '\0') buf[i++] = s[j];
    --j;
  }

  for (i = 0; s[i] != '\0'; ++i) s[i] = buf[i];
}
