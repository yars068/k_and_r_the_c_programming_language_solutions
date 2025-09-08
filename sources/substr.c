/* substr: return a pointer to position in s, where pattern occurs, or NULL if no occurence */
/* function accepts only 2-character patterns */
char *substr(char *s, char *pattern) {
  const int next = 1; /* next character */
  int i = 0;

  while (*(s + i) && *(s + i) != *pattern) i++;

  if (*(s + i) && *(s + i) == *pattern)
    return (*(s + i + next) == *(pattern + next)) ? (s + i) : NULL;

  else return NULL;
}
