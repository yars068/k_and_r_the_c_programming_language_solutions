#include <stdio.h>
#define BUFSIZE 10

int atoi(char [], int);
int fact(int n);
int get_line(char [], int, const char []);

int main(void) {
  int len;
  int n;
  const int lim = 10;
  char buf[lim];
  const char msg[] = "Enter a number: ";

  while ((len = get_line(buf, 10, msg)) > 0) {
    if ((n = atoi(buf, len)) > 0) {
      printf("Calculating factorial of number %d\n", n);
      printf("Factorial of %d is %d\n", n, fact(n));
    }
}
  return 0;
}

/* atoi: transform a character representation of integer number to number itself */
int atoi(char buf[], int len) {
  int mul = 1;
  int i, res = 0;

  for (i = len; i >= 0; --i) {
    if (buf[i] >= '0' && buf[i] <= '9') {
      res += (buf[i] - '0') * mul;
      mul *= 10;
    }
  }
  return res;
}

/* fact: calculate factorial */
int fact(int n) {
  int ret = 1;

    if (n == 0) ret = 1;
    else ret = n * (fact(n - 1));

  return ret;
}

/* get_line: read string from the input */
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
