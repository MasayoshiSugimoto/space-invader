#ifndef ARENA_H
#define ARENA_H


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "consts.h"


typedef uint8_t byte;
struct Arena;


struct Arena* arena_create(uint64_t capacity);
void arena_release(struct Arena* arena);
void arena_reset(struct Arena* arena);
byte* arena_alloc(struct Arena* arena, uint64_t size);

void arena_frame_create(void);  // Create frame arena
byte* arena_frame_alloc(uint64_t size);  // Allocate for the lifecycle of a frame.
void arena_frame_release(void);
void arena_frame_reset(void);


#endif