#include "space.h"


#define SPACE_DOT_POURCENTAGE 20
#define SPACE_STAR_POURCENTAGE 2


struct Vector* _dot_vectors;
static struct SliceVector _dots;
struct Vector* _star_vectors;
static struct SliceVector _stars;
static uint32_t _offset_dot_y;
struct RecuringFrameTimer _timer_dot;


uint32_t _screen_width_get(void) {
    return virtual_screen_get_width();
}


uint32_t _screen_height_get(void) {
    return virtual_screen_get_height();
}


uint32_t _screen_length_get(void) {
    return _screen_width_get() * _screen_height_get();
}


uint32_t _dot_length_get(void) {
    return _screen_length_get() * SPACE_DOT_POURCENTAGE / 1000;
}


uint32_t _star_length_get(void) {
    return _screen_length_get() * SPACE_STAR_POURCENTAGE / 1000;
}


static void _on_time_out_dot(void* p) {
    _offset_dot_y = (_offset_dot_y + 1) % (_screen_width_get() * 2);
}


static void _space_generate(struct SliceVector* vectors) {
    for (uint32_t i = 0; i < vectors->length; i++) {
        uint32_t index = rand() % _screen_length_get();
        struct Vector* v = slice_vector_get(vectors, i);
        v->x = index % _screen_width_get();
        v->y = index / _screen_width_get();
    }
}


void space_init(void) {
    _dot_vectors = NULL;
    slice_vector_init(&_dots);
    _offset_dot_y = 0;
}


void space_allocate(void) {
    _dot_vectors = malloc(sizeof(*_dot_vectors) * _dot_length_get());
    _dots.data = _dot_vectors;
    _dots.length = _dot_length_get();
    _star_vectors = malloc(sizeof(*_star_vectors) * _dot_length_get());
    _stars.data = _star_vectors;
    _stars.length = _star_length_get();
}


void space_release(void) {
    free(_dot_vectors);
    free(_star_vectors);
}


void space_setup(void) {
    recurring_frame_timer_set(&_timer_dot, _on_time_out_dot, NULL, milliseconds_as_duration(70));
    _space_generate(&_dots);
    _space_generate(&_stars);
}


void space_update(void) {
    recurring_frame_timer_update(&_timer_dot);
}


void space_draw(void) {
    for (uint32_t i = 0; i < _dots.length; i++) {
        struct Vector* v = slice_vector_get(&_dots, i);
        virtual_screen_set_char(v->x, (v->y + _offset_dot_y / 4) % _screen_height_get(), '.');
    }
    for (uint32_t i = 0; i < _stars.length; i++) {
        struct Vector* v = slice_vector_get(&_stars, i);
        virtual_screen_set_char(v->x, (v->y + _offset_dot_y) % _screen_height_get(), '*');
    }
}