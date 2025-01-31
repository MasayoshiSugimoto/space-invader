#include "arena.h"


struct Arena {
    byte* buffer;
    byte* next;
    uint64_t capacity;
};


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