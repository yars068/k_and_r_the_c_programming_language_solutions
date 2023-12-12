#include <stdio.h>
#include <limits.h>
#include <float.h>

/* Show limits from included headers */
/* Just read the source itself, no code here */

int main(void) {
  printf("Size of type char:\n");
  printf("Bit depth: %d\n", CHAR_BIT);
  printf("Maximal values: %d, %d\n", SCHAR_MAX, SCHAR_MIN);
  printf("Maximal value, if unsigned: %d\n", UCHAR_MAX);
  printf("Minimal value, if unsigned: %d\n", SCHAR_MIN);
  return 0;
}
