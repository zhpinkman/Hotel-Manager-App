//
// Created by zhivar on 4/17/20.
//

#include <iostream>
#include "../includes/Interface.h"
#include "../includes/Utrip.h"


Interface::Interface() {
    utrip = new Utrip();
}

void Interface::runSignupCommand(const std::vector<std::string> &args) {
    utrip->signup(args[4], args[6], args[8]);
}

void Interface::runLoginCommand(const std::vector<std::string> &args) {
    utrip->login(args[4], args[6]);
}

void Interface::runLogoutCommand(const std::vector<std::string> &args) {
    utrip->logout();
}


