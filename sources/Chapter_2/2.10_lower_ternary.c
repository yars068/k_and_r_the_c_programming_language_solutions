#include <stdio.h>

/* Lesson 2.10. Write function lower(char s) which makes a UPPERCASE letter */
/* to be lowercase using ternary operator */

char lower(char s) {
  return (s >= 'A' && s <= 'Z') ? ((s - 'A') + 'a') : (s >= 'a' && s <= 'z') ? s : '\0';
}

int main(void) {
  char w[] = "aBcDeF";
  int i = 0;

  printf("Source: %s, transformed: ", w);
  for (i = 0; w[i] != '\0'; i++) {
    printf("%c", lower(w[i]));
  }
  putchar('\n');
  return 0;
}
