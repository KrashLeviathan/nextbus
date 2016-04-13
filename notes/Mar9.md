# Lecture Notes - March 9




                 string327.h
=============================================



#ifndef STRING327_H
# define STRING327_H

# include <iostream>
# include <cstring> // Equivalent to string.h in C

class string327 {
  char *str;
 public:
  string327(); // default constructor
  ~string327(); // default destructor
  string327(const char *s);
  inline int length() const {              // Things that are very small,
    return strlen(str);                    // put the implementation in
  }                                        // the header so the compiler
  inline const char *c_str() const {       // can try to inline them.
    return str;
  }

  // Users don't worry about string length
  // Overload comparison operators
  inline int operator<(const string327 &s) {
    return strcmp(str, s.str) < 0;
  }
  inline int operator<=(const string327 &s) {
    return strcmp(str, s.str) <= 0;
  }
  inline int operator>(const string327 &s) {
    return strcmp(str, s.str) > 0;
  }
  inline int operator>=(const string327 &s) {
    return strcmp(str, s.str) >= 0;
  }
  inline int operator==(const string327 &s) {
    return strcmp(str, s.str) == 0;
  }
  inline int operator!=(const string327 &s) {
    return strcmp(str, s.str) != 0;
  }

  ... // stuff implemented in .c file...

  // Get individual characters with []. Maybe modify?
  inline char &operator[](const int index) {
    return str[index];
  }

  inline operator const char*() {
    return str;
  }
}



                 string327.c
=============================================


#include <cstring>
#include <cstdlib>

#include "string327.h"

string327::string327() {
  str = (char *) malloc(1);      // Have to cast it because C++ is picky
  // Didn't check for null, which we should probably do because malloc
  // can fail
  str[0] = '\0';
}

string327::string327(const char *s) {     // Rule of thumb: Do not
  str = (char *) malloc(strlen(s) + 1);   // explicitly call constructors
  strcpy(str, s);                         // or destructors.
}

string327::~string327() {
  free(str);
  str = NULL;
}

std::ostream &operator<<(std::ostream &o, const string327 &str) {
  return o << *str;
}
