/* 
 * pabackendtest.cpp
 * Test for Photo Album Backend
 * 
 *
 * Last Modified 11/30/22
 * Rafael Li
*/
#include "pabackend.h"
#include <iostream>
using namespace std;

int main() {
    LL photos = LL();

    // TESTING PUSH
    cout << "||TESTING PUSH||" << endl;
    cout << "PUSHING 10 IMGS NAMED 0-9" << endl;
    for (int i = 0; i < 10; i++) {
        string stri = to_string(i);
        char* chi = _strdup(stri.c_str());
        vwrap vw;
        image_node n = { 0, "location", vw, NULL, chi };
        photos.push(n);
    }
    cout << "RESULT: " << endl;
    photos.print_out();
    cout << endl;


    // TESTING REMOVE_LAST
    cout << endl;
    cout << "||TESTING REMOVELAST||" << endl;
    cout << "REMOVING 9 IMAGES" << endl;
    // Remove images from list
    for (int j = 0; j < 9; j++) {
        photos.remove_Last();
    }
    cout << "RESULT: " << endl;
    photos.print_out();
    cout << endl;

    cout << "TESTING REMOVE ON EMPTY LIST" << endl;
    // Empties list before trying exception
    photos.remove_Last();
    // Testing empty list case
    try {
        photos.remove_Last();
    }
    catch (EmptyListException ele) {
        cout << "RESULT: " << endl;
        cout << "Caught EmptyListException" << endl;
        cout << ele.what() << endl;
    }
    cout << endl << endl;

    // TESTING ADD_LAST
    // Generate images and fill list with them
    cout << "||TESTING ADDLAST||" << endl;
    cout << "ADDING TO TAIL 10 IMGS NAMED 0-9" << endl;
    for (int k = 0; k < 10; k++) {
        string stri = to_string(k);
        char* chi = _strdup(stri.c_str());
        vwrap vw;
        image_node n = { 0, "location", vw, NULL, chi };
        photos.add_Last(n);
    }
    cout << "RESULT: " << endl;
    photos.print_out();
    cout << endl << endl;


    // TESTING INSERT
    cout << "||TESTING INSERT||" << endl;
    cout << "CURRENT LIST: " << endl;
    photos.print_out();
    cout << endl;

    cout << "INSERTING INTO FIRST INDEX" << endl;
    char chfi[6] = "first";
    vwrap vw0;
    image_node infi = { 0, "location", vw0, NULL, chfi };
    photos.insert(0, infi);
    cout << "RESULT: " << endl;
    photos.print_out();
    cout << endl;

    cout << "INSERTING INTO MIDDLE, INDEX 6" << endl;
    char chmi[7] = "middle";
    vwrap vw1;
    image_node inmi = { 0, "location", vw1, NULL, chmi };
    photos.insert(5, inmi);
    cout << "RESULT: " << endl;
    photos.print_out();
    cout << endl;

    cout << "INSERTING INTO LAST INDEX" << endl;
    char chla[5] = "last";
    vwrap vw2;
    image_node inla = { 0, "location", vw2, NULL, chla };
    photos.insert(11, inla);
    cout << "RESULT: " << endl;
    photos.print_out();
    cout << endl;

    cout << "TESTING INSERTING WITH TOO LARGE INDEX" << endl;
    // Testing desired index out of bounds
    try {
        photos.insert(100, inla);
    }
    catch (ImageNotFoundException infe) {
        cout << "RESULT: " << endl;
        cout << "Caught ImageNotFoundException" << endl;
        cout << infe.what() << endl;
    }


    // TESTING REMOVE
    cout << "||TESTING REMOVE||" << endl;
    cout << "CURRENT LIST: " << endl;
    photos.print_out();
    cout << endl;

    cout << "REMOVING FIRST INDEX" << endl;
    photos.remove(0);
    cout << "RESULT: " << endl;
    photos.print_out();
    cout << endl;

    cout << "REMOVING MIDDLE INDEX" << endl;
    photos.remove(4);
    cout << "RESULT: " << endl;
    photos.print_out();
    cout << endl;

    cout << "REMOVING LAST INDEX" << endl;
    photos.remove(9);
    cout << "RESULT: " << endl;
    photos.print_out();
    cout << endl;

    // TESTING SELECT
    cout << endl << endl;
    cout << "||TESTING SELECT||" << endl;
    cout << "EMPTYING LIST" << endl;
    // Emptying list for next tests
    for (int l = 0; l < 10; l++) {
        photos.pop();
    }
    cout << "TESTING SELECTING FROM EMPTY LIST" << endl;
    // Testing selecting image from empty list
    try {
        for (int l = 0; l < 6; l++) {
            photos.pop();
        }
        photos.select(1);
    }
    catch (EmptyListException ele) {
        cout << "RESULT: " << endl;
        cout << "Caught EmptyListException" << endl;
        cout << ele.what() << endl;
    }
    cout << endl;

    // Fills list with values
    for (int m = 0; m < 5; m++) {
        string stri = to_string(m);
        char* chi = _strdup(stri.c_str());
        vwrap vw;
        image_node n = { 0, "location", vw, NULL, chi };
        photos.add_Last(n);
    }

    cout << "TESTING SELECTING FROM TOO LARGE INDEX" << endl;
    // Testing selecting image from empty list
    try {
        photos.select(6);
    }
    catch (ImageNotFoundException infe) {
        cout << "RESULT: " << endl;
        cout << "Caught ImageNotFoundException" << endl;
        cout << infe.what() << endl;
    }
    cout << endl;

    cout << "TESTING SELECTING SPECIFIC NODE" << endl;
    cout << "SELECTING 3RD NODE" << endl;
    photos.print_out();
    cout << "RESULT: " << endl;
    cout << photos.select(2)->name << endl;

    // TESTING ADD TAG
    cout << endl << endl;
    cout << "||TESTING TAGGING FUNCTIONS||" << endl;

    cout << "TESTING ADD_TAGS()" << endl;
    cout << "ADDING 3 TAGS TO FIRST MEMBER" << endl;
    char tag1[10] = "landscape";
    char tag2[12] = "atmospheric";
    char tag3[5] = "warm";
    photos.add_Tag(0, tag1);
    photos.add_Tag(0, tag2);
    photos.add_Tag(0, tag3);
    cout << "RESULT: " << endl;
    photos.print_Tags(0);
    cout << endl;

    cout << "TESTING GET_NUM_TAGS()" << endl;
    cout << "REQUESTING NUMBER OF TAGS OF FIRST MEMBER" << endl;
    cout << "RESULT: " << endl;
    cout << "PHOTO 0 HAS " << photos.get_Num_Tags(0) << " TAGS" << endl;

    cout << "REMOVING 'LANDSCAPE' TAG FROM FIRST MEMBER" << endl;
    photos.remove_Tag(0, tag1);
    cout << "RESULT: " << endl;
    photos.print_Tags(0);
    cout << endl;

    char tag4[5] = "cold";
    cout << "TESTING REMOVING NONEXISTENT TAG" << endl;
    // Testing selecting tag from image that does not contain that tag
    try {
        photos.remove_Tag(0, tag4);
    }
    catch (TagNotFoundException tnfe) {
        cout << "RESULT: " << endl;
        cout << "Caught TagNotFoundException" << endl;
        cout << tnfe.what() << endl;
    }
    cout << endl;

    return 0;
}