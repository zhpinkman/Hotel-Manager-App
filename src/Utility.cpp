#include "Utility.hh"
#include "Exception.hh"
#include "Constants.hh"

#include <random>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <random>
#include <iostream>

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


double utility::mean(vector<double> data)
{
  double sum = std::accumulate(data.begin(), data.end(), 0);
  return sum / data.size();
}

double utility::sampleVariance(std::vector<double> data)
{
  double _mean = mean(data);
  double sumOfSquares = 0;
  for (double datum: data)
    sumOfSquares += pow(datum - _mean, 2);
  return sumOfSquares / (data.size() - 1);
}

double utility::sampleStandardDeviation(vector<double> data)
{
  return sqrt(sampleVariance(data));
}

double utility::sum(std::vector<double> data)
{
  // it is important that the third argument be 0. (double), not 0 (int). because
  // the sum operation is performed w.r.t to the type of this argument, and this means
  // casting everything to integer if 0 is passed.
  return std::accumulate(data.begin(), data.end(), 0.);
}

double utility::weightedSum(vector<double> data, vector<double> weights)
{
  if (data.size() != weights.size())
    throw invalid_argument("weightedSum: data and weights do not have the same size.");
  double sum = 0;
  for (int i = 0; i < data.size(); i++) 
    sum += data[i] * weights[i];
  return sum;
}

double utility::weightedAverage(vector<double> data, vector<double> weights) 
{
  return weightedSum(data, weights) / utility::sum(weights);
}

vector<double> utility::randomUniform(double lowerBound, double upperBound, uint sampleSize) {
  vector<double> result;
  std::uniform_real_distribution<double> distribution(lowerBound, upperBound);
  std::default_random_engine generator;
  for (uint i = 0; i < sampleSize; i++) {
    result.push_back(distribution(generator));
  }
  return result;
}

template<> bool utility::extractFromString<bool>(const std::string& stringValue)
{
  if (trim(stringValue) == "true") return true;
  if (trim(stringValue) == "false") return false;
  throw ParseException();
}

string utility::trim(string s) {
  int start = s.find_first_not_of(" \n\t");
  if (start == string::npos)
    return "";
  int end = s.find_last_not_of(" \n\t");
  return s.substr(start, end-start+1);
}


 double utility::truncate(double value, int nDecimalDigits)
 {
   int temp = (int)(value * pow(10, nDecimalDigits));
   return ((double)temp) / pow(10, nDecimalDigits);
 }
