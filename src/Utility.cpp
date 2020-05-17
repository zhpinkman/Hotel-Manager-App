#include "../includes/Utility.hh"
#include "../includes/Exception.hh"
#include "../includes/Constants.hh"
#include <random>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

vector<string> utility::split_by_char(string word, char separator)
{
  vector<string> result;
  stringstream ss(word);

  string str;
  while (getline(ss, str, separator))
    result.push_back(str);

  return result;
}

ifstream utility::open_csv_file(string filePath)
{
  ifstream file(filePath);
  if (file.fail())
    throw NotFoundException();
  return file;
}

vector<vector<string>> utility::parse_csv_file(ifstream &file)
{
  string line;
  vector<vector<string>> result;

  while (getline(file, line, ENTER))
  {
    vector<string> words = split_by_char(line, COMMA);
    result.push_back(words);
  }

  return result;
}


double utility::mean(vector<double> data) {
  double sum = std::accumulate(data.begin(), data.end(), 0);
  return sum / data.size();
}

double utility::variance(std::vector<double> data) {
  vector<double> squares;
  std::transform(data.begin(), data.end(), std::back_inserter(squares), [](double x){return x*x;});
  return mean(squares) - pow(mean(data), 2);
}


double utility::standardDeviation(vector<double> data) {
  return sqrt(variance(data));
}

template<> bool utility::extractFromString<bool>(const std::string& stringValue) {
  return stringValue == "true";
}

