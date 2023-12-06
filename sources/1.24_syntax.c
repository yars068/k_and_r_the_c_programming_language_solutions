#include <stdio.h>

/* Write a program to check C program for the syntax errors like */
/* unpaired brackets, quotes, broken escape sequences and comments 
/* and so on. */

#define BUFSIZE      1024
#define FIELDWIDTH     16
#define FALSE          -1
#define PREPROC_COUNT  13
#define KEYWORDS_COUNT 43
#define KEYWORD_MAXLEN 14

/* Map definitions for non-keywords and other lexems */

#define OTHER                      8
#define LVAL                       1
#define SINGLE_STRING_COMMENT      2
#define MULTI_STRING_COMMENT_BEGIN 3
#define MULTI_STRING_COMMENT_END   4
#define DELIMITER                  5
#define PREPROCESSOR               6
#define KEYWORD                    7

int get_line(char buf[], int lim, char msg[]) {
  int c, len;
  c = len = 0;

  printf("%s", msg);
  while ((len < (lim - 1)) && (c = getchar()) != EOF && c != '\n')
    buf[len++] = c;

  if (c == '\n') buf[len++] = c;
  
  buf[len] = '\0';
  return len;
}

int get_keyword(char buf[], char res[], int number, int field_width) {
  int i = 0;
  int len = 0;
  int ret = FALSE;
  int first_item = (number * field_width) + 1;
  
  len = buf[number * field_width];
  if (len > 0) {
    while ((buf[first_item] != 0) && (i < len)) {
      res[i] = buf[first_item + i];
      ++i;
    }
    ret = len;
  }
  else ret = FALSE;
  return ret;
}

