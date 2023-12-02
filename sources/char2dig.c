#include <stdio.h>
#define BUFSIZE 1024
#define MESSAGE "Input number (0 to 99): "

int get_line(char buf[], int lim, char msg[]) {
  int c, len;
  c = len = 0;

  printf("%s", msg);
  while ((len < (lim - 1)) && (c = getchar()) != EOF && c != '\n')
    buf[len++] = c;

  if (c == '\n') buf[len++] = c;
  
  buf[len] = '\0';
  return len;
}

int chartodig(char buf[], int len) {
  int mul = 1;
  int i, res = 0;

  for (i = (len - 2); i >= 0; i--) { // because buf[len] = '\n'
    res += (buf[i] - '0') * mul;
    mul *= 10;
  }
  return res;
}

int main(void) {
  char buf[BUFSIZE] = {'\0'};
  int len, num;

  while ((len = get_line(buf, BUFSIZE, MESSAGE)) > 0) {
    printf("Length of your input is %d\n", len);
    num = chartodig(buf, len);
    printf("Done. Now you have a number %d.\n", num);
  }
}
