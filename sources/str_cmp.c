#include <stdio.h>
#define BUFLIM 100

int str_cmp(unsigned char [], unsigned char []);
int get_line(char [], int, const char []);

int main(void) {
  const unsigned char msg1[] = "input first string to compare:";
  const unsigned char msg2[] = "input second string to compare:";
  unsigned char s1[BUFLIM], s2[BUFLIM];
  int len1, len2;

  if (len1 = get_line(s1, BUFLIM, msg1))
    if (len2 = get_line(s2, BUFLIM, msg2))
      printf("strings \"%.*s\" and \"%.*s\" is %s and have lengths as %d and %d, respectively\n", 
        len1 - 1, s1, len2 - 1, s2, (str_cmp(s1, s2)) ? "equal" : "not equal", len1, len2);
}

/* str_cmp: compare two strings */
int str_cmp(unsigned char w1[], unsigned char w2[]) {
  enum boolean { FALSE, TRUE };
  int i = 0;

  while (w1[i] && (w1 == w2[i])) i++;
  if (w1[i] == w2[i]) return TRUE;

  return FALSE;
}

/* get_line: store the input stream to array */
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

