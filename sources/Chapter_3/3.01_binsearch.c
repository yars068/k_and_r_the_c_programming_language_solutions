#include <stdio.h>

/* Lesson 3.1. Write program that realize the binary search algorithm */
/* using only one check in the cycle loop. */

/* binsearch: find х in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch_old(int x, int v[], int n) {
  int low, high, mid;
  low = 0;
  high = n - 1 ;

  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1 ;
    else /* match found */
      return mid;
  }

  return -1; /* no match */
}

int main(void) {
  const int num = 10;
  int array[num];
  int i, res;
  int x = 12;
  
  for (i = 0; i < num; i++) array[i] = i + 1;
  for (i = 0; i < num; i++) printf("array[%d] = %d\n", i, array[i]);
  printf("Search result for number %d: ", x);
  (res = binsearch_old(x, array, num)) != -1 ? printf("%d\n", res) : printf("Nothing\n");
  return 0;
}
