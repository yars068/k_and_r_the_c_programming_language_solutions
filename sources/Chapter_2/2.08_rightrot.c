#include <stdio.h>

/* Lesson 2.8 */

unsigned rightrot(unsigned x, int n) {

  while (n-- > 0) {
    if (x & 1)
      x = (x >> 1) | ~(~0U >> 1);
    else
      x = x >> 1;
  }
  return x;
}

int main(void)
{
    printf("%u\n", rightrot(100, 1));
    return 0;
}
