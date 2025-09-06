#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TABSIZE 8
#define BUFSIZE 1024
#define MAXARGS 10
#define NO_ARGS 1

/* Lesson 5.11. Extend programs 'detab' and 'entab' to accept the list of tab stops */
/* as a command line arguments. Use the default tab stop size if there are no arguments. */
/* tabman -- a tab and space manipulation program */

int ask_line(char *buf, int lim, char *msg);
int get_line(char *buf, int lim);
int detab(char *buf, int tabsize);
int entab(char *buf, int tabsize);

int main(int argc, char *argv[]) {
  enum booleans { FALSE, TRUE };
  enum ops { DETAB, ENTAB };
  char *msg = "Enter text to operate:\n";
  char buf[BUFSIZE] = { '\0' };
  int stops_arr[MAXARGS] = { 0 };
  int *stops = stops_arr;
  int mode = FALSE;
  int def_tab_size = TRUE;  /* use default tab stop size */
  int flag = FALSE;         /* common use flag */
  int tabsize = TABSIZE;

  if (argc > MAXARGS) {
    printf("Error: too many arguments\n");
    return EXIT_FAILURE;
  }

  if (argc == NO_ARGS) {
    printf("Usage: tabman [-d|-e] [-number]... \n");
    return EXIT_SUCCESS;
  }

  while (argc-- != NO_ARGS && *++argv) { /* Skip *argv[0] because this points to program name */
    while (**argv == '-') {
      switch (*++*argv) {
        case 'd':
          mode = DETAB;
          break;
        case 'e':
          mode = ENTAB;
          break;
        default:
          if (isdigit(**argv)) {
            *stops++ = atoi(*argv);
            def_tab_size = FALSE;
          }
          break;
      }
    }
  }

  /* determine the tab stop size */
  if (!def_tab_size) {
    stops = stops_arr;
    tabsize = *++stops - *(stops - 1);
  }

  /* check tabstop size for equality */
  stops = stops_arr;
  flag = FALSE;
  while (!def_tab_size && *++stops) {
    if (*stops - *(stops - 1) == tabsize) flag = TRUE;
    else flag = FALSE;
  }
  if (!flag && !def_tab_size) {
    printf("Error: tab stops should be equal\n");
    return EXIT_FAILURE;
  }

  /* check work mode and run it */
  flag = FALSE;
  printf("Entering %s mode\n", (mode ? "entab" : "detab"));
  if (ask_line(buf, BUFSIZE, msg)) {
    switch (mode) {
      case DETAB:
        if (detab(buf, tabsize)) flag = TRUE;
        break;
      case ENTAB:
        if (entab(buf, tabsize)) flag = TRUE;
        break;
    }
  }

  if (flag) {
    printf("Result:\n%s\n", buf);
    return EXIT_SUCCESS;
  }
  else {
    printf("tabman: error: unable to %s\n", (mode ? "entab" : "detab"));
    return EXIT_FAILURE;
  }
}

#define TAB '\t'
#define SPACE ' '

static int eval_space_count(char *buf, char *start, int tabsize);

/* detab: replace a tabstops by proper count of spaces */
int detab(char *buf, int tabsize) {
  char tmpbuf[BUFSIZE] = { '\0' };
  char *tmp = tmpbuf;
  char *start = buf;
  int len = 0;

  /* Save input buffer to a local buffer, and clear it */
  for (int i = 0; *(tmp + i) = *(buf + i); i++) 
    *(buf + i) = '\0';

  while (*tmp) {
    if (*tmp != TAB) {
      *buf++ = *tmp++;
      len++;
    }
    else {
      int spaces = eval_space_count(buf, start, tabsize);
      while (spaces--) {
        *buf++ = SPACE;
        len++;
      }
      *tmp++; /* skip current position, because here is a tabstop */
    }
  }
  return len;
}

static int get_space_count(char *buf);

/* entab: replace sequences of spaces by proper number of tabstops and spaces, */
/* keeping input looks unchanged */
int entab(char *buf, int tabsize) {
  char tmpbuf[BUFSIZE] = { '\0' };
  char *tmp = tmpbuf;

  /* First, copy input buffer to local buffer and clear input buffer */
  for (int i = 0; *(tmp + i) = *(buf + i); i++) *(buf + i) = '\0';

  /* Then, entab it */
  char *start = tmp;
  while (*tmp) {
    if (*tmp != SPACE) *buf++ = *tmp++;
    else {
      int spaces = get_space_count(tmp);
      int spaces_to_next_tab = eval_space_count(tmp, start, tabsize);
      if (spaces == spaces_to_next_tab) {
        *buf++ = TAB;
        tmp += spaces;
      }
      else if (spaces > spaces_to_next_tab && spaces_to_next_tab) {
        *buf++ = TAB;
        tmp += spaces;
        while (spaces != spaces_to_next_tab) {
          *buf++ = SPACE;
          spaces--;
        }
      }
      else {
        *buf++ = SPACE;
        tmp++;
      }
    }
  }

  return tmp - start;
}

/* get_count_spaces: return count of spaces to first non-space character */
static int get_space_count(char *buf) {
  int i = 0;
  while (*buf++ == SPACE) i++;

  return i;
}

/* eval_space_count: returns the number of spaces needed to fill the current tabstop */
static int eval_space_count(char *buf, char *start, int tabsize) {
  return (buf - start) ? (tabsize - (buf - start) % tabsize) % tabsize : tabsize;
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *tmp = buf;

  while (lim-- && (*tmp = getchar()) != EOF && *tmp++ != '\n');
  *tmp++ = '\0';
  return tmp - buf;
}

/* ask_line: ask the question to user */
int ask_line(char *buf, int lim, char *msg) {

  printf("%s", msg);
  return get_line(buf, lim);
}

