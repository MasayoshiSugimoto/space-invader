#include "array_test.h"


void array_test(void) {
    log_info("BEGIN array test");
    struct ArrayUint32 a;
    array_uint32_t_allocate(&a, 4);
    array_uint32_t_add(&a, 1);
    array_uint32_t_add(&a, 2);
    array_uint32_t_add(&a, 3);
    assert(array_uint32_t_get(&a, 0) == 1, "a[0] != 1");
    assert(array_uint32_t_get(&a, 1) == 2, "a[1] != 2");
    assert(array_uint32_t_get(&a, 2) == 3, "a[2] != 3");
    array_uint32_t_release(&a);
    log_info("END array test");
}