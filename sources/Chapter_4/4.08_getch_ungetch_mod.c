#include <stdio.h>
#define MAXLEN 100

/* Lesson 4.8. Suppose that there will newer be more than one character pushed back. */
/* Modify getch() and ungetch() accordingly. */

int getch(void);
void ungetch(int);

unsigned char line[MAXLEN]; /* will push here */

int main(void) {
  char c;
  unsigned len = 0;
  unsigned lim = MAXLEN;

  printf("Enter a string: ");
  while (lim-- && (c = getchar()) != EOF && c != '\n') {
    ungetch(c); /* call to ungetch() guarantees that getch() will always return */
    line[len++] = getch(); /* the contents of its buffer */
  }
  if (c == '\n') {
    ungetch(c);
    line[len++] = getch();
  }
  ungetch('\0');
  line[len] = getch();

  printf("Your input is:\n\"%.*s\"\n", len - 1, line);
}

char buf = EOF; /* one-character-sized buffer for getch() and ungetch() */

/* getch(): get a (possibly pushed back) character */
int getch(void) {

  return (buf != EOF) ? buf : getchar();
}

/* ungetch(): push character back on input */
void ungetch(int с) {

    buf = с;
}
