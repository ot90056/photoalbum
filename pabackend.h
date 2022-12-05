/*
 * pabackend.h
 * Header for pabackend
 *
 * 11/28/22
 * Last Modified by Rafael Li
 */
#ifndef PABACKEND_CLASS
#define PABACKEND_CLASS

#include "image_node.h"
#include <vector>
#include <string>
#ifndef __clang__
class EmptyListException : public std::exception {
public:
    const char* what() {
        return "Exception: List is empty, requested operation invalid for empty lists";
    }
};

class ImageNotFoundException : public std::exception {
public:
    const char* what() {
        return "Exception: Specified image not found based on index value";
    }
};

class TagNotFoundException : public std::exception {
public:
    const char* what() {
        return "Exception: Specified image does not contain specified tag";
    }
};
#else
class EmptyListException : public std::exception {
public:
    const char* what() const _NOEXCEPT {
        return "Exception: List is empty, requested operation invalid for empty lists";
    }
};

class ImageNotFoundException : public std::exception {
public:
    const char* what() const _NOEXCEPT {
        return "Exception: Specified image not found based on index value";
    }
};

class TagNotFoundException : public std::exception {
public:
    const char* what() const _NOEXCEPT {
        return "Exception: Specified image does not contain specified tag";
    }
};
#endif

class LL
{
public:
    int length;
    image_node* head;
    image_node* tail;

    LL() { length = 0; head = NULL; tail = NULL; }

    // Adds image node to the head of the list
    void push(image_node n);

    // Removes image node from head of the list
    void pop();

    // Adds image node to the tail of the list
    void add_Last(image_node n);

    // Removes image node from the tail of the list
    void remove_Last();

    // Returns selected image node
    image_node* select(int ind);

    // ** ALL FUNCTIONS THAT GET SPECIFIED NODE AT INDEX USE ABOVE FUNCTION, SELECT
    // ALL EXCEPTION HANDLING FOR BAD INDEXES HAPPENS THROUGH SELECT

    // Insert image node at selected index
    void insert(int ind, image_node n);

    // Remove image node at selected index
    void remove(int ind);

    // Adds tag for image at selected index
    void add_Tag(int ind, char* tag);

    // Removes tag for image at selected index
    void remove_Tag(int ind, char* tag);

    // Returns a vector for the tags of a specified image
    std::vector<std::string> get_Tags(int ind);

    // Returns number for image at selected index
    int get_Num_Tags(int ind);

    // Returns length
    int get_Length();

    // Destructor
    ~LL();

    // BELOW FUNCTIONS USED FOR TESTING
    // Prints out entire LL
    void print_out();

    // Prints all tags for image at selected index
    void print_Tags(int ind);
private:
    // Internal func for creating image node pointers
    image_node* crt_nptr(image_node n);
};

#endif
