#include <stdio.h>
#define DEBUG fprintf(stderr,

/* Write a program to check C program for the syntax errors like */
/* unpaired brackets, quotes, broken escape sequences and comments 
/* and so on. */

#define BUFSIZE         1024
#define FIELD_16_BYTE     16
#define FIELD_6_BYTE       6
#define TRUE               1
#define FALSE              0

/* Map definitions: */

#define SIMPLE_COMMENT                  0x01
#define INLINE_COMMENT_BEGIN            0x02
#define INLINE_COMMENT_END              0x03
#define DELIMITER                       0x04
#define SPACE                           0x05   /*Spacebar, new-line or h-tab */
#define PREPROCESSOR                    0x06
#define KEYWORD                         0x07
#define UPPERCASE_LETTER                0x08
#define LOWERCASE_LETTER                0x09
#define DIGIT                           0x0A
#define ADDITION                        0x0B
#define SUBTRACTION                     0x0C
#define MULTIPLY                        0x0D
#define DIVISION                        0x0E
#define REMAINDER                       0x0F
#define DIVIDE_THEN_ASSIGN              0x10
#define MULTIPLY_THEN_ASSIGN            0x11
#define ADD_THEN_ASSIGN                 0x12
#define SUBTRACT_THEN_ASSIGN            0x13
#define REMAINDER_THEN_ASSIGN           0x14
#define MORE                            0x15
#define LESS                            0x16
#define MORE_OR_EQUAL                   0x17
#define LESS_OR_EQUAL                   0x18
#define IS_EQUAL                        0x19
#define NOT_EQUAL                       0x1A
#define INCREMENT                       0x1B
#define DECREMENT                       0x1C
#define BITWISE_AND                     0x1D
#define BITWISE_OR                      0x1E
#define BITWISE_XOR                     0x1F
#define BITWISE_SHIFT_LEFT              0x20
#define BITWISE_SHIFT_RIGHT             0x21
#define BITWISE_AND_THEN_ASSIGN         0x22
#define BITWISE_OR_THEN_ASSIGN          0x23
#define BITWISE_XOR_THEN_ASSIGN         0x24
#define BITWISE_SHIFT_LEFT_THEN_ASSIGN  0x25
#define BITWISE_SHIFT_RIGHT_THEN_ASSIGN 0x26
#define LOGICAL_AND                     0x27
#define LOGICAL_OR                      0x28
#define LOGICAL_XOR                     0x29
#define LOGICAL_NOT                     0x30
#define BITWISE_NOT                     0x31
#define ASSIGN                          0x32
#define COMMA                           0x33
#define ADDRESS                         0x34
#define UNARY_PLUS                      0x35
#define UNARY_MINUS                     0x36
#define POINTER_DEREFERENCE             0x37
#define OTHER                           0xFE

int ask_line(char buf[], int lim, char msg[]);
int get_line(char buf[], int lim);
int get_keyword(char buf[], char res[], int number, int field_width);
int get_word(char buf[], char res[], char map[], int start, int len);
int str_cmp(char w1[], char w2[]);
void set_map(char map[], int start, int end, int map_as);
void reset(char buf[]);

