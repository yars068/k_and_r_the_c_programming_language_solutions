#include <stdio.h>
#include <stdbool.h>
#define MAXARGS 100

/* sequence.c: find and then print a sequence of integer numbers */
/* this version cannot handle a multiple sequences */

int find_seq(int [], int []);
int is_seq(int, int);

int main(void) {
  int nums[MAXARGS] = { 1, 100, 3, 73, 2, 4, 42 };
  int seq[MAXARGS] = { 0 };
  int length = 0;

  printf("Input: ");
  for (int i = 0; *(nums + i); i++) printf("%d, ", *(nums + i));
  putchar('\n');

  /* sorting */
  for (int i = 0; nums[i]; i++)
    for (int j = 0; nums[j]; j++)
      if (nums[i] < nums[j]) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
      }

  printf("Sorted input: ");
  for (int i = 0; *(nums + i); i++) printf("%d, ", *(nums + i));
  putchar('\n');

  length = find_seq(nums, seq);

  printf("Sequence: ");
  for (int i = 0; i < length; i++) printf("%d,", seq[i]);
  printf("\nLength of sequence: %d\n", length);

  return 0;
}

/* is_seq: check if two numbers is a sequence */
int is_seq(int m, int n) {
return (n == (m + 1)) ? true : false;
}

#define NEXT 1
/* find_seq: search for a sequence in the array of integers */
/* store the result into another array and returns its length */
int find_seq(int nums[], int seq[]) {
  int i, length = 0;
  for (i = 0, length = NEXT; is_seq(nums[i], nums[length]); i++) {
    if (length <= MAXARGS) {
      for (int k = 0 ; k <= length; k++) seq[k] = nums[k];
      length++;
    }
  }
  return length;
}
