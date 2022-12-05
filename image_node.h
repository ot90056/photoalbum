/*
 * image_node.h
 * public image metadata structure
 *
 * 11/1/2022
 * Kevin Gonzales
 * 11/30/22
 * Modified by Rafael Li
 * 12/01/2022
 * Made C99 compliant - Kevin Gonzales
 */

#ifndef IMAGE_NODE_FILE
#define IMAGE_NODE_FILE
#include <string>
typedef struct vwrap vwrap;

typedef struct image_node {
    int num_tags;
    std::string location;
    vwrap * tags;
    struct image_node * next;
    std::string name; /* !MUST BE NUL TERMINATED! */
} image_node;

#endif
