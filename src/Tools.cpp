#include "../includes/Tools.hpp"
#include "../includes/Exception.hpp"
#include "../includes/constants.hpp"
#include <random>
#include <sstream>
using namespace std;

vector<string> Tools::split_by_char(string word, char separator) {
  vector<string> result;
  stringstream ss(word);

  string str;
  while (getline(ss, str, separator))
    result.push_back(str);

  return result;
}

ifstream Tools::open_csv_file(string filePath) {
  ifstream file(filePath);
  if (file.fail())
    throw Not_found_exception();
  return file;
}

vector<vector<string>> Tools::parse_csv_file(ifstream &file) {
  string line;
  vector<vector<string>> result;

  while (getline(file, line)) {
    vector<string> words = split_by_char(line, COMMA);
    result.push_back(words);
  }

  return result;
}
