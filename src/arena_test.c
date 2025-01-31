#include "arena_test.h"


void arena_test(void) {
    log_info("BEGIN arena test");
    struct Arena* arena = arena_create(8);
    byte* b1 = arena_alloc(arena, 4);
    byte* b2 = arena_alloc(arena, 4);
    log_info_f("b1=%p, b2=%p", b1, b2);
    arena_reset(arena);
    byte* b3 = arena_alloc(arena, 4);
    byte* b4 = arena_alloc(arena, 4);
    assert(b1 == b3, "Arena pointer inconsistent");
    assert(b2 == b4, "Arena pointer inconsistent");
    arena_release(arena);
    log_info("END arena test");
}