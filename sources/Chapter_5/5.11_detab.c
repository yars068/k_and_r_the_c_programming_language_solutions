#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 1000

int get_line(char *, int);
int get_space_count(char *, char *);
int detab(char *, int *);
char *args_ok(int, char **);
void clear(char *);

int main(int argc, char **argv) {
  const int base = 10;
  int len = 0;
  int tabstops[BUFSIZE] = { 0 };
  char buf[BUFSIZE], *msg = NULL;

  if (argc > 1 && (msg = args_ok(argc, argv)) == NULL) {
    for (int i = 0; --argc > 0 && **++argv == '-'; i++)
      while (isdigit(*++(*argv)))
        tabstops[i] = tabstops[i] * base + (**argv - '0');

    printf("Enter text:\n ");
    if (len = get_line(buf, BUFSIZE))
      len = detab(buf, tabstops);
  }
  else if (argc == 1) {
    printf("Enter text:\n ");
    if (len = get_line(buf, BUFSIZE))
      len = detab(buf, NULL);
  }
  else {
    printf("unknown argument: %s\n", msg);
    return EXIT_FAILURE;
  }

  printf("Result:\n\"%.*s\"\n", len - 1, buf);
  return EXIT_SUCCESS;
}

int detab(char *buf, int *tabstops) {
  char res[BUFSIZE] = { '\0' };
  char *tmp = res;
  int i = 0, tabnumber = 0;

  strcpy(tmp, buf);
  clear(buf);
  for (i = 0; *tmp; tmp++) {
    if (*tmp != '\t') buf[i++] = *tmp;
    if (tabstops == NULL && *tmp == '\t') {
      for (int spaces = get_space_count(buf, buf + i); spaces >= 1; spaces--)
        buf[i++] = ' ';
    }
    else if (tabstops != NULL && *tmp == '\t')
      for (int spaces = tabstops[tabnumber++] - ((buf + i) - buf); spaces >= 1; spaces--)
        buf[i++] = ' ';
  }
  return i;
}

#ifndef TABSTOP
#define TABSTOP 8
#endif
/* get_space_cont: returns the number of spaces needed to replace a tab */
int get_space_count(char *start, char *current) {
  int tab_pos = 0;
  int tab_num = 0;
  int space_count;

  while (tab_pos <= (current - start)) {
    tab_pos = tab_num * TABSTOP;
    space_count = tab_pos - (current - start);
    ++tab_num;
  }
  return space_count;
}

/* args_ok: return the pointer to a unknown command line argument */
/* or NULL if all arguments are valid */
char *args_ok(int argc, char **argv) {
  int i = 0;
  while (--argc > 0 && argv[++i] != NULL) {
    int j = 0;
    if (argv[i][j] == '-') {
      while (argv[i][++j] && isdigit(argv[i][j]));
      if (argv[i][j]) return argv[i];
    }
    else return argv[i];
  }
  return NULL;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  if (!lim) return EOF; /* buffer is full */
  *buf = '\0';
  return buf - start;
}

void clear(char *buf) {
  while (*buf) *buf++ = '\0';
}
