#include <stdio.h>
#define BUFSIZE 1024

int get_line(char buf[], int lim) {
  int c, len;
  c = len = 0;

//  printf("Type something:\n");
  while ((len < (lim - 1)) && (c = getchar()) != EOF && c != '\n')
    buf[len++] = c;

  if (c == '\n') buf[len++] = c;
  
  buf[len] = '\0';
  return len;
}

int main(void) {
  char buf[BUFSIZE] = {'\0'};
  int i, d, len;
  printf("{\n");
  while ((len = get_line(buf, BUFSIZE)) > 0) {
    printf("                     %3d, ", len);
    for (i = 0; i < len - 1; ++i)
      printf("\'%c\', ", buf[i]);
      
    if ((len - 1) <= 14) {
      for (d = (14 - (len -1)); d >= 0; --d)
        printf("\'0\', ");

      putchar('\n');
    }
  }
  putchar('}');
  putchar(';');
  putchar('\n');

  return 0;
}
