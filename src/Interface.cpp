//
// Created by zhivar on 4/17/20.
//

#include <iostream>
#include "../includes/Interface.h"


Interface::Interface() {}

void Interface::runCommand(std::vector<std::string> args) {
    for (unsigned int i = 0; i < args.size(); i++) {
        std::cout << args[i] << std::endl;
    }
}