int main(void) {
  int state = FALSE;
  int i, j, kw_num, len;
  int start = 0;
  int kw_len = FALSE;
  int word_len = 0;
  int operator_type = FALSE;
  char map[BUFSIZE] = {FALSE};
  char word[FIELD_16_BYTE] = {'\0'};
  char keyword[FIELD_16_BYTE] = {'\0'};
  char buf[BUFSIZE] = {'\0'};

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
                     13, '_', 'T', 'h', 'r', 'e', 'a', 'd', '_', 'l', 'o', 'c', 'a', 'l', '0', '0',
                      0, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'
                     };

  char delimiters[] = {',', ';', '.', '+', '-', '*', '^', '&', '=', '~', '!', '/', '<', '>', '(',
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
                      0, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'
                   };

  char operators[] = { 1, '+', '0', '0', '0', ADDITION,
                       1, '+', '0', '0', '0', UNARY_PLUS,
                       1, '-', '0', '0', '0', SUBTRACTION,
                       1, '-', '0', '0', '0', UNARY_MINUS,
                       1, '*', '0', '0', '0', MULTIPLY,
                       1, '*', '0', '0', '0', POINTER_DEREFERENCE,
                       1, '/', '0', '0', '0', DIVISION,
                       1, '%', '0', '0', '0', REMAINDER,
                       1, '>', '0', '0', '0', MORE,
                       1, '<', '0', '0', '0', LESS,
                       1, '=', '0', '0', '0', ASSIGN,
                       1, '&', '0', '0', '0', BITWISE_AND,
                       1, '&', '0', '0', '0', ADDRESS,
                       1, '|', '0', '0', '0', BITWISE_OR,
                       1, '^', '0', '0', '0', BITWISE_XOR,
                       1, '~', '0', '0', '0', BITWISE_NOT,
                       1, ',', '0', '0', '0', COMMA,
                       1, '!', '0', '0', '0', LOGICAL_NOT,
                       1, '&', '0', '0', '0', ADDRESS,
                       2, '/', '/', '0', '0', SIMPLE_COMMENT,
                       2, '/', '*', '0', '0', INLINE_COMMENT_BEGIN,
                       2, '*', '/', '0', '0', INLINE_COMMENT_END,
                       2, '/', '=', '0', '0', DIVIDE_THEN_ASSIGN,
                       2, '*', '=', '0', '0', MULTIPLY_THEN_ASSIGN,
                       2, '+', '=', '0', '0', ADD_THEN_ASSIGN,
                       2, '-', '=', '0', '0', SUBTRACT_THEN_ASSIGN,
                       2, '%', '=', '0', '0', REMAINDER_THEN_ASSIGN,
                       2, '<', '=', '0', '0', LESS_OR_EQUAL,
                       2, '>', '=', '0', '0', MORE_OR_EQUAL,
                       2, '=', '=', '0', '0', IS_EQUAL,
                       2, '!', '=', '0', '0', NOT_EQUAL,
                       2, '+', '+', '0', '0', INCREMENT,
                       2, '-', '-', '0', '0', DECREMENT,
                       2, '&', '&', '0', '0', LOGICAL_AND,
                       2, '|', '|', '0', '0', LOGICAL_OR,
                       2, '<', '<', '0', '0', BITWISE_SHIFT_LEFT,
                       2, '>', '>', '0', '0', BITWISE_SHIFT_RIGHT,
                       2, '|', '=', '0', '0', BITWISE_OR_THEN_ASSIGN,
                       2, '&', '=', '0', '0', BITWISE_AND_THEN_ASSIGN,
                       2, '^', '=', '0', '0', BITWISE_XOR_THEN_ASSIGN,
                       3, '<', '<', '=', '0', BITWISE_SHIFT_LEFT_THEN_ASSIGN,
                       3, '>', '>', '=', '0', BITWISE_SHIFT_RIGHT_THEN_ASSIGN,
                       0, '0', '0', '0', '0', '0'
                     };

  while ((len = ask_line(buf, BUFSIZE, "Enter the source code to check: ")) > 0) {
    /* Start with delimiters, uppercase and lowercase letters, and digits */
    for (i = 0; buf[i] != '\0'; ++i) {
      j = 0;
      while (delimiters[j] != buf[i] && delimiters[j] != '\0') j++;

      if (delimiters[j] == buf[i])
        map[i] = DELIMITER;
      else if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
        map[i] = SPACE;
      else if (buf[i] >= 'A' && buf[i] <= 'Z')
        map[i] = UPPERCASE_LETTER;
      else if (buf[i] >= 'a' && buf[i] <= 'z')
        map[i] = LOWERCASE_LETTER;
      else if (buf[i] >= '0' && buf[i] <= '9')
        map[i] = DIGIT;
      else map[i] = OTHER;
    }
    /* Then, prepocessor directives and keywords: */
    /* Preprocessor directive always starts with '#' at begin of string */
    i = 0;
    while (buf[i] != '\0') {
      for (start = i; (buf[start] != '\0' && (map[start] == DELIMITER || map[start] == SPACE)); ++start); /* drop the leading delimiters */

      if ((word_len = get_word(buf, word, map, start, len)) != FALSE) {
        for (kw_num = 0; state == FALSE && (kw_len = get_keyword(keywords, keyword, kw_num, FIELD_16_BYTE)) != FALSE; ++kw_num) {
          if (str_cmp(keyword, word)) {
            set_map(map, start, word_len + start, KEYWORD);
            state = TRUE;
          }
        }
        for (kw_num = 0; state == FALSE && (kw_len = get_keyword(preproc, keyword, kw_num, FIELD_16_BYTE)) != FALSE; ++kw_num) {
          if (str_cmp(keyword, word)) {
            set_map(map, start, word_len + start, PREPROCESSOR);
            state = TRUE;
          }
        }
      }
      i++;
      state = FALSE;
      if (word_len != FALSE) i = (word_len + start);
      else i += start;
    }
    /* Then, character sequences: operators, commentaries and so on */
    i = 0;
    while (buf[i] != '\0') {
      word_len = 0;
      for (j = 0; word[j] != '\0'; j++) word[j] = '\0'; /* reset */

      for (start = i; map[start] == DELIMITER; start++) /* was: map[start] == DELIMITER && word_len < 2 */
        word[word_len++] = buf[start];

      for (kw_num = 0; state == FALSE && word_len > 0 && ((kw_len = get_keyword(operators, keyword, kw_num, FIELD_6_BYTE)) != FALSE); ++kw_num)
        if (str_cmp(keyword, word)) {
          operator_type = operators[kw_num * FIELD_6_BYTE + FIELD_6_BYTE - 1]; /* the last byte in the field of digraphs structure */
          set_map(map, i, start, operator_type);
          state = TRUE;
        }
      i++;
      state = FALSE;
    } /* while */

    printf("debug: string you entered and its map:\n");
    for (i = 0; buf[i] != '\0'; i++) printf(" %c", buf[i]);
    //putchar('\n');
    for (i = 0; map[i] != FALSE; i++) printf("%.2X", map[i]);
    putchar('\n');
    fprintf(stderr, "Preparing to parse new string, buffers cleared\n");
    reset(map); /* reset the buffers*/
    reset(buf);
  }
  return 0;
}

