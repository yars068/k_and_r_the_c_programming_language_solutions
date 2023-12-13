#include <stdio.h>
#include <stdint.h>

int main(void) {
  uint16_t x = 0x0001;
  printf("%s-endian\n", *((uint8_t *) &x) ? "little" : "big");

  return 0;
}
