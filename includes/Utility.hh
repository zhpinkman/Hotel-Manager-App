#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace utility {
  std::ifstream open_csv_file(std::string filePath);
  std::vector<std::vector<std::string>>
  parse_csv_file(std::ifstream &file);
  std::vector<std::string> split_by_char(std::string word, char separator);
  double mean(std::vector<double> data);
  double variance(std::vector<double> data);
  double standardDeviation(std::vector<double> data);
};

