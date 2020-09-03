
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <regex>
#include <algorithm>
#include <fstream>
#include "dirent.h"
#include <unistd.h>
#include <thread>

using namespace std;
vector<string> split(const string& s, char delimiter);
vector<string> taskImages(const char * path);
vector<string> taskStrings(const char * path);
vector<string> preg_match_all(const std::string & rex,const string & str,unsigned int id);
string preg_match(const std::string & rex,const string & str,unsigned int id);
string replaceAll(std::string str, const string& from, string& to);
void saveStringVectorToFile(string resultFile,const vector<string> & G);
