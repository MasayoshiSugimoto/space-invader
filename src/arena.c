#include "arena.h"


struct Arena {
    byte* buffer;
    byte* next;
    uint64_t capacity;
};
static struct Arena* _arena_frame = NULL;


struct Arena* arena_create(uint64_t capacity) {
    struct Arena* arena = malloc(sizeof(struct Arena));
    byte* buffer = malloc(capacity);
    arena->buffer = buffer;
    arena->next = buffer;
    arena->capacity = capacity;
    return arena;
}


void arena_release(struct Arena* arena) {
    if (arena == NULL) return;
    if (arena->buffer == NULL) return;
    free(arena->buffer);
    free(arena);
}


void arena_reset(struct Arena* arena) {
    arena->next = arena->buffer;
}


byte* arena_alloc(struct Arena* arena, uint64_t size) {
    byte* b = arena->next;
    arena->next += size;
    assert(arena->next <= arena->buffer + arena->capacity, "Arena over capacity");
    return b;
}


void arena_frame_create(void) {
    _arena_frame = arena_create(ARENA_FRAME_SIZE);
}


byte* arena_frame_alloc(uint64_t size) {
    return arena_alloc(_arena_frame, size);
}


void arena_frame_release(void) {
    arena_release(_arena_frame);
}


void arena_frame_reset(void) {
    arena_reset(_arena_frame);
}