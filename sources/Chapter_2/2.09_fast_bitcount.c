# include <stdio.h>

/* lesson 2.9 */
/* bitcount: count bits that set in '1' in an integer х */

int bitcount_old(unsigned char x) {
  int b;

  for (b = 0; x != 0; x >>= 1) {
    if (x & 1) b++;
  }
  return b;
}

int bitcount(unsigned char x) {
  int b = 0;

  while (x != 0) {
    x &= (x - 1);
    b++;
  }
  return b;
}

int main(void) {
  unsigned char x = 55;

  printf("oldfunc: Count of bits that set in number %d is %d\n", x, bitcount_old(x));
  printf("Count of bits that set in number %d is %d\n", x, bitcount(x));

  return 0;
}