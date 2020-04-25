#include "../includes/CommandHandler.hh"
#include "../includes/Constants.hh"
#include "../includes/Tools.hh"
#include "../includes/Exception.hh"
#include "../includes/Interface.hh"
#include "../includes/Request.hh"

#include <string>
#include <iostream>
#include <vector>

void CommandHandler::start()
{
    processCommands();
}

void CommandHandler::processCommands()
{
    std::string command;

    while (std::getline(std::cin, command, '\n'))
        processCommand(command);
}

void CommandHandler::processCommand(const std::string &command)
{
    runCommand(RequestType(command));
}

void CommandHandler::runCommand(const RequestType &&request)
{
    try
    {
        if (request.getRequestUrl()[0] == SIGNUP && request.getMethod() == RequestType::Methods::POST)
            interface.runSignupCommand(request);
        else if (request.getRequestUrl()[0] == LOGIN && request.getMethod() == RequestType::Methods::POST)
            interface.runLoginCommand(request);
        else if (request.getRequestUrl()[0] == LOGOUT && request.getMethod() == RequestType::Methods::POST)
            interface.runLogoutCommand(request);

        // else if (order == LOGIN && commandMethod == "POST") {
        //     interface.runLoginCommand(commandWords[4], commandWords[6]);
        // }
        // else if (order == LOGOUT && commandMethod == "POST") {
        //     interface.runLogoutCommand();
        // }
        // else if (order == WALLET && commandMethod == "GET") {
        //     interface.runWalletCommand(commandWords[4]);
        // }
        // else if (order == HOTELS_GET && commandMethod == "GET" && commandWords.size() == HOTESL_GET_ARG_SIZE) {
        //     interface.runGetHotelsCommand();
        // }
        // else if (order == HOTELS_GET && commandMethod == "GET" && commandWords.size() == HOTEL_GET_ARG_SIZE) {
        //     interface.runGetHotelCommand(commandWords[4]);
        // }
        else
            throw new Not_found_exception();
    }
    catch (Exception *exception)
    {
        std::cout << exception->what() << std::endl;
        delete exception;
    }
}