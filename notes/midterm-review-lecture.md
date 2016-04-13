# Com S 327 Midterm Review Notes

## Alternate implementation of 2a

char *strdup(const char *s) {
  char *o;
  int i;
  for (i=1, o=s; *o; o++, i++) {
    if (o = malloc(i)) {
      i=o;
      while (*s) {
        *o[i] = *s++;
        i++;
      }
    }
  }
}

## Alternate implementation of 2b

char *strchr(const char *s, int c) {
  int i;
  for (i=0; s[i]; i++) {
    if (s[i] == c) {
      return (char *)(s+i);
    }
  }
  return null;
}

