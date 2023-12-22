#include <stdio.h>
#include <limits.h>
#define BUFSIZE 25
#define YES 1
#define NO  0

/* Lesson 3.4. Explain why this function cannot handle the greatest negative */
/* number? The answer: when comparing n < 0 to determine the sign, becomes a type owerflow. */

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

/* original version of itoa: transform a number to its character representation */
void itoa_original (int n, char s[]) {
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
  reverse(s, i);
}

/* itoa: transform an integer to character form and prints it to a field with minimal width */
/* when the number is shorter than the field, append it with proper number of spaces and align */
/* to the right edge */
void itoa (int n, char s[], int width) {
  int sign = NO;
  int is_max = NO;
  int len;

  for (len = 0; s[len] != '\0'; ++len) s[len] = '\0'; /* reset buffer */

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
  len = 0;
  do {
    if (len == 0 && sign && is_max) s[len++] = 1 + (n % 10) + '0';
    else s[len++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign) s[len++] = '-';
  while (len < width && len < (width - len)) s[len++] = ' ';

  s[len] = '\0';
  reverse(s, len);
}

int main(void) {
  char buf[BUFSIZE] = {'\0'};
  int len = 0;
  int number = INT_MAX;
  printf("Number is: %d\n", number);
  itoa(number, buf, BUFSIZE);
  printf("Now how itoa() works: \"%s\"\n", buf);

}
