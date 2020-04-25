#include "../includes/Tools.hh"
#include "../includes/Exception.hh"
#include "../includes/Constants.hh"
#include <random>
#include <sstream>

std::vector<std::string> Tools::split_by_char(std::string word, char separator)
{
  std::vector<std::string> result;
  std::stringstream ss(word);

  std::string str;
  while (getline(ss, str, separator))
    result.push_back(str);

  return result;
}

std::ifstream Tools::open_csv_file(std::string filePath)
{
  std::ifstream file(filePath);
  if (file.fail())
    throw NotFoundException();
  return file;
}

std::vector<std::vector<std::string>> Tools::parse_csv_file(std::ifstream &file)
{
  std::string line;
  std::vector<std::vector<std::string>> result;

  while (std::getline(file, line, ENTER))
  {
    std::vector<std::string> words = split_by_char(line, COMMA);
    result.push_back(words);
  }

  return result;
}
