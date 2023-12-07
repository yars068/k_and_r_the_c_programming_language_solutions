#include <stdio.h>
#define BUFSIZE 1024
#define MESSAGE "Input number: "

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
  int ret = -1;
  
  for (i = len; i >= 0; --i) {
    if (buf[i] >= '0' && buf[i] <= '9') {
      res += (buf[i] - '0') * mul;
      mul *= 10;
      ret = 0;
    }
  }
  if (ret == -1) return ret;
  else return res;
}

int main(void) {
  char buf[BUFSIZE] = {'\0'};
  int len, num;

  while ((len = get_line(buf, BUFSIZE, MESSAGE)) > 0) {
    if ((num = chartodig(buf, len)) >= 0)
      printf("Now you have a number %d.\n", num);
    else
      printf("Something went wrong, retype\n");
  }
}
