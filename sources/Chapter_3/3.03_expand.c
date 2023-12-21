#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 1024U
#define TRUE 1
#define FALSE 0

/* Lesson 3.3. Write function expand(s1, s2) that expands shorthand /*
/* notations like a-z in the string s1 into equivalent complete */
/* list abc...xyz in s2. Allow for letters of either case and digits, */
/* and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. */
/* Arrange that a leading or trailing - taken literally. */

int make_expand(unsigned char buf[], unsigned pos, unsigned lim, unsigned char start, unsigned char end) {
  unsigned i = 0;
  for (i = start; pos < (lim - 1) && i <= end; ++i) buf[pos++] = i;

  return pos;
}

int expand(unsigned char buf[], unsigned char res[]) {
  const unsigned char dash = '-';
  const unsigned char term = '\0';
  const unsigned char nl = '\n';
  unsigned i, expanded = FALSE;
  unsigned len = 0;

  for (i = 0; res[i] != term && i < BUFSIZE; ++i) res[i] = '\0'; /* reset buffer */

  for (i = 0; buf[i] != nl; i++) {
    if (i == 0 && buf[i] == dash) {
      res[len++] = buf[i];
    }
    else if (i > 0 && buf[i] == dash && isupper(buf[i - 1]) && isupper(buf[i + 1])) {
      len = make_expand(res, len - 1, BUFSIZE, buf[i - 1], buf[i + 1]);
      expanded = TRUE;
    }
    else if (i > 0 && buf[i] == dash && islower(buf[i - 1]) && islower(buf[i + 1])) {
      len = make_expand(res, len - 1, BUFSIZE, buf[i - 1], buf[i + 1]);
      expanded = TRUE;
    }
    else if (i > 0 && buf[i] == dash && isdigit(buf[i - 1]) && isdigit(buf[i + 1])) {
      len = make_expand(res, len - 1, BUFSIZE, buf[i - 1], buf[i + 1]);
      expanded = TRUE;
    }
    else {
      if (!expanded) res[len++] = buf[i];
      expanded = FALSE;
    }
  }
  return len;
}

int get_line(char buf[], int lim, const char msg[]) {
  int i = 0;
  char c = '\0';

  printf("%s ", msg);
  while (i < lim - 1 && ((c = getchar()) != EOF) && c != '\n')
    buf[i++] = c;

  if (c == '\n') buf[i++] = '\n';

  buf[i] = '\0';
  return i;
}

int main(void) {
  const char msg[] = "Type something:";
  unsigned char buf[BUFSIZE] = {'\0'};
  unsigned char res[BUFSIZE] = {'\0'};
  int len, i;

  while ((len = get_line(buf, BUFSIZE, msg)) != 0) {
    if (expand(buf, res))
      printf("expanded string: \'%s\'\n", res);
  }
  return 0;
}
