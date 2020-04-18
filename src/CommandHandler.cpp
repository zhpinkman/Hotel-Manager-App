#include "../includes/CommandHandler.hpp"
#include "../includes/constants.hpp"
#include "../includes/Tools.hpp"
#include "../includes/Exception.hpp"
#include "../includes/Interface.h"
#include <string>
#include <iostream>
#include <vector>




CommandHandler::CommandHandler(/* args */) {
    interface = new Interface();
}


void CommandHandler::start(const std::string &pathToCSVFile) {
    interface->runHotelsImport(pathToCSVFile);
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
        std::vector<std::string> commandWords = Tools::split_by_char(command, SPACE);
        validateCommand(commandWords);
        runCommand(commandWords);
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
    if (commandWords[0] != POST && commandWords[0] != GET)
        throw new Bad_request_exception();
}

void CommandHandler::validateCommandOrder(const std::vector<std::string> &commandWords)
{
//    todo
}


void CommandHandler::runCommand(const std::vector<std::string> &commandWords)
{
    std::string commandMethod = commandWords[0];
    std::string order = commandWords[1];

    if (order == SIGNUP && commandMethod == POST) {
        interface->runSignupCommand(commandWords[4], commandWords[6], commandWords[8]);
    }
    else if (order == LOGIN && commandMethod == POST) {
        interface->runLoginCommand(commandWords[4], commandWords[6]);
    }
    else if (order == LOGOUT && commandMethod == POST) {
        interface->runLogoutCommand();
    }
    else if (order == WALLET && commandMethod == GET) {
        interface->runWalletCommand(commandWords[4]);
    }
    else if (order == HOTELS_GET && commandMethod == GET && commandWords.size() == HOTESL_GET_ARG_SIZE) {
        interface->runGetHotelsCommand();
    }
    else if (order == HOTELS_GET && commandMethod == GET && commandWords.size() == HOTEL_GET_ARG_SIZE) {
        interface->runGetHotelCommand(commandWords[4]);
    }
    else
        throw new Not_found_exception();
}