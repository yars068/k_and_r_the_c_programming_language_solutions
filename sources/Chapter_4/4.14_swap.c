#include <stdio.h>

/* Lesson 4.14. Define the macro swap(t, x, y),  that interchanges two arguments */
/* of type t */

#define swap(t, x, y) {t temp = x; x = y; y = temp;}

int main(void) {
  int ia = 10;
  int ib = 20;
  char ca = 'a';
  char cb = 'b';

  printf("Values with type int: a = %d, b = %d\n", ia, ib);
  swap(int, ia, ib);
  printf("Do a swap: a = %d, b = %d\n", ia, ib);
  printf("Values with type char: ca = \'%c\', cb = \'%c\'\n", ca, cb);
  swap(char, ca, cb);
  printf("Now do a swap: ca = \'%c\', cb = \'%c\'\n", ca, cb);

}
