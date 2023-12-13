#include <stdio.h>

/* Lesson 2.6. Write a function setbits(x, p, n, y) that returns x 
   with the n bits that begin at position p set to rightmost n 
   bits of y, leaving other bits unchanged. */

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    // xxxxx00000xxxxx
    unsigned a = x & ~(~(~0U << n) << (p + 1 - n));

    // 00000yyyyy00000
    unsigned b = (y & ~(~0U << n)) << (p + 1 - n);

    // xxxxxyyyyyxxxxx
    return a | b;
}

int main(void) {
    printf("%u\n", setbits(0xFF, 4, 3, 0x7F));
    return 0;
}
