/*
 * buffer_test.c
 * unit test for buffer
 *
 * 11/30/2022
 * Jacob McHugh
 * 12/02/2022
 * Modified by Kevin Gonzales
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"

#ifdef NDEBUG
#undef NDEBUG
#endif

void test_buffer_load_image() {
    image_node img = { 0, "./", NULL, NULL, "test-img.png"};
    const texture_t * texture = buffer_load_image(&img);
    assert(texture && "buffer_load_image returned NULL\n");
    
    buffer_reset();
}

void test_buffer_free_image() {
    image_node img = { 0, "./", NULL, NULL, "test-img.png"};
    const texture_t * texture1 = buffer_load_image(&img);
    
    buffer_free_image(texture1);
    
    texture1 = buffer_load_image(&img);
    const texture_t * texture2 = buffer_load_image(&img);
    
    buffer_free_image(texture1);
    
    assert(texture2->data && "texture corrupted\n");
    
    buffer_reset();
}

int main() {
    test_buffer_load_image();
    test_buffer_free_image();
    printf("test passed\n");
#ifdef __clang__
    system("leaks buffer_test");
#endif
}
