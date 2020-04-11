#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <vector>
#include <string>
#include <fstream>
#include "constants.hpp"

class Tools
{
public:
    static std::ifstream openCSVFile(std::string filePath);
    static std::vector < std::vector<std::string> > parseCSVFile(std::ifstream &file);
    static std::vector<std::string> splitByChar(std::string word, char separator);
    static std::string generateRandomString();
    static bool stringToBool(std::string word);
};

#endif
