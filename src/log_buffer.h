#ifndef LOG_BUFFER_H
#define LOG_BUFFER_H


#include <stddef.h>
#include <stdlib.h>
#include "sprite_buffer.h"


struct LogBuffer {
    char* buffer;
    char* buffer_end;
    char* pointer_begin;
    char* pointer_end;
    int length;
};


void log_buffer_init(struct LogBuffer* log_buffer);
void log_buffer_allocate(struct LogBuffer* log_buffer, int length);
void log_buffer_add_char(struct LogBuffer* log_buffer, char c);
void log_buffer_draw_to_sprite_buffer(struct LogBuffer* log_buffer, struct SpriteBuffer* sprite_buffer);


#endif