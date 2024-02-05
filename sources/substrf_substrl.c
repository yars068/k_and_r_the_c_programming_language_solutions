#include <stdio.h>
#include <stdlib.h>

char *substrf(char *, char *);
char *substrl(char *, char *);

int main(void) {
  char *line = "this is test string. How my functions work? What she would be return?";
  char *pattern = "stri";
  char *start, *end;
  
  printf("test data: \"%s\", search pattern is \"%s\"\n", line, pattern);
  if ((start = substrf(line, pattern)) != NULL) printf("first match in position %d, that is \"%s\"\n", start - line, start);
  if ((end = substrl(line, pattern)) != NULL) printf("last match in position %d, that is \"%s\"\n", end - line, end);
}

/* substrf: return a pointer to first position in s, where p occurs, or NULL if no occurence */
char *substrf(char *s, char *p) {
  char *res = NULL;
  int i;

  while (*s) {
    if (*s == *p) {
      if (res == NULL) res = s;
      for (i = 0; *s && *(p + i) && *s == *(p + i); i++) s++;

      if (i > 0 && !*(p + i)) return res;
      else res = NULL;
    }
    s++;
  }
  return res;
}

/* substrl: return a pointer to last position in s, where p occurs, or NULL if no occurence */
char *substrl(char *s, char *p) {
  char *res = NULL;
  int i;

  while (*s) {
    if (*s == *p) {
      if (res == NULL) res = s;
      for (i = 0; *s && *(p + i) && *s == *(p + i); i++) s++;

      if (i > 0 && !*(p + i)) return s;
      else res = NULL;
    }
    s++;
  }
  return NULL;
}
