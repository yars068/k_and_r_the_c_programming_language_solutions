#include <stdio.h>
#define LOWER 0
#define UPPER 300
#define STEP 10

float f2c(float fahr) {
  float celsius;
  celsius = (5.0/9.0) * (fahr - 32.0);
  return celsius;
}

int main() {
  int i;
  printf("Температура:\nПо Фаренгейту\tПо Цельсию\n");
  for (i = LOWER; i <= UPPER; i = i + STEP)
    printf("%13d\t%10.2f\n", i, f2c(i));
}
