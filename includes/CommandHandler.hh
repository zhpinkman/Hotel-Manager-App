#ifndef __COMMANDHANDLER_H__
#define __COMMANDHANDLER_H__

#define HOTESL_GET_ARG_SIZE 2

#define HOTEL_GET_ARG_SIZE 5

#include <string>
#include <vector>
#include "Interface.hh"
#include "Request.hh"

class CommandHandler
{
  using RequestType = Request<BadRequestException, BadRequestException>;
  Interface<RequestType> interface;

public:
  CommandHandler(const std::string &pathToCSVFile) : interface(pathToCSVFile)
  {
  }

  void start();

  void processCommands();

  void processCommand(const std::string &command);

  void runCommand(const RequestType &&request);
};

#endif