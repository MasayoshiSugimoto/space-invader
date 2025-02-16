#include "string.h"


void string_init(struct String* string) {
    string->data = NULL;
    string->length = 0;
}


void string_setup(struct String* string, const char* data) {
    string->data = data;
    string->length = strlen(data);
}


char string_get_char(const struct String* string, uint32_t index) {
    assert_f(index < string->length, "String index out of bound: index=%d, length=%d", index, string->length);
    return string->data[index];
}