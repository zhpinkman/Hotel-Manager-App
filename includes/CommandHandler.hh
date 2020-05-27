#pragma once

#define HOTESL_GET_ARG_SIZE 2

#define HOTEL_GET_ARG_SIZE 5

#include "Interface.hh"
#include "Request.hh"

#include <string>
#include <vector>

class CommandHandler
{
  using RequestType = Request<BadRequestException, BadRequestException>;
  Interface<RequestType> interface;

public:
  CommandHandler(const std::string &hotelsFileName, const std::string &ratingsFileName) :
   interface(hotelsFileName, ratingsFileName) {}

  void start();

  void processCommands();

  void runCommand(const std::string &command);
};
