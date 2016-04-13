# Lecture Notes - March 7

## Assignment 1.05

- Valgrind output to file:  $ valgrind | grep <file>
- Maybe use mvprintw() to print monster list and such
- Maybe abstract(?) the popup dialog

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Random

last value that was returned to the shell:  $?
List stuff:  strings a.out

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

## Combining C and C++ in one program

We need to tell the g++ compiler not to change the names of
the functions. Which means we can't overload functions anymore,
but it allows C++ code to work with C code.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

### Example 1 - C++ part

#include <iostream>

void cpp_function(const char *s) {
  std::cout << s << std::endl;
}

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

### Example 1 - C part

int main(int argc, char *argv[]) {
  // cpp_function("Hello World!\n");   // Won't link
  // _Z12cpp_functionPKc("Hello World!\n");   // Works, but really horrible.

  return 0;
}

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

### Example 1 - How to reconcile?

Make a header file for the C++ part

#ifndef HEADER_H
# define HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

void cpp_function(const char *s);

#ifdef __cplusplus
}
#endif

#endif

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

### How does it work?

Tells the g++ compiler not to name-mangle anything within the brackets.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

### Example 2 - Using C++ code WITH C code

#include <iostream>

void cpp_function(const char *s) {
  std::cout << s << std::endl;
}

void *get_cout() {
  return (void *) &std::cout;
}

void use_cout(void *ptr) {
  (*(std::ostream *) ptr) << "CS 327 rocks!\n";
}

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

### Usage

#ifndef HEADER_H
# define HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

void cpp_function(const char *s);
void *get_cout();
void use_cout(void *ptr);

#ifdef __cplusplus
}
#endif

#endif

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main(int argc, char *argv[]) {
  cpp_function("Hello World!\n");
  void *v;
  v = get_cout();
  use_cout(v);

  return 0;
}

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -n

## Inheritance in C++

class shape {
public:
  double area();
  double perimeter();
  //...
};

class rectangle : public shape {
protected:
  double side1, side2;
  // Can call area, perimeter, or can override with new versions
};

class square : public rectangle {
  ...
};
