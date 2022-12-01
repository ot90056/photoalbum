/*
 * buffer.h
 * [mostly] thread safe
 *
 * stb image is not completely thread safe but
 * switching stb image's global state is not
 * necessary so all should be fine
 *
 * 11/1/2022
 * Kevin Gonzales
 */

#ifndef BUFFER_FILE
#define BUFFER_FILE

#include "image_node.h"

#include <stdint.h>

typedef struct texture_t {
    int width;
    int height;
    uint8_t * data;
} texture_t;

/* loads an image into memory
 * node - the image_node to load
 * returns - texture data in 32bit RGBA pixel format */
const texture_t * buffer_load_image(const image_node * node);

/* marks texture at address as free space
 * addr - address of texture returned from buffer_load_image
 * WARNING: if an invalid address is given and the application is
 * not in debug mode [NDEBUG is defined] this function will
 * access invalid memory. DO NOT CALL ON INVALID POINTERS!*/
void buffer_free_image(const texture_t * texture);

/* resets buffer and frees all memory in use
 * quicker and safer than buffer_free_image
 */
void buffer_reset();

#endif
