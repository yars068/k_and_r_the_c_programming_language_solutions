#include <stdio.h>
#define MAXCOUNT 1000
#define OUTW 0
#define INW 1
#define DELIMITER "  "

/* Write a program that makes a word length histo */

int main() {
  int wordlen[MAXCOUNT];
  int c, i, j, wc, m, state;
  for (i = 0; i < MAXCOUNT; ++i) wordlen[i] = 0;
  c = i = j = wc = m = 0;

  state = OUTW;
  while ((c = getchar()) != EOF && wc < MAXCOUNT - 1 ) {
    if (c == ' ' || c == '\t' || c == '\n') {
      state = OUTW;
      ++wordlen[wc];
      ++wc;
    }
    else if (state == OUTW)
      state = INW;
    else ++wordlen[wc];
  }

  printf("Building histograms. First, horizontal:\n");
  for (i = 0; i < wc; ++i) {
    printf("word %d: ", i);
    for (j = 0; j < wordlen[i]; ++j) putchar('+');
    putchar('\n');
  }

  printf("Then, vertical:\n");
  /* what's the longest word? */
  m = 0;
  for (i = 0; i < wc; ++i)
    if (wordlen[i] > m) m = wordlen[i];

  for (i = 0; i < m; ++i) {
    for (j = 0; j < wc; ++j) {
      if (wordlen[j] >= m) putchar('+');
      else putchar(' ');
      printf(DELIMITER);
    }
    putchar('\n');
    --m;
  }
  /* the legend under histogram */
  for (i = 0; i < wc; ++i)
    printf("%d%s", i, DELIMITER);
  putchar('\n');
}
