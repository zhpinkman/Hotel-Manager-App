#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>
#include <iomanip>

namespace utility {
  std::ifstream open_csv_file(std::string filePath);
  std::vector<std::vector<std::string>>
  parse_csv_file(std::ifstream &file);
  std::vector<std::string> split_by_char(std::string word, char separator);
  double mean(std::vector<double> data);
  double variance(std::vector<double> data);
  double standardDeviation(std::vector<double> data);

  double sum(std::vector<double> data);
  double weightedSum(std::vector<double> data, std::vector<double> weights);
  double weightedAverage(std::vector<double> data, std::vector<double> weights);

  std::vector<double> randomUniform(double lowerBound, double upperBound, uint sampleSize);

  template <typename T>
  std::vector<T> vectorSum(std::vector<T> v1, std::vector<T> v2)
  {
    if (v1.size() != v2.size())
      throw std::invalid_argument("vectorSum: the two vectors must be the same size.");
    std::vector<T> result(v1.size());
    for (int i = 0; i < v1.size(); i++) {
      result[i] = v1[i] + v2[i];
    }
    return result;
  }

  template <typename T>
  std::vector<T> vectorScale(std::vector<T> v, double scale)
  {
    std::transform(v.begin(), v.end(), v.begin(), [scale](const T& value){return scale*value;});
    return v;
  }

  template <typename T>
  std::vector<T> vectorDifference(std::vector<T> v1, std::vector<T> v2)
  {
    v2 = vectorScale(v2, -1);
    return vectorSum(v1, v2);
  }

  template <typename T>
  T clamp(T value, T lower, T upper) 
  {
    if (value < lower) return lower;
    if (value > upper) return upper;
    return value;
  }

  template <typename T>
  std::vector<T> vectorClamp(std::vector<T> v, T lower, T upper)
  {
    std::transform(v.begin(), v.end(), v.begin(),
      [lower, upper](const T& value){return clamp(value, lower, upper);}
    );
    return v;
  }

  template <typename ReturnValueType>
  ReturnValueType extractFromString(const std::string &stringValue)
  {
    std::stringstream ss(stringValue);
    ReturnValueType result;
    ss >> result;
    return result;
  }

  // for the specific case of booleans:
  template<> bool extractFromString<bool>(const std::string& stringValue);

  template <typename T>
  std::string vec2str(std::vector<T> vec) {
    std::stringstream ss;
    ss<<std::fixed<<std::setprecision(2);
    ss<<"[";
    for (int i = 0; i < vec.size()-1; i++)
      ss<<vec[i]<<", ";
    ss<<vec.back()<<"]";
    return ss.str();
  }
};