int main(void) {
  int i, j, k, len;
  int kw_len = FALSE;
  int word_len = 0;
  char word[BUFSIZE] = {'\0'};
  char keyword[BUFSIZE] = {'\0'};
  char buf[BUFSIZE] = {'\0'};
  int map[BUFSIZE] = {FALSE};
  char keywords[] = { 6, 's', 'i', 'z', 'e', 'o', 'f', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      7, 't', 'y', 'p', 'e', 'd', 'e', 'f', '0', '0', '0', '0', '0', '0', '0', '0', 
                      4, 'a', 'u', 't', 'o', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      8, 'r', 'e', 'g', 'i', 's', 't', 'e', 'r', '0', '0', '0', '0', '0', '0', '0', 
                      6, 'e', 'x', 't', 'e', 'r', 'n', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      6, 's', 't', 'a', 't', 'i', 'c', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      4, 'v', 'o', 'i', 'd', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      4, 'c', 'h', 'a', 'r', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      5, 's', 'h', 'o', 'r', 't', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      3, 'i', 'n', 't', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      4, 'l', 'o', 'n', 'g', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      6, 's', 'i', 'g', 'n', 'e', 'd', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      8, 'u', 'n', 's', 'i', 'g', 'n', 'e', 'd', '0', '0', '0', '0', '0', '0', '0', 
                      5, 'f', 'l', 'o', 'a', 't', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      6, 'd', 'o', 'u', 'b', 'l', 'e', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      5, 'c', 'o', 'n', 's', 't', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      8, 'v', 'o', 'l', 'a', 't', 'i', 'l', 'e', '0', '0', '0', '0', '0', '0', '0', 
                      6, 's', 't', 'r', 'u', 'c', 't', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      4, 'e', 'n', 'u', 'm', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      5, 'u', 'n', 'i', 'o', 'n', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      2, 'd', 'o', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      3, 'f', 'o', 'r', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      5, 'w', 'h', 'i', 'l', 'e', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      2, 'i', 'f', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      4, 'e', 'l', 's', 'e', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      6, 's', 'w', 'i', 't', 'c', 'h', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      4, 'c', 'a', 's', 'e', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      7, 'd', 'e', 'f', 'a', 'u', 'l', 't', '0', '0', '0', '0', '0', '0', '0', '0', 
                      5, 'b', 'r', 'e', 'a', 'k', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      8, 'c', 'o', 'n', 't', 'i', 'n', 'u', 'e', '0', '0', '0', '0', '0', '0', '0', 
                      4, 'g', 'o', 't', 'o', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      6, 'r', 'e', 't', 'u', 'r', 'n', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      6, 'i', 'n', 'l', 'i', 'n', 'e', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      8, 'r', 'e', 's', 't', 'r', 'i', 'c', 't', '0', '0', '0', '0', '0', '0', '0', 
                      5, '_', 'B', 'o', 'o', 'l', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
                      8, '_', 'C', 'o', 'm', 'p', 'l', 'e', 'x', '0', '0', '0', '0', '0', '0', '0', 
                     10, '_', 'I', 'm', 'a', 'g', 'i', 'n', 'a', 'r', 'y', '0', '0', '0', '0', '0', 
                      7, '_', 'A', 't', 'o', 'm', 'i', 'c', '0', '0', '0', '0', '0', '0', '0', '0', 
                      8, '_', 'A', 'l', 'i', 'g', 'n', 'a', 's', '0', '0', '0', '0', '0', '0', '0', 
                      8, '_', 'A', 'l', 'i', 'g', 'n', 'o', 'f', '0', '0', '0', '0', '0', '0', '0', 
                      8, '_', 'G', 'e', 'n', 'e', 'r', 'i', 'c', '0', '0', '0', '0', '0', '0', '0', 
                      9, '_', 'N', 'o', 'r', 'e', 't', 'u', 'r', 'n', '0', '0', '0', '0', '0', '0', 
                     14, '_', 'S', 't', 'a', 't', 'i', 'c', '_', 'a', 's', 's', 'e', 'r', 't', '0', 
                     13, '_', 'T', 'h', 'r', 'e', 'a', 'd', '_', 'l', 'o', 'c', 'a', 'l', '0', '0'
                     };

/* Place them itself in a map. Possibly better is use named constants instead of this, because */
/* it would be more consistent. */
  char delimiters[] = {' ', ',', ';', '.', '+', '-', '*', '^', '&', '=', '~', '!', '/', '<', '>', '(',
                       ')', '{', '}', '[', ']', '|', '%', '?', '\'', '"', ':', '_', '\\', '#', '\0',
                      };

  char preproc[] = {  6, 'd', 'e', 'f', 'i', 'n', 'e', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                      5, 'u', 'n', 'd', 'e', 'f', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                      7, 'i', 'n', 'c', 'l', 'u', 'd', 'e', '0', '0', '0', '0', '0', '0', '0', '0',
                      2, 'i', 'f', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                      5, 'i', 'f', 'd', 'e', 'f', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                      6, 'i', 'f', 'n', 'd', 'e', 'f', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                      4, 'e', 'l', 's', 'e', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                      4, 'e', 'l', 'i', 'f', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                      5, 'e', 'n', 'd', 'i', 'f', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                      4, 'l', 'i', 'n', 'e', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                      5, 'e', 'r', 'r', 'o', 'r', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                      7, 'w', 'a', 'r', 'n', 'i', 'n', 'g', '0', '0', '0', '0', '0', '0', '0', '0',
                      6, 'p', 'r', 'a', 'g', 'm', 'a', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                   };

  while ((len = get_line(buf, BUFSIZE, "Enter the source code to check: ")) > 0) {
    /* Start with delimiters */
    for (i = 0; buf[i] != '\0'; ++i) {
      j = 0;
      while (delimiters[j] != buf[i] && delimiters[j] != '\0') j++;
      if (delimiters[j] == buf[i]) {
        map[i] = DELIMITER;
      }
      else map[i] = OTHER;
    }
    /* Then, prepocessor directives: */
    /* Preprocessor directive always starts with '#' at begin of string */
    if (buf[0] == '#') {
      for (i = 1; map[i] != DELIMITER; ++i) word[word_len++] = buf[i]; /* get a word */

      for (i = 0; i < KEYWORDS_COUNT && ((kw_len = get_keyword(preproc, keyword, i, FIELDWIDTH)) != FALSE); ++i) {
        for (j = 0; j < kw_len && word[j] == keyword[j]; j++) map[j + 1] = PREPROCESSOR;
        for (j = 0; j < kw_len; ++j) keyword[j] = '\0'; /* reset after when all done */
      }
    }

    printf("debug: you entered a string:\n%s", buf);
    printf("text mapped as follows:\n");
    for (i = 0; (map[i] > 0) && (map[i] != FALSE); i++) printf("%u", map[i]);
    putchar('\n');
  }
  return 0;
}
