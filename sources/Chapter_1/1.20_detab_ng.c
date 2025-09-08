#include <stdio.h>
#define TABSIZE 8
#define BUFSIZE 1024

/* Lesson 1.20. Write a program 'detab' that replaces tabs in the */
/* input with the proper nuber of blanks to space to the next tab stop */
/* Assume a fixed set of tab stops, say every n columns. Should n be a */
/* variable, or symbolic parameter? */

int get_line(char buf[], int lim);
int detab(char buf[], int tabsize);

int main(void) {
  char buf[BUFSIZE];
  int len = 1;

  while (len > 0) {
    int new_len = 0;
    printf("Enter text with a tabs:\n");
    if ((len = get_line(buf, BUFSIZE)) > 0)
      new_len = detab(buf, TABSIZE);

    printf("result: Before replacing length was %d, replaced text is:\n\"%s\"\nNew length is %d\n", len, buf, new_len);
  }
}


/* detab: replace a tabulations with the proper number of spacebars */
int detab(char buf[], int tabsize) {
  char tmp[BUFSIZE] = { '\0' };
  int i = 0;
  int b_pos = 0;
  int t_pos = 0;

  /* Copy the buffer into local buffer and then clear */
  /* to be ready for the result */
  while (buf[i] != '\0') {
    tmp[i] = buf[i];
    buf[i++] = '\0';
  }

#define SPACE ' '
  /* Now, we work on tmp's contents */
  while (tmp[t_pos] != '\0') {
    if (tmp[t_pos] != '\t')
      buf[b_pos++] = tmp[t_pos++];
    else {
      int space_count = 0;
      for (space_count = tabsize - t_pos % tabsize; space_count > 0; space_count--)
        buf[b_pos++] = SPACE;

      t_pos++;
    }
  }
  buf[b_pos] = '\0';
  return b_pos;
}

int get_line(char buf[], int lim) {
  int c, i;

  i = 0;
  while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
    buf[i++] = c;

  if (c == '\n') buf[i++] = c;

  buf[i] = '\0';
  return i;
}
