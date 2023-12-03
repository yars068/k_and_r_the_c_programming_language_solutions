#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "../include/custom_functions.h"
/* Lesson 2.4. Remove all characters from string s1 that appears in string s2 */

#define BUFSIZE 1024

int main(void) {
  unsigned char str_one[BUFSIZE] = {'\0'};
  unsigned char str_two[BUFSIZE] = {'\0'};
  short int i, j, k, len_one, len_two;
  const char message_one[] = "Enter first string: ";
  const char message_two[] = "Enter second string: ";

  len_one = get_line(str_one, BUFSIZE, message_one);
  len_two = get_line(str_two, BUFSIZE, message_two);
  for (i = 0; str_one[i] != '\0'; ++i) {
    for (j = 0; str_two[j] != '\0'; ++j) {
      if (str_one[i] == str_two[j]) {
        for (k = 0; str_one[i + k] != '\0'; ++k)
          str_one[i + k] = str_one[i + k + 1];
      }
    }
  }
  printf("Result: %s\n", str_one);
  return EXIT_SUCCESS;
}
