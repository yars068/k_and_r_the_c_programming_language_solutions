#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 255
#define _HAVE_ASK_LINE_H 1
#include "../include/my_functions.h"

/* Translate unix time to worldwide time */

int get_month_days(int, int);
int get_line(char *, int);
int ask_line(char *, int, char *);

enum month_numbers { NONE, JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OKT, NOV, DEC };

int main(void) {
  enum constants { EPOCH = 1970, HRMIN = 59, DAY_HOURS = 23, WEEK_DAYS = 7, THURSDAY = 4, MONDAY = 1 };
  char *day_names[] = { NULL, "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday", NULL };
  char *month_names[] = { NULL, "yanuary", "february", "march", "april", "may", "june", "july", 
                        "august", "september", "october", "november", "december", NULL };
  char buf[BUFSIZE];
  char *msg = "Enter a Unix time (seconds):";
  int unix_time;
  int year = EPOCH;
  int month = JAN;
  int day_of_week = THURSDAY;
  int day = 1;
  int hour = 0;
  int minute = 0;
  int second = 0;
  int state = EXIT_SUCCESS;
  int len;

  while (len = ask_line(buf, BUFSIZE, msg)) {
    if (unix_time = atoll(buf)) {
      while (unix_time--) {
        if (++second > HRMIN) {
          second = 0;
          minute++;
        }
        if (minute > HRMIN) {
          minute = 0;
          hour++;
        }
        if (hour > DAY_HOURS) {
          hour = 0;
          day++;
          day_of_week++;
          if (day_of_week > WEEK_DAYS) day_of_week = MONDAY;
        }
        if (day > get_month_days(month, year)) {
          day = 1;
          month++;
        }
        if (month > DEC) {
          month = 1;
          year++;
        }
      }
      printf("%s, %d-%s-%d, %02d:%02d:%02d\n", *(day_names + day_of_week), day, *(month_names + month), year, hour, minute, second);
    }
  }
  putchar('\n');
  return state;
}

/* get_month_days: return a number of days in the given month, */
/* considering the leap year */
int get_month_days(int month, int year) {
  int month_days[][13] = {
      { NONE, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
      { NONE, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
  };
  int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  if (month >= JAN && month <= DEC) return month_days[leap][month];
}
