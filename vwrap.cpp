/*
 * vwrap.cpp
 * Header for vwrap, wrapper for C++ vector
 *
 * 11/30/22
 * Last Modified by Rafael Li
*/
#include "vwrap.h"

void vwrap::push_back(std::string s) {
	v.push_back(s);
}

std::vector<std::string>::iterator vwrap::begin() {
	return v.begin();
}

std::vector<std::string>::iterator vwrap::end() {
	return v.end();
}

std::string vwrap::at(int ind) {
	return v.at(ind);
}

void vwrap::erase(std::vector<std::string>::iterator ind) {
	v.erase(ind);
}

int vwrap::size() {
	return v.size();
}