#include "CommandHandler.hh"
#include "Constants.hh"
#include "Exception.hh"
#include "Interface.hh"
#include "Request.hh"
#include "Tools.hh"

#include <iostream>
#include <string>
#include <vector>

void CommandHandler::start() { processCommands(); }

void CommandHandler::processCommands()
{
  std::string command;

  while (std::getline(std::cin, command, '\n'))
    runCommand(command);
}

void CommandHandler::runCommand(const std::string &command)
{
  try
  {
    const RequestType request(command);
    if (request.getRequestUrl()[0] == SIGNUP && request.getMethod() == RequestType::Methods::POST)
      interface.runSignupCommand(request);
    else if (request.getRequestUrl()[0] == LOGIN && request.getMethod() == RequestType::Methods::POST)
      interface.runLoginCommand(request);
    else if (request.getRequestUrl()[0] == LOGOUT && request.getMethod() == RequestType::Methods::POST)
      interface.runLogoutCommand(request);
    else if (request.getRequestUrl()[0] == WALLET && request.getMethod() == RequestType::Methods::POST)
      interface.runAddWalletCommand(request);
    else if (request.getRequestUrl()[0] == WALLET && request.getMethod() == RequestType::Methods::GET)
      interface.runGetWalletCommand(request);
    else if (request.getRequestUrl()[0] == HOTELS_GET && request.getMethod() == RequestType::Methods::GET)
      interface.runGetHotelsCommand(request);
    else if (request.getRequestUrl()[0] == "filters" && request.getMethod() == RequestType::Methods::POST)
      interface.runAddFilterCommand(request);
    else if (request.getRequestUrl()[0] == "comments" && request.getMethod() == RequestType::Methods::POST)
      interface.runAddCommentCommand(request);
    else if (request.getRequestUrl()[0] == "comments" && request.getMethod() == RequestType::Methods::GET)
      interface.runGetCommentsCommand(request);
    else if (request.getRequestUrl()[0] == "ratings" && request.getMethod() == RequestType::Methods::GET)
      interface.runGetRateCommand(request);
    else if (request.getRequestUrl()[0] == "ratings" && request.getMethod() == RequestType::Methods::POST)
      interface.runAddRateCommand(request);
    else if (request.getRequestUrl()[0] == "reserves" && request.getMethod() == RequestType::Methods::POST)
      interface.runSetReserveCommand(request);
    else if (request.getRequestUrl()[0] == "reserves" && request.getMethod() == RequestType::Methods::GET)
      interface.runGetReserveCommand(request);
    else if (request.getRequestUrl()[0] == "reserves" && request.getMethod() == RequestType::Methods::DELETE)
      interface.runDeleteReserveCommand(request);

    else
      throw new NotFoundException();
  }
  catch (Exception *exception)
  {
    std::cout << exception->what() << std::endl;
    delete exception;
  }
}