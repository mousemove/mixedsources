#include "text.h"

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

string loadFileAsString(const char *name)
{
    std::ifstream config(name);
    std::string data,tmp;
    if(config.is_open())
    {
        while(true)
        {
            tmp = config.get();
            if(config.eof()){break;}
            data+=tmp;
        }
        //cout << "FILE SIZE ===" << data << endl;
    }
    config.close();
    return data;
}