/* ask_line: ask the user to input text data */
int ask_line(char buf[], int lim, char msg[]) {
  printf("%s", msg);
  return get_line(buf, lim);
}

/* get_line: read the string from input */
int get_line(char buf[], int lim) {
  int c, len;
  c = len = 0;

  while ((len < (lim - 1)) && (c = getchar()) != EOF && c != '\n')
    buf[len++] = c;

  if (c == '\n') buf[len++] = c;

  buf[len] = '\0';
  return len;
}

/* get_keyword: get a keyword by the its number from the dictionary */
int get_keyword(char buf[], char res[], int number, int field_width) {
  int i = 0;
  int len = 0;
  int first_item = (number * field_width) + 1;
  
  reset(res); /* reset */
  len = buf[number * field_width];
  if (len > 0) {
    for (i = 0; i < len; ++i) /* was: (buf[first_item] != '0' && i < len) */
      res[i] = buf[first_item + i];

    return len;
  }

  return FALSE;
}

/* get_word: get a word from string */
int get_word(char buf[], char res[], char map[], int start, int len) {
int i, res_len;

  reset(res); /* reset */
  res_len = 0;
  for (i = start; (i < len && map[i] != DELIMITER && map[i] != SPACE); ++i)
    res[res_len++] = buf[i];

  return res_len;
}

/* str_cmp: compare two strings */
int str_cmp(char w1[], char w2[]) {
  int i = 0;

  while (w1[i] && (w1[i] == w2[i])) i++;
  if (w1[i] == w2[i]) return TRUE;
  return FALSE;
}

/* set_map: map the character set from start to end as given in map_as */
void set_map(char map[], int start, int end, int map_as) {
  int i;
  for (i = start; i < end; i++)
    map[i] = map_as;

}

/* reset: fill with zeroes the given array */
void reset(char buf[]) {
  int i = 0;

  while (buf[i]) buf[i++] = '\0';
}
