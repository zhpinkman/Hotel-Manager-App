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

double utility::variance(std::vector<double> data)
{
  vector<double> squares;
  std::transform(data.begin(), data.end(), std::back_inserter(squares), [](double x){return x*x;});
  return mean(squares) - pow(mean(data), 2);
}


double utility::standardDeviation(vector<double> data)
{
  return sqrt(variance(data));
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
  // cout<<"weighted avg: "<<vec2str(data)<<" "<<vec2str(weights)<<endl;
  // cout<<"numerator: "<<weightedSum(data, weights)<<" denominator: "<<utility::sum(weights)<<endl;
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
  return stringValue == "true";
}