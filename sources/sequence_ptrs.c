#include <stdio.h>
#include <stdbool.h>
#define MAXARGS 100

/* sequence.c: find and then print a sequence of integer numbers */

int find_seq(int *, int *);
int is_seq(int, int);
void clear_int(int *, int);

int main(void) {
  int nums[MAXARGS] = { 1, 100, 3, 73, 2, 4, 42, 5, 10, 11, 12 };
  int seq[MAXARGS] = { 0 };
  int *np = nums;
  int len = 0;

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

  while (*np++ && (len = find_seq(np += len - 1, seq)) > 1) {
    int i = 0;
    printf("\nFound sequence, len is %d, that is: ", len);
    while (seq[i]) printf("%d,", seq[i++]);
    clear_int(seq, len);
    i++;
  }
  putchar('\n');
  return 0;
}

/* is_seq: check if two numbers is a sequence */
int is_seq(int m, int n) {
return (n == (m + 1)) ? true : false;
}

void clear_int(int *var, int sz) {
  int i = 0;
  while (i < sz) *(var + i++) = 0;
}

#define NEXT 1
/* find_seq: search for a sequence in the array of integers */
/* store the result into another array and returns its length */
int find_seq(int nums[], int seq[]) {

  int i, length = 0;
  for (i = 0, length = NEXT; is_seq(nums[i], nums[length]); i++) {
    if (length <= MAXARGS) {
      for (int k = i ; k <= length; k++) seq[k] = nums[k];
      length++;
    }
  }
  return length;
}
