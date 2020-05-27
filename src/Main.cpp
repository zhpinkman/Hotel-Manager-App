#include "CommandHandler.hh"

#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  constexpr std::size_t HOTELS_FILE_INDEX = 1;
  constexpr std::size_t RATINGS_FILE_INDEX = 2;

  CommandHandler *commandHandler =
      new CommandHandler(argv[HOTELS_FILE_INDEX], argv[RATINGS_FILE_INDEX]);
  commandHandler->start();
  return 0;
}
