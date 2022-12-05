/* 
 * pabackend.cpp
 * Singly-linked list for photo album
 *
 * Last Modified 11/28/22
 * Rafael Li
*/
#include "image_node.h"
#include "pabackend.h"
#include "vwrap.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

image_node* LL::crt_nptr(image_node n) {
    image_node* nptr = new image_node();
    nptr->location = n.location;
    nptr->name = n.name;
    nptr->next = n.next;
    nptr->num_tags = n.num_tags;
    nptr->tags = n.tags;
    return nptr;
}

void LL::push(image_node n) {
    image_node* nptr = crt_nptr(n);
    // If list is empty, set head to new node
    if (head == NULL) {
        head = nptr;
        length++;
        return;
    }
    // Otherwise, traverse to end of list and add new node
    image_node* curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = nptr;
    length++;
}

void LL::pop() {
    // Case empty list
    if (length == 0) {
        throw EmptyListException();
    }
    // Case list of size 1
    else if (length == 1) {
        delete head;
        head = NULL;
        tail = NULL;
        length--;
    }
    // Remove the head
    else {
        image_node* nptr = head->next;
        delete head;
        head = nptr;
        length--;
        if (length == 1) {
            tail = head;
        }
    }
}

void LL::add_Last(image_node n) {
    image_node* nptr = crt_nptr(n);
    // Case pushing into an empty list
    if (length == 0) {
        head = nptr;
        tail = nptr;
        length++;
    }
    // Add image node to the end of the list
    else {
        tail->next = nptr;
        tail = nptr;
        length++;
    }
}

void LL::remove_Last() {
    // Case list is empty
    if (length == 0) {
        throw EmptyListException();
    }
    // Case popping from a 1-item list
    else if (length == 1) {
        delete head;
        head = NULL;
        tail = NULL;
        length--;
    }
    // Delete the last item in list
    else {
        image_node* prev = NULL;
        image_node* curr = head;
        while (curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = NULL;
        delete curr;
        tail = prev;
        length--;
    }
}

void LL::insert(int ind, image_node n) {
    image_node* nptr = crt_nptr(n);
    // Case list is empty
    if (length == 0) {
        throw EmptyListException();
    }
    // Case desired index not in list
    else if (ind > length || ind < 0) {
        throw ImageNotFoundException();
    }
    // Case inserting into beginning
    else if (ind == 0) {
        nptr->next = head;
        head = nptr;
        length++;
    }
    // Insert at specified index
    else {
        image_node* prev = NULL;
        image_node* curr = head;
        // Find desired image
        for (int i = 0; i < ind; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = nptr;
        nptr->next = curr;
        length++;
    }
}

void LL::remove(int ind) {
    // Case list is empty
    if (length == 0) {
        throw EmptyListException();
    }
    // Case desired index not in list
    else if (ind > length || ind < 0) {
        throw ImageNotFoundException();
    }
    // Case index is or list is 2 items
    else if (ind == 0 || length == 2) {
        if (ind == 0) {
            image_node* curr = head;
            head = head->next;
            delete curr;
            length--;
        }
        else {
            image_node* curr = head->next;
            tail = head;
            delete curr;
            length--;
        }
    }
    // Remove from specified index
    else {
        image_node* prev = NULL;
        image_node* curr = head;
        for (int i = 0; i < ind; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        delete curr;
        length--;
        if (prev->next == NULL) {
            tail = prev;
        }
    }
}

image_node* LL::select(int ind) {
    // Select image at specified index
    image_node* curr = head;
    if (ind > length || ind < 0) {
        throw ImageNotFoundException();
    }
    for (int i = 0; i < ind; i++) {
        curr = curr->next;
    }
    return curr;
}

void LL::add_Tag(int ind, char* tag) {
    image_node* nptr = select(ind);
    nptr->tags->vector.push_back(tag);
}

void LL::remove_Tag(int ind, char* tag) {
    image_node* nptr = select(ind);
    if (std::find(nptr->tags->vector.begin(), nptr->tags->vector.end(), tag) != nptr->tags->vector.end()) {
        int ind = 0;
        bool found = false;
        // Find proper index
        while (!found) {
            if (nptr->tags->vector.at(ind) == tag)
                found = true;
            else ind++;
        }
        nptr->tags->vector.erase(nptr->tags->vector.begin() + ind);
    }
    else {
        throw TagNotFoundException();
    }
}

int LL::get_Num_Tags(int ind) {
    image_node* nptr = select(ind);
    return nptr->tags->vector.size();
}

std::vector<std::string> LL::get_Tags(int ind) {
    image_node* nptr = select(ind);
    return nptr->tags->vector;
}

void LL::print_Tags(int ind) {
    image_node *n = select(ind);
    int j = 1;
    for (string i : n->tags->vector) {
        cout << "TAG[" << j << "]" << i << endl;
        j++;
    }
}

int LL::get_Length() {
    return length;
}

LL::~LL() {
    if (head != NULL) {
        image_node* prev = NULL;
        image_node* curr = head;
        while (curr != NULL) {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
    }
    else {
        head = NULL;
        tail = NULL;
        length = 0;
    }
}

// For testing
// Prints out the names of every image in the list
// Prints "EMPTY LIST" if list is empty
void LL::print_out() {
    if (head == NULL && tail == NULL && length == 0) {
        cout << "EMPTY LIST" << endl;
    }
    else {
        image_node* curr = head;
        int i = 1;
        while (curr->next != NULL) {
            cout << "[" << i << "] = " << curr->name << endl;
            curr = curr->next;
            i++;
        }
        cout << "[" << i << "] = " << curr->name << endl;
    }
}
