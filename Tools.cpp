#include <sstream>
#include <random>
#include <algorithm>
#include "Tools.hpp"
#include "Exceptions.hpp"
using namespace std;

vector<string> Tools::splitByChar(string word, char separator)
{
    vector<string> result;
    stringstream ss(word);

    string str;
    while (getline(ss, str, separator))
        result.push_back(str);

    return result;
}

ifstream Tools::openCSVFile(string filePath)
{
    ifstream file(filePath);
    if (file.fail())
        throw Not_Found_Exception();
    return file;
}

vector<vector<string>> Tools::parseCSVFile(ifstream &file)
{
    string line;
    vector<vector<string>> result;

    while (getline(file, line))
    {
        vector<string> words = Tools::splitByChar(line, COMMA);
        result.push_back(words);
    }

    return result;
}

string Tools::generateRandomString()
{

    string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    random_device rd;
    mt19937 generator(rd());

    shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32); // assumes 32 < number of characters in str
}

bool Tools::stringToBool(string word)
{
    istringstream is(word);
    bool result;
    is >> boolalpha >> result;
    return result;
}