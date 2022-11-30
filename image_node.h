/*
 * image_node.h
 * public image metadata structure
 *
 * 11/1/2022
 * Kevin Gonzales
 * 11/30/22
 * Modified by Rafael Li
 */
#include "vwrap.h"

#ifndef IMAGE_NODE_FILE
#define IMAGE_NODE_FILE

typedef struct image_node {
    int num_tags;
    const char *location;
    vwrap tags;
    struct image_node *next;
    char *name; /* !MUST BE NUL TERMINATED! */
} image_node;

#endif