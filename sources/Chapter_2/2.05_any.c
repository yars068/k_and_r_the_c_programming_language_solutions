#include <stdio.h>
#include <ctype.h>
#define FALSE -1
#define BUFSIZE 1024

/* Lesson 2.5. Write function any(s1, s2) that returns the 
   first position number of s1 matched to any of character in s2,
   or -1 if no match */

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

int any(unsigned char s1[], unsigned char s2[]) {
  int i, j;
  int ret = FALSE;

  for (i = 0; s1[i] != '\0' && s1[i] != '\n' && ret == FALSE; ++i)
    for (j = 0; s2[j] != '\0' && s2[j] != '\n' && ret == FALSE; ++j)
      if (s1[i] == s2[j]) ret = i;
      else ret = FALSE;

    return ret;
}

int main(void) {
  unsigned char s1[BUFSIZE] = {'\0'};
  unsigned char s2[BUFSIZE] = {'\0'};
  const char msg1[] = "Enter string: ";
  const char msg2[] = "Enter another string: ";
  int len1 = 0;
  int len2 = 0;
  int res = 0;
  
    len1 = get_line(s1, BUFSIZE, msg1);
    len2 = get_line(s2, BUFSIZE, msg2);
    res = any(s1, s2);
    if (res != FALSE) /* Printing using string length, -1 is used to supress a trailing '\n'*/
                      /*, remember that C string is in 'hello\n\0' format. */
      printf("Characters in \'%.2s\' enters \'%.4s\' at position %d\n", (len2 - 1), s2, (len1 - 1), s1, res);
    else printf("Nothing of string \'%.*s\' enters \'%.*s\'\n.", (len2 - 1), s2, (len1 - 1), s1);

  return 0;
}