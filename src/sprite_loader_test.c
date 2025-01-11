#include "sprite_loader_test.h"


void _assert_sprite(struct SpriteBuffer* expected_sprite, struct SpriteBuffer* actual_sprite) {
    char buf_1[2048];
    char buf_2[2048];
    sprite_buffer_as_string(expected_sprite, buf_1);
    sprite_buffer_as_string(actual_sprite, buf_2);
    assert_f(
        strcmp(buf_1, buf_2) == 0, 
        "Sprite not equal:\n"
        "Expected:\n"
        "%s\n"
        "Actual:\n"
        "%s",
        buf_1,
        buf_2
    );
}


void sprite_loader_test(void) {
    log_info("sprite_loader_test...");
    int width = 4;
    int height = 2;
    {
        struct SpriteBuffer sprite;
        sprite_buffer_init(&sprite);
        sprite_buffer_file_name_set(&sprite, "sprite_buffer_test_1.dat");
        sprite_loader_save(&sprite);
    }
    {
        struct SpriteBuffer sprite_2;
        sprite_buffer_init(&sprite_2);
        sprite_buffer_file_name_set(&sprite_2, "sprite_buffer_test_2.dat");
        sprite_buffer_allocate(&sprite_2, width, height);
        sprite_buffer_clear(&sprite_2);
        sprite_buffer_access(&sprite_2, 0, 0)->character = 'a';
        sprite_buffer_access(&sprite_2, 1, 0)->character = 'b';
        sprite_buffer_access(&sprite_2, 2, 0)->character = 'c';
        sprite_buffer_access(&sprite_2, 3, 0)->character = 'd';
        sprite_buffer_access(&sprite_2, 0, 1)->character = 'e';
        sprite_buffer_access(&sprite_2, 1, 1)->character = 'f';
        sprite_buffer_access(&sprite_2, 2, 1)->character = 'g';
        sprite_buffer_access(&sprite_2, 3, 1)->character = 'h';
        sprite_loader_save(&sprite_2);
        sprite_buffer_free(&sprite_2);
    }
    {
        struct SpriteBuffer sprite;
        sprite_buffer_init(&sprite);
        sprite_loader_save(&sprite);
    }
    sprite_loader_load_sprite_set("sprite_set_test.dat");
    {
        struct SpriteBuffer* sprite = sprite_loader_sprite_get("sprite_buffer_test_1.dat");
        assert(sprite != NULL, "Sprite is null");
        assert_f(sprite->width == 0, "sprite->width -> 0 != %d", sprite->width);
        assert_f(sprite->height == 0, "sprite->height -> 0 != %d", sprite->height);
        assert_f(
            strcmp(sprite->file_name, "sprite_buffer_test_1.dat") == 0, 
            "sprite->file_name -> %s != %s", 
            sprite->file_name, 
            "sprite_buffer_test_1.dat"
        );
    }
    {
        struct SpriteBuffer* sprite = sprite_loader_sprite_get("sprite_buffer_test_2.dat");
        assert_f(sprite->width == 4, "sprite->width -> 4 != %d", sprite->width);
        assert_f(sprite->height == 2, "sprite->height -> 2 != %d", sprite->height);
        assert_f(
            strcmp(sprite->file_name, "sprite_buffer_test_2.dat") == 0, 
            "sprite->file_name -> %s != %s", 
            sprite->file_name, 
            "sprite_buffer_test_2.dat"
        );
        char buffer[2][4] = {
            {'a', 'b', 'c', 'd'},
            {'e', 'f', 'g', 'h'}
        };
        for (int y = 0; y < sprite->height; y++) {
            for (int x = 0; x < sprite->width; x++) {
                char c1 = sprite_buffer_get(sprite, x, y).character;
                char c2 = buffer[y][x];
                assert_f(c1 == c2, "sprite->buffer -> %c != %c", c1, c2);
            }
        }
        int colors[2][4] = {
            {8, 8, 8, 8},
            {8, 8, 8, 8}
        };
        for (int y = 0; y < sprite->height; y++) {
            for (int x = 0; x < sprite->width; x++) {
                int c1 = sprite_buffer_get(sprite, x, y).color_pair_id;
                int c2 = colors[y][x];
                assert_f(c1 == c2, "sprite->color_pair_id -> %c != %c", c1, c2);
            }
        }
    }
}