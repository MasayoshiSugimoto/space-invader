#include "log_buffer.h"


static struct IntRingBuffer {
    int* buffer;
    int* buffer_end;
    int* pointer_begin;
    int* pointer_end;
};


void _ring_buffer_allocate(struct IntRingBuffer* ring_buffer, int length) {
    ring_buffer->buffer = malloc(sizeof(*ring_buffer->buffer) * length);
    ring_buffer->buffer_end = ring_buffer->buffer + length;
    ring_buffer->pointer_begin = ring_buffer->buffer;
    ring_buffer->pointer_end = ring_buffer->buffer;
    memset(ring_buffer->buffer, 'X', sizeof(*ring_buffer->buffer) * length);
}


void _ring_buffer_pointer_increment(struct IntRingBuffer* ring_buffer, int** pp) {
    int* p = *pp;
    p++;
    if (p >= ring_buffer->buffer_end) {
        p = ring_buffer->buffer;
    }
    *pp = p;
}


bool _ring_buffer_next(struct IntRingBuffer* ring_buffer, int** pp) {
    if (*pp == ring_buffer->pointer_end) return false;
    _ring_buffer_pointer_increment(ring_buffer, pp);
    return true;
}


void _ring_buffer_add(struct IntRingBuffer* ring_buffer, int x) {
    *ring_buffer->pointer_end = x;
    _ring_buffer_pointer_increment(ring_buffer, &ring_buffer->pointer_end);
    if (ring_buffer->pointer_begin == ring_buffer->pointer_end) {
        _ring_buffer_pointer_increment(ring_buffer, &ring_buffer->pointer_begin);
    }
}


void _ring_buffer_free(struct IntRingBuffer* ring_buffer) {
    if (ring_buffer->buffer == NULL) return;
    free(ring_buffer->buffer);
    ring_buffer->buffer = NULL;
}


void _pointer_next(const struct LogBuffer* buffer, char** pointer) {
    char* p = *pointer;
    p++;
    if (p >= buffer->buffer_end) {
        p = buffer->buffer;
    }
    *pointer = p;
}


void log_buffer_init(struct LogBuffer* log_buffer) {
    log_buffer->buffer = NULL;
    log_buffer->buffer_end = NULL;
    log_buffer->pointer_begin = NULL;
    log_buffer->pointer_end = NULL;
    log_buffer->length = 0;
}


void log_buffer_allocate(struct LogBuffer* log_buffer, int length) {
    log_buffer->buffer = malloc(length * sizeof(*log_buffer->buffer));
    log_buffer->buffer_end = log_buffer->buffer + length;
    log_buffer->pointer_begin = log_buffer->buffer;
    log_buffer->pointer_end = log_buffer->buffer + 1;
    log_buffer->length = length;
    *log_buffer->pointer_begin = '\n';
}


void log_buffer_add_char(struct LogBuffer* log_buffer, char c) {
    *log_buffer->pointer_end = c;
    _pointer_next(log_buffer, &log_buffer->pointer_end);
    if (log_buffer->pointer_begin == log_buffer->pointer_end) {
        for (int i = 0; i < log_buffer->length; i++) {
            _pointer_next(log_buffer, &log_buffer->pointer_begin);
            if (*log_buffer->pointer_begin == '\n') break;
        }
    }
}


void log_buffer_draw_to_sprite_buffer(struct LogBuffer* log_buffer, struct SpriteBuffer* sprite_buffer) {
    // Search last line.
    int width = sprite_buffer->width;
    int height = sprite_buffer->height;
    sprite_buffer_clear(sprite_buffer);
    char** lines = malloc(sizeof(char*) * height);
    memset(lines, 0, sizeof(char*) * height);
    int i = 1;
    int line_length = 0;
    lines[0] = log_buffer->pointer_begin;
    for (char* p = log_buffer->pointer_begin + 1; p != log_buffer->pointer_end; _pointer_next(log_buffer, &p)) {
        if (*p == '\n') {
            lines[i] = p;
            line_length = 0;
            i=(i+1)%height;
        } else if (line_length >= width) {
            lines[i] = p;
            line_length = 1;
            i=(i+1)%height;
        } else {
            line_length++;
        }
    }
    int x = 0;
    int line_start = i;
    for (int y = 0; y < height; y++) {
        i = (line_start + y) % height;
        if (lines[i] == 0) continue;
        for (char* c = lines[i]; c < log_buffer->buffer_end && c != log_buffer->pointer_end && c != lines[(i+1)%height]; _pointer_next(log_buffer, &c)) {
            if (*c == '\n') continue;
            struct VirtualPixel* p = sprite_buffer_access(sprite_buffer, x, y);
            p->character = *c;
            x++;
        }
        x = 0;
    }
    free(lines);
}