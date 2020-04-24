#ifndef __COMMANDHANDLER_H__
#define __COMMANDHANDLER_H__


#define HOTESL_GET_ARG_SIZE 2

#define HOTEL_GET_ARG_SIZE 5

#include <string>
#include <vector>
#include "Interface.h"

class CommandHandler {
  Interface interface;

public:
    CommandHandler(const std::string &pathToCSVFile);

    void start();

    void processCommands();

    void processCommand(std::string command);


    void validateCommand(const std::vector<std::string> &commandWords);

    void validateCommandSize(const std::vector<std::string> &commandWords);

    void validateCommandOrder(const std::vector<std::string> &commandWords);

    void validateCommandType(const std::vector<std::string> &commandWords);

    void runCommand(const std::vector<std::string> &commandWords);
};



#endif