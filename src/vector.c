#include "vector.h"


const struct Vector VZERO = {0, 0};


void vector_as_string(char* buf, struct Vector v) {
  sprintf(buf, "{x:%d, y:%d}", v.x, v.y); 
}


struct Vector vector_add(struct Vector v1, struct Vector v2) {
  struct Vector result = {v1.x + v2.x, v1.y + v2.y};
  return result;
}
