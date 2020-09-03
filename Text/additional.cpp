
#include "additional.h"

vector<string> split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}


vector<string> taskImages(const char * path)
				{
	vector<string> result;
	DIR *dir;;
	struct dirent *ent;
	if ((dir = opendir (path)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			string f(ent->d_name);
			if(f.find("jpg") != std::string::npos || f.find("png") != std::string::npos || f.find("jpeg") != std::string::npos )
				result.push_back(f);
		}
		closedir (dir);
	} else {
	}

	return result;
				}

vector<string> taskStrings(const char * path)
{
	vector<string> result;
	ifstream read(path);
	if (read.is_open())
	{
		string x ;
		while(getline(read,x)){
			result.push_back(x);
		}
	}
	return result;
}

/*Названия функций поиска с использованием регулярным выражениям сделаны по аналогии с существующими в других языках */
vector<string> preg_match_all(const std::string & rex,const string & str,unsigned int id)
		{
	vector<string> result;
	std::regex re(rex);
	std::smatch match;
	string::const_iterator searchStart( str.cbegin() );
	while(std::regex_search(searchStart, str.cend(), match, re)) {
		if(id < match.size()) result.push_back(match[id]);
		searchStart = match.suffix().first;
	}

	return result;
		}


string preg_match(const std::string & rex,const string & str,unsigned int id)
{
	string result = "";
	std::regex re(rex);
	std::smatch match;
	if(std::regex_search(str, match, re)) {
		if(id < match.size()) result = match[id];
	}

	return result;
}

string replaceAll(std::string str, const string& from, string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

void saveStringVectorToFile(string resultFile,const vector<string> & G)
{
	std::ofstream out;          // поток для записи
	out.open(resultFile);
	if (out.is_open())
	{
		for(auto row: G)
		{
			 out << row << std::endl;

		}
	}
}
