#include "string_buffer.h"


void string_buffer_init(struct StringBuffer* string_buffer) {
    string_buffer->data = NULL;
    string_buffer->length = 0;
    string_buffer->capacity = 0;
}


void string_buffer_add(struct StringBuffer* string_buffer, char c) {
    assert_f(
        string_buffer->length < string_buffer->capacity, 
        "Stringbuffer already full: length=%d, capacity=%d", 
        string_buffer->length,
        string_buffer->capacity
    );
    string_buffer->data[string_buffer->length++] = c;
}


void string_buffer_string_add(struct StringBuffer* string_buffer, const char* string) {
    for (uint32_t i = 0; string[i] != 0; i++) {
        string_buffer_add(string_buffer, string[i]);
    }
}


char string_buffer_get(struct StringBuffer* string_buffer, uint32_t index) {
    assert_f(index < string_buffer->length, "Index out of bound: index=%d, length=%d", index, string_buffer->length);
    return string_buffer->data[index];
}


char* string_buffer_access(struct StringBuffer* string_buffer, uint32_t index) {
    assert_f(index < string_buffer->length, "Index out of bound: index=%d, length=%d", index, string_buffer->length);
    return &string_buffer->data[index];
}


// Add a 0 at the end of data to make it a normal C string.
void string_buffer_terminate(struct StringBuffer* string_buffer) {
    string_buffer_add(string_buffer, 0);
}