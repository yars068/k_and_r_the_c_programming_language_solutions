int chartodig(char buf[], int len) {
  int mul = 1;
  int i, res = 0;

  for (i = (len - 2); i >= 0; i--) { // because buf[len] = '\n'
    res += (buf[i] - '0') * mul;
    mul *= 10;
  }
  return res;
}
