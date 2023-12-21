#include <stdio.h>
#include <limits.h>
#define BUFSIZE 25
#define YES 1
#define NO  0

/* Lesson 3.4. Explain why this function cannot handle the greatest negative */
/* number? The answer: when comparing n < 0 to determine the sign, becomes a type owerflow. */

/* original version of itoa: transform a number to its character representation */
void itoa (int n, char s[]) {
  int i, sign;

  if ((sign = n) < 0)
    n = -n;

  i = 0;
  do
   s[i++] = n % 10 + '0';
  while ((n /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';

  s[i] = '\0';
  reverse(s);
}

/* reverse: replace the s with s reverted */
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

/* itoa: transform an integer to character form */
void itoa (int n, char s[]) {
  int i, sign = NO;
  int is_max = NO;

  for (i = 0; s[i] != '\0'; ++i) s[i] = '\0'; /* reset buffer */

  if (n > 0) sign = NO;
  else if (n + 1 == INT_MIN + 1) {
    sign = YES;
    n = -(n += 1);
    is_max = YES;
  }
  else {
    sign = YES;
    n = -n;
  }
  i = 0;
  do {
    if (i == 0 && sign && is_max) s[i++] = 1 + (n % 10) + '0';
    else s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  
  if (sign) s[i++] = '-';

  s[i] = '\0';
  reverse(s, i);
}

int main(void) {
  char buf[BUFSIZE] = {'\0'};
  int len = 0;
  int number = -365;
  printf("Number is: %d\n", number);
  itoa(number, buf);
  printf("Now how itoa() works: %s\n", buf);

}
