#pragma once

#define HOTESL_GET_ARG_SIZE 2

#define HOTEL_GET_ARG_SIZE 5

#include <string>
#include <vector>
#include "Interface.hh"
#include "Request.hh"

class CommandHandler
{
  using RequestType = Request<KeyDoesNotExistException, BadRequestException>;
  Interface<RequestType> interface;

public:
  CommandHandler(const std::string &pathToCSVFile) : interface(pathToCSVFile)
  {
  }

  void start();

  void processCommands();

  void runCommand(const std::string &command);
};
