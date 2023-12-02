#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define WIDTH 8

int main(int argc, char** argv) {
  int i, j;

  if (argc > 1)
    if (strcmp(argv[1], "-n") != 0) {
    printf("charmap: unknown option \'%s\'\n", argv[1]);
    printf("Usage: charmap [-n]\n");
    printf("-n   Print ASCII codes and characters.\n");
    printf("When charmap invoked without -n, only characters will be printed.\n");
    return EINVAL;
  } 
  for (i = 32; i <= 126; i++) {
    if ((i % WIDTH) == 0)
      putchar('\n');

      if ((argc > 1) && (strcmp(argv[1], "-n") == 0)) printf("%4d %c" ,i, i);
      else printf("%4c %c" , ' ', i);
  }
  putchar('\n');
  return EXIT_SUCCESS;
}
