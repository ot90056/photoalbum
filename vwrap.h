/*
 * vwrap.h
 * Header for vwrap, wrapper for C++ vector
 *
 * 11/30/22
 * Last Modified by Rafael Li
 * 12/01/2022
 * modified to aide C99 compliance in "image_node.h" - Kevin Gonzales
*/
#ifndef VWRAP_FILE
#define VWRAP_FILE

#include <vector>
#include <string>

struct vwrap {
    std::vector<std::string> vector;
};

#endif
