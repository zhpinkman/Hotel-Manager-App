#include "../includes/Tools.hh"
#include "../includes/Exception.hh"
#include "../includes/Constants.hh"
#include <random>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

vector<string> Tools::split_by_char(string word, char separator)
{
  vector<string> result;
  stringstream ss(word);

  string str;
  while (getline(ss, str, separator))
    result.push_back(str);

  return result;
}

ifstream Tools::open_csv_file(string filePath)
{
  ifstream file(filePath);
  if (file.fail())
    throw NotFoundException();
  return file;
}

vector<vector<string>> Tools::parse_csv_file(ifstream &file)
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


double Tools::mean(vector<double> data) {
  double sum = std::accumulate(data.begin(), data.end(), 0);
  return sum / data.size();
}

double Tools::variance(std::vector<double> data) {
  vector<double> squares;
  std::transform(data.begin(), data.end(), std::back_inserter(squares), [](double x){return x*x;});
  return Tools::mean(squares) - Tools::mean(data);
}


double Tools::standardDeviation(vector<double> data) {
  return sqrt(Tools::variance(data));
}
