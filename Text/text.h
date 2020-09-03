#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
std::vector<std::string> split(const std::string &s, char delim);
std::string loadFileAsString(const char * name);

#endif // TEXT_H
