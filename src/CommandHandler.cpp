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
        std::vector<std::string> commandWords = Tools::split_by_char(command, SPACE);
        validateCommand(commandWords);
        interface->runCommand(commandWords);
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