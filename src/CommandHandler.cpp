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

    while (std::getline(std::cin, command, ENTER))
        processCommand(command);
}

void CommandHandler::processCommand(std::string command)
{
    try
    {
        const RequestType request(command);
        std::vector<std::string> commandWords = Tools::split_by_char(command, SPACE);
        validateCommand(commandWords);
        runCommand(request);
    }
    catch (Exception *e)
    {
        std::cout << e->what() << std::endl;
    }
}

void CommandHandler::validateCommand(const std::vector<std::string> &commandWords)
{
    validateCommandSize(commandWords);
    validateCommandType(commandWords);
    validateCommandOrder(commandWords);
}

void CommandHandler::validateCommandSize(const std::vector<std::string> &commandWords)
{
    //    todo
}

void CommandHandler::validateCommandType(const std::vector<std::string> &commandWords)
{
    if (commandWords[0] != "POST" && commandWords[0] != "GET")
        throw new BadRequestException();
}

void CommandHandler::validateCommandOrder(const std::vector<std::string> &commandWords)
{
    //    todo
}

void CommandHandler::runCommand(const RequestType &request)
{
    if (request.getRequestUrl()[0] == SIGNUP && request.getMethod() == RequestType::Methods::POST)
    {
        interface.runSignupCommand(request);
    }
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