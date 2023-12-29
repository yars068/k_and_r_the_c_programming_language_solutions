#include <stdio.h>

/* Write a program that removes the comments from the C program */

#define BUFSIZE 1000
#define FALSE -1

/* Map assignments: */
#define OTHER 0
#define SINGLE_QUOTE 1
#define DOUBLE_QUOTE 2
#define SLASH 3
#define ASTERISK 4
#define SINGLE_STRING_COMMENT 5
#define MULTI_STRING_COMMENT_BEGIN 6
#define MULTI_STRING_COMMENT_END 7

int get_line(char buf[], int lim) {
  int c, len;
  c = len = 0;

//  printf("Type something:\n");
  while ((len < (lim - 1)) && (c = getchar()) != EOF && c != '\n')
    buf[len++] = c;

  if (c == '\n') buf[len++] = c;
  
  buf[len] = '\0';
  return len;
}

int main(void) {
  char buf[BUFSIZE] = {'\0'};
  char res[BUFSIZE] = {'\0'};
  int map[BUFSIZE] = {FALSE};
  int i, j, len, state;

  while ((len = get_line(buf, BUFSIZE)) > 0) {
    for (i = 0; i < BUFSIZE; ++i) res[i] = 0;
    
    state = FALSE;
    
    for (i = 0; (i < len && buf[i] != '\0'); ++i) {
      if (state == SLASH && buf[i] == '*')
         map[i] = MULTI_STRING_COMMENT_BEGIN;

      else if (state == ASTERISK && buf[i] == '/')
        map[i] = MULTI_STRING_COMMENT_END;

      else if (state == SLASH && buf[i] == '/')
        map[i] = SINGLE_STRING_COMMENT;

      else if (buf[i] == '\'')
        map[i] = SINGLE_QUOTE;

      else if (buf[i] == '\"')
        map[i] = DOUBLE_QUOTE;

      else if (buf[i] == '*')
        map[i] = ASTERISK;

      else if (buf[i] == '/')
        map[i] = SLASH;

      else map[i] = OTHER;
      state = map[i];
    }

    i = j = 0;
    state = FALSE;
    while (i < len) {
      if (state != MULTI_STRING_COMMENT_BEGIN && state != SINGLE_STRING_COMMENT && map[i] == SINGLE_QUOTE) {
        res[j++] = buf[i];
        state = SINGLE_QUOTE;
      }
      else if (state != MULTI_STRING_COMMENT_BEGIN && state != SINGLE_STRING_COMMENT && map[i] == DOUBLE_QUOTE) {
        state = DOUBLE_QUOTE;
        res[j++] = buf[i];
      }
      else if (state != SINGLE_QUOTE && state != DOUBLE_QUOTE && map[i] == SLASH && map[i + 1] == MULTI_STRING_COMMENT_BEGIN) {
        state = MULTI_STRING_COMMENT_BEGIN;
        i+=2;
      }
      else if (state == MULTI_STRING_COMMENT_BEGIN && map[i] == ASTERISK && map[i + 1] == MULTI_STRING_COMMENT_END) {
        state = MULTI_STRING_COMMENT_END;
        i+=2;
        res[j++] = buf[i];
      }
      else if (map[i] == SLASH && map[i + 1] == SINGLE_STRING_COMMENT) {
        state == SINGLE_STRING_COMMENT;
        break; //drop the rest of line
      }
      else if (map[i] == SLASH && map[i + 1] != MULTI_STRING_COMMENT_BEGIN && map[i + 1] != SINGLE_STRING_COMMENT) {
        state = SLASH;
        res[j++] = buf[i];
      }
      else if (map[i] == ASTERISK && map[i + 1] != MULTI_STRING_COMMENT_END) {
        state = ASTERISK;
        //++i;
        res[j++] = buf[i];
      }
      else if (state != MULTI_STRING_COMMENT_BEGIN && state != SINGLE_STRING_COMMENT && (map[i] == OTHER || map[i] == ASTERISK)) {
        state = OTHER;
        res[j++] = buf[i];
      }

      ++i;
    }
    /* Print the result: */
    if (j > 1) printf("%s", res);
  }
  
  return 0;
}
