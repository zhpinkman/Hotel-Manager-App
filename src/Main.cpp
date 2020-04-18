#include <iostream>
#include "../includes/CommandHandler.hpp"
#include "../includes/constants.hpp"
#include <string>



int main(int argc, char const *argv[]) {
  CommandHandler* commandHandler = new CommandHandler();
  std::string pathToHotelsFile = argv[INPUT_CSV_FILE_INDEX];
  commandHandler->start(pathToHotelsFile);
  return 0;
}