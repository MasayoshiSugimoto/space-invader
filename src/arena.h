#ifndef ARENA_H
#define ARENA_H


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"


typedef uint8_t byte;
struct Arena;


struct Arena* arena_create(uint64_t capacity);
void arena_release(struct Arena* arena);
void arena_reset(struct Arena* arena);
byte* arena_alloc(struct Arena* arena, uint64_t size);


#endif