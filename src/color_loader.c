#include "color_loader.h"


void color_loader_load_color_palette(const char* color_palette_file_name) {
    log_info_f("Loading color palette: color_palette_file_name=%s", color_palette_file_name);
    char file_path_buffer[SYSTEM_PATH_LENGTH_MAX];
    struct StringBuffer string_buffer_path = ARRAY_AS_STRING_BUFFER(file_path_buffer);
    string_buffer_string_add(&string_buffer_path, DATA_COLOR_PALETTE_DIRECTORY);
    string_buffer_string_add(&string_buffer_path, "/");
    string_buffer_string_add(&string_buffer_path, color_palette_file_name);
    string_buffer_terminate(&string_buffer_path);
    FILE* file = fopen(string_buffer_path.data, "r");
    if (file == NULL) {
      log_fatal_f("Could not load color palette: `%s`.", string_buffer_path.data);
    }
    color_color_palette_activate(COLOR_PALETTE_ID_DEFAULT);
    char c;
    for (uint32_t color_id = 0; color_id < COLOR_COLOR_MAX; color_id++) {
        char red_buf[4] = {fgetc(file), fgetc(file), fgetc(file), 0};
        c = fgetc(file);
        assert_f(c == ' ', "' ' expected, found %c", c);
        char green_buf[4] = {fgetc(file), fgetc(file), fgetc(file), 0};
        c = fgetc(file);
        assert_f(c == ' ', "' ' expected, found %c", c);
        char blue_buf[4] = {fgetc(file), fgetc(file), fgetc(file), 0};
        struct Color color = {
            .red = atoi(red_buf),
            .green = atoi(green_buf),
            .blue = atoi(blue_buf)
        };
        color_color_set(color_id, color);
        c = fgetc(file);
        assert_f(c == '\n' || c == EOF, "'\n' or EOF expected, found %c", c);
    }
    fclose(file);
    color_color_palette_push(COLOR_PALETTE_ID_DEFAULT);
}


void color_loader_color_pair_palette_load(const char* color_pair_palette_file_name) {
    log_info_f("Loading color pair palette: color_pair_palette_file_name=%s", color_pair_palette_file_name);
    char file_path_buffer[SYSTEM_PATH_LENGTH_MAX];
    struct StringBuffer string_buffer_path = ARRAY_AS_STRING_BUFFER(file_path_buffer);
    string_buffer_string_add(&string_buffer_path, DATA_COLOR_PAIR_PALETTE_DIRECTORY);
    string_buffer_string_add(&string_buffer_path, "/");
    string_buffer_string_add(&string_buffer_path, color_pair_palette_file_name);
    string_buffer_terminate(&string_buffer_path);
    FILE* file = fopen(string_buffer_path.data, "r");
    if (file == NULL) {
      log_fatal_f("Could not load color pair palette: string_buffer_path.data=%s", string_buffer_path.data);
    }
    char c;
    for (uint32_t color_pair_id = 0; color_pair_id < COLOR_COLOR_PAIR_MAX; color_pair_id++) {
        char background_buf[4] = {fgetc(file), fgetc(file), fgetc(file), 0};
        c = fgetc(file);
        assert_f(c == ' ', "' ' expected, found %c", c);
        char foreground_buf[4] = {fgetc(file), fgetc(file), fgetc(file), 0};
        color_color_pair_set(color_pair_id, atoi(background_buf), atoi(foreground_buf));
        c = fgetc(file);
        assert_f(c == '\n' || c == EOF, "'\n' or EOF expected, found %c", c);
    }
    color_color_pair_push();
    fclose(file);
}