#include <stdio.h>
#include <string.h>
#define MAXLINES 5000 /* string count limit */
#define BUFSIZE 10000 /* space to store strings */

/* Lesson 5.7. Write the new version of readlines() that will store the strings */
/* in the buffer defined in main(), instead of using alloc() */

char *lineptr[MAXLINES]; /* pointers to strings */
int readlines_v1(char **, int);
int readlines(char **, char *, int);
void writelines(char **, int);
void qsort(char **, int, int);

/* sort and print lines */
int main(void) {
  char strbuf[BUFSIZE]; /* strings storage */
  int nlines; /* number of lines */

  /* Was: */
/* if ((nlines = readlines_v1(lineptr, MAXLINES)) >= 0) {*/
 /* Now: */
  if ((nlines = readlines(lineptr, strbuf, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  }
  else {
    printf("error: too many strings\n");
    return 1;
  }
}

#define MAXLEN 1000 /* string length limit */
int get_line(char *, int);
char *alloc(int);

/* readlines: read the lines, version 1 */
int readlines_v1(char **lineptr, int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL) return -1;
    else {
      line[len-1] = '\0'; /* remove the '\n' character */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

int readlines(char **lineptr, char *strbuf, int maxlines) {
  int len, nlines;
  char *p = strbuf;
  char line[MAXLEN];

  nlines = 0;
  printf("Type the string (ctrl + D when done): ");
  while ((len = get_line(line, MAXLEN)) > 0)
    if (nlines >= maxlines || ((p + len) - strbuf) >= BUFSIZE) return -1;
    else {
      line[len - 1] = '\0';
      lineptr[nlines++] = strcpy(p, line);
      p += len;
    }
  return nlines;
}

/* writelines: print the lines */
void writelines(char **lineptr, int nlines) {
  while (nlines-- > 0)
    printf( "%s\n", *lineptr++);
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  if (!lim) return EOF; /* buffer is full */
  *buf = '\0';
  return buf - start;
}

#define ALLOCSIZE 10000 /* count of space total */
static char allocbuf[ALLOCSIZE]; /* buffer for alloc */
static char *allocp = allocbuf; /* pointer to the free space */

/* alloc: returns the poitner to next free position */
char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n; /* space enough */
    return allocp - n; /* old р */
  }
  else return 0; /* no space */
}

/* afree: free the space pointed by р */
void afree(char *p) {
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
  allocp = p;
}

/* qsort: sort v[left]...v[right] in ascending order */
void qsort(char **v, int left, int right) {
  int i, last;
  void swap(char **, int, int);

  if (left >= right) /* does nothing if in the array less than two elements */
    return;

  swap(v, left, (left+ right)/2);
  last = left;
  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0) swap(v, ++last, i);

  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

/* swap: exchange v[i] and v[j] */
void swap(char **v, int i, int j) {
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
