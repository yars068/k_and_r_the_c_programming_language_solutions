#include <stdio.h>
#define MAXLEN 100

/* Lesson 4.9. Our functions does not handle EOF correctly. Modify them, to do that. */

int getch(void);
void ungetch(char);

unsigned char line[MAXLEN]; /* will push here */

int main(void) {
  char c, g;
  unsigned len = 0;
  unsigned lim = MAXLEN;

  printf("Enter a string: ");
  while (lim-- && (c = getchar()) != EOF && c != '\n') {
    ungetch(c); /* call to ungetch() guarantees that getch() will always return */
    if ((g = getch()) != EOF) line[len++] = g; /* the contents of its buffer */
  }
  if (c == '\n') {
    ungetch(c);
    if ((g = getch()) != EOF) line[len++] = g;
  }
  ungetch('\0');
  if ((g = getch()) != EOF) line[len] = g;

  printf("Your input is:\n\"%.*s\"\n", len - 1, line);
}

char buf = EOF; /* one-character-sized buffer for getch() and ungetch() */

/* getch(): get a (possibly pushed back) character */
int getch(void) {
  int c;
  return (buf != EOF) ? buf : ((c = getchar()) != EOF) ?  c : EOF;
}

/* ungetch(): push character back on input */
void ungetch(char с) {

    buf = с;
}
