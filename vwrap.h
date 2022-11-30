/*
 * vwrap.h
 * Header for vwrap, wrapper for C++ vector
 *
 * 11/30/22
 * Last Modified by Rafael Li
*/

#include <vector>
#include <iterator>
#include <string>

#ifndef VWRAP_CLASS
#define VWRAP_CLASS

class vwrap {
private:
	std::vector<std::string> v;
public:
	void push_back(std::string s);

	std::vector<std::string>::iterator begin();

	std::vector<std::string>::iterator end();

	std::string at(int ind);

	void erase(std::vector<std::string>::iterator ind);

	int size();
};

#endif