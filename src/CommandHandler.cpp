#include "CommandHandler.hh"
#include "Constants.hh"
#include "Exception.hh"
#include "Interface.hh"
#include "Request.hh"
#include "Utility.hh"

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

    if (request.getMethod() == RequestType::Methods::GET)
    {
      if (request.getRequestUrl()[0] == "wallet")
        interface.runGetWalletCommand(request);
      else if (request.getRequestUrl()[0] == "hotels")
        interface.runGetHotelsCommand(request);
      else if (request.getRequestUrl()[0] == "comments")
        interface.runGetCommentsCommand(request);
      else if (request.getRequestUrl()[0] == "ratings")
        interface.runGetRateCommand(request);
      else if (request.getRequestUrl()[0] == "reserves")
        interface.runGetReserveCommand(request);
      else if (request.getRequestUrl()[0] == "manual_weights")
        interface.runGetManualWeightsCommand(request);
      else 
        throw new NotFoundException();
    }

    else if (request.getMethod() == RequestType::Methods::POST)
    {
      if (request.getRequestUrl()[0] == "signup")
        interface.runSignupCommand(request);
      else if (request.getRequestUrl()[0] == "login")
        interface.runLoginCommand(request);
      else if (request.getRequestUrl()[0] == "logout")
        interface.runLogoutCommand(request);
      else if (request.getRequestUrl()[0] == "wallet")
        interface.runAddWalletCommand(request);
      else if (request.getRequestUrl()[0] == "filters")
        interface.runAddFilterCommand(request);
      else if (request.getRequestUrl()[0] == "comments")
        interface.runAddCommentCommand(request);
      else if (request.getRequestUrl()[0] == "ratings")
        interface.runAddRateCommand(request);
      else if (request.getRequestUrl()[0] == "reserves")
        interface.runSetReserveCommand(request);
      else if (request.getRequestUrl()[0] == "sort")
        interface.runSortCommand(request);
      else if (request.getRequestUrl()[0] == "manual_weights")
        interface.runSetManualWeightsCommand(request);
      else 
        throw new NotFoundException();
    }

    else if (request.getMethod() == RequestType::Methods::DELETE)
    {
      if (request.getRequestUrl()[0] == "filters")
        interface.runResetFilterCommand(request);
      else if (request.getRequestUrl()[0] == "reserves")
        interface.runDeleteReserveCommand(request);
      else 
        throw new NotFoundException();
    }

  }
  catch (Exception *exception)
  {
    std::cout << exception->what() << std::endl;
    delete exception;
  }
}