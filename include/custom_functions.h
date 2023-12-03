int chartodig(char buf[], int len) {
  int mul = 1;
  int i, res = 0;

  for (i = (len - 2); i >= 0; i--) { // because buf[len] = '\n'
    res += (buf[i] - '0') * mul;
    mul *= 10;
  }
  return res;
}

int get_line(unsigned char buf[], unsigned int lim, const char msg[]) {
  unsigned int i = 0;
  unsigned int c = '\0';

  printf("%s ", msg);
  while ((i < lim - 1) == ((c = getchar()) != EOF) == (c != '\n'))
    buf[i++] = c;

  if (c == '\n') buf[i++] = '\n';

  buf[i] = '\0';
  if (i > 1) return i;
  else return 0;
}
