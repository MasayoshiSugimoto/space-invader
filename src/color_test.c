#include "color_test.h"


const struct Color BLACK = {0, 0, 0};
const struct Color RED = {255, 0, 0};
const struct Color GREEN = {0, 255, 0};
const struct Color BLUE = {0, 0, 255};
const struct Color MAGENTA = {255, 0, 255};
const struct Color WHITE = {255, 255, 255};


static void _print(const char* text) {
  for (const char* c = text; *c != 0; c++) {
    addch(*c);
  }
}


void _test_color_palettes() {
    log_info("Testing color palettes...");

    color_init();

    color_color_palette_activate(0);
    ColorId black_id = color_color_palette_add(BLACK);
    ColorId white_id = color_color_palette_add(WHITE);
    ColorId red_id = color_color_palette_add(RED);
    ColorId green_id = color_color_palette_add(GREEN);
    ColorId blue_id = color_color_palette_add(BLUE);
    ColorId magenta_id = color_color_palette_add(MAGENTA);
    
    color_color_palette_activate(1);
    color_color_palette_add(BLACK);
    color_color_palette_add(WHITE);
    color_color_palette_add(MAGENTA);
    color_color_palette_add(RED);
    color_color_palette_add(GREEN);
    color_color_palette_add(BLUE);

    color_color_palette_activate(2);
    color_color_palette_add(BLACK);
    color_color_palette_add(WHITE);
    color_color_palette_add(BLUE);
    color_color_palette_add(MAGENTA);
    color_color_palette_add(RED);
    color_color_palette_add(GREEN);

    color_color_palette_activate(3);
    color_color_palette_add(BLACK);
    color_color_palette_add(WHITE);
    color_color_palette_add(GREEN);
    color_color_palette_add(BLUE);
    color_color_palette_add(MAGENTA);
    color_color_palette_add(RED);

    color_color_pair_add(black_id, white_id);  // 1
    color_color_pair_add(black_id, red_id);  // 2
    color_color_pair_add(black_id, green_id);  // 3
    color_color_pair_add(black_id, blue_id);  // 4
    color_color_pair_add(black_id, magenta_id);  // 5
    color_color_pair_add(white_id, black_id);  // 6
    color_color_pair_add(white_id, red_id);  // 7
    color_color_pair_add(white_id, green_id);  // 8
    color_color_pair_add(white_id, blue_id);  // 9
    color_color_pair_add(white_id, magenta_id);  // 10
    color_color_pair_push();

    char buf[512];
    for (int k = 0; k < 10; k++) {
        color_color_palette_push(k%4);
        color_color_pair_push();
        erase();
        _print("TESTING COLOR PALETTES\n");
        _print("======================\n");
        _print("\n");
        _print("Color should change every second.\n");
        _print("\n");
        for (short i = 8; i <= 8+9; i++) {
            attron(COLOR_PAIR(i));
            sprintf(buf, "Color %d\n", i);
            _print(buf);
            attroff(COLOR_PAIR(i));
        }
        refresh();
        sleep(1);
    }
}


void _test_fade_in() {
    log_info("Testing fade in...");

    color_init();
    frame_timer_init();

    color_color_palette_activate(0);
    ColorId black_id = color_color_palette_add(BLACK);
    ColorId white_id = color_color_palette_add(WHITE);
    ColorId red_id = color_color_palette_add(RED);
    ColorId green_id = color_color_palette_add(GREEN);
    ColorId blue_id = color_color_palette_add(BLUE);
    ColorId magenta_id = color_color_palette_add(MAGENTA);

    color_color_pair_add(black_id, white_id);  // 1
    color_color_pair_add(black_id, red_id);  // 2
    color_color_pair_add(black_id, green_id);  // 3
    color_color_pair_add(black_id, blue_id);  // 4
    color_color_pair_add(black_id, magenta_id);  // 5
    color_color_pair_add(white_id, black_id);  // 6
    color_color_pair_add(white_id, red_id);  // 7
    color_color_pair_add(white_id, green_id);  // 8
    color_color_pair_add(white_id, blue_id);  // 9
    color_color_pair_add(white_id, magenta_id);  // 10
    color_color_pair_push();

    color_fade_start_fade_in(milliseconds_as_duration(1000));
    int mode_fade_in = 0;
    int mode_fade_out = 1;
    int mode = mode_fade_in;

    char buf[512];
    for (int fade_count = 0; fade_count < 2;) {
        frame_timer_on_frame_start();
        color_update();
        if (color_fade_is_done() && mode == mode_fade_in) {
          color_fade_start_fade_out(milliseconds_as_duration(1000));
          mode = mode_fade_out;
        } else if (color_fade_is_done() && mode == mode_fade_out) {
          color_fade_start_fade_in(milliseconds_as_duration(1000));
          mode = mode_fade_in;
          fade_count++;
        }

        erase();
        _print("TESTING FADE IN/OUT\n");
        _print("===================\n");
        _print("\n");
        _print("Fade in and fade out should loop\n");
        _print("\n");
        for (short i = 8; i <= 8+9; i++) {
            attron(COLOR_PAIR(i));
            sprintf(buf, "color_pair_id = %d\n", i);
            _print(buf);
            attroff(COLOR_PAIR(i));
        }
        refresh();
    }
}


static void _test_interpolation_cos_f() {
  float iteration_count = 10;
  for (int i = 0; i <= iteration_count; i++) {
    float input_start = 10.0f;
    float input_end = 20.0f;
    float input_current = input_start + (input_end - input_start) * ((float)i / (float)iteration_count);
    float output_start = 15.0f;
    float output_end = 5.0f;
    float output = interpolation_cos_f(input_current, input_start, input_end, output_start, output_end);
    log_info_f("COLOR_TEST_INTERPOLATION_COS_F:%f, %f", input_current, output);
  }
}


void color_test() {
  _test_interpolation_cos_f();
  _test_fade_in();
  _test_color_palettes();
}


