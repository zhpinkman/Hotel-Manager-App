#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "Exception.hpp"
#include "constants.hpp"
#include <fstream>
#include <string>
#include <vector>

class Tools {
public:
  static std::ifstream open_csv_file(std::string filePath);
  static std::vector<std::vector<std::string>>
  parse_csv_file(std::ifstream &file);
  static std::vector<std::string> split_by_char(std::string word,
                                                char separator);
};

#endif
