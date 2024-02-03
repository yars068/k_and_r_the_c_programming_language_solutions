#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 100

/* Lesson 5.8. There is no error checking in day_of_year() and month_day(). Remedy this defect */

int get_line(char *, int);
void clear(char *);
int get_month_day(int, int, int *, int *);
int get_day_of_year(int, int, int);

int main(void) {
  char buf[BUFSIZE];
  enum yesno { NO, YES };
  char *suffix[] = { "year", "month", "day", NULL };
  int year;
  int month;
  int day;
  int *vars[] = { &year, &month, &day, NULL };
  int i, state;
  int day_of_year;

  for (i = 0; state != EOF && *(vars + i) != NULL; i++) {
    printf("Enter the %s: ", *(suffix + i));
    clear(buf);
    if (state = get_line(buf, BUFSIZE) != EOF) {
      if (**(vars + i) = atoi(buf));
      else state = EOF;
    }
  }
  if (day_of_year = get_day_of_year(year, month, day))
    printf("Day of year is %d\n", day_of_year);
  else {
    printf("Wrong input, try again\n");
    return EXIT_FAILURE;
  }
  month = day = 0; /* to check whether get_month_day() works */
  if (get_month_day(year, day_of_year, &month, &day))
    printf("You enter the date %02d-%02d-%d\n", day, month, year);
  else {
    printf("Wrong input, try again\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

enum months { WRONG, JAN = 1, DEC = 12};

/* day_of_year: determine the day of year by month and day */
int get_day_of_year(int year, int month, int day) {
  int i, leap, day_of_year = day;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  if (month >= JAN && month <= DEC && day >= 1 && day <= daytab[leap][month]) {
    for (i = 1; i < month; i++)
      day_of_year += daytab[leap][i];
  }
  else return WRONG;
  return day_of_year;
}

/* month_day: determine the month and day by the day of year */
int get_month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;
  int maxdays[2] = { 365, 366 };

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  if (yearday  <= maxdays[leap]) {
    for (i = 1; yearday > daytab[leap][i]; i++)
      yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;
  }
  return (yearday <= maxdays[leap]);
}

void clear(char *buf) {
  while (*buf) *buf++ = '\0';
}

/* get_line: store the input stream to array */
int get_line(char *buf, int lim) {
  char *start = buf;

  while (lim-- && (*buf = getchar()) != EOF && *buf++ != '\n');
  if (!lim) return EOF; /* buffer is full */
  *buf = '\0';
  return buf - start;
}
