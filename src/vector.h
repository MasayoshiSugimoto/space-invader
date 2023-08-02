#ifndef VECTOR_H
#define VECTOR_H


#include <stdio.h>


struct Vector {
  int x;
  int y;
};


const struct Vector VZERO;


void vector_as_string(char* buf, struct Vector v);
struct Vector vector_add(const struct Vector v1, const struct Vector v2);
struct Vector vector_minus(const struct Vector v1, const struct Vector v2);


#endif
