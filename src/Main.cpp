#include <iostream>
#include "../includes/CommandHandler.hh"
#include "../includes/Constants.hh"
#include <string>
#include <cstdlib>

int main(int argc, char const *argv[])
{
  constexpr std::size_t INPUT_CSV_FILE_INDEX = 1;

  CommandHandler *commandHandler = new CommandHandler(argv[INPUT_CSV_FILE_INDEX]);
  commandHandler->start();
  return 0;
}