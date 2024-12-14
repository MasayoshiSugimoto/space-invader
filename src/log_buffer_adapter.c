// #include "log_buffer_adapter.h"


// /*
// 0123456789|
// de0def0d0c|
//         b
//        e
//   1   2  0
// def

// */


// struct LogBufferAdapter {
//     struct LogBuffer buffer;
//     int width;
//     int height;
// };


// void _pointer_next(const struct LogBuffer* buffer, char** pointer) {
//     char* p = *pointer;
//     p++;
//     if (p >= buffer->buffer_end) {
//         p = buffer->buffer;
//     }
// }


// void log_buffer_adapter_init(struct LogBufferAdapter* adapter) {
//     struct LogBuffer* log_buffer = &adapter->buffer;
//     log_buffer->buffer = NULL;
//     log_buffer->buffer_end = NULL;
//     log_buffer->pointer_begin = NULL;
//     log_buffer->pointer_end = NULL;
// }


// void log_buffer_adapter_allocate(struct LogBufferAdapter* adapter, int width, int height) {
//     struct LogBuffer* log_buffer = &adapter->buffer;
//     int length = width * height;
//     log_buffer->buffer = malloc(length * sizeof(*log_buffer->buffer));
//     log_buffer->buffer_end = log_buffer->buffer + length;
//     log_buffer->pointer_begin = log_buffer->buffer;
//     log_buffer->pointer_end = log_buffer->buffer + 1;
//     *log_buffer->pointer_begin = '\n';
// }


// void log_buffer_adapter_add_char(struct LogBufferAdapter* adapter, char c) {
//     struct LogBuffer* log_buffer = &adapter->buffer;
//     *log_buffer->pointer_end = c;
//     _pointer_next(log_buffer, &log_buffer->pointer_end);
//     if (log_buffer->pointer_begin == log_buffer->pointer_end) {
//         while (*log_buffer->pointer_begin != '\n') {
//             _pointer_next(log_buffer, &log_buffer->pointer_begin);
//         }
//     }
// }


// void log_buffer_fill_sprite_buffer(struct LogBuffer* log_buffer, struct SpriteBuffer* sprite_buffer) {
//     // Search last line.
//     sprite_buffer_clear(sprite_buffer);
//     char** lines = malloc(sizeof(char*) * sprite_buffer->height);
//     int i = 0;
//     for (char* p = log_buffer->pointer_begin; p < log_buffer->pointer_end; _pointer_next(log_buffer, &p)) {
//         if (*p == '\n') lines[i++] = p;
//     }
//     int y = 0;
//     int x = 0;
//     for (int l = imax(i - 1, 0); l < i; l++) {
//         for (char* c = lines[l]; c != lines[l+1] || c < log_buffer->buffer_end; c++) {
//             if (*c == '\n') continue;
//             struct VirtualPixel* p = sprite_buffer_access(sprite_buffer, x, y);
//             p->character = *c;
//             x++;
//             if (x >= sprite_buffer->width) {
//                 x = 0;
//                 y = imin(sprite_buffer->height - 1, y + 1);
//             }
//         }
//     }
//     free(lines);
// }