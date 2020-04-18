//
// Created by zhivar on 4/17/20.
//

#include <iostream>
#include "../includes/Interface.h"
#include "../includes/Utrip.h"


Interface::Interface() {
    utrip = new Utrip();
}

void Interface::runSignupCommand(const std::string &email, const std::string &username, const std::string &password) {
    utrip->signup(email, username, password);
}

void Interface::runLoginCommand(const std::string &email, const std::string &password) {
    utrip->login(email, password);
}

void Interface::runLogoutCommand() {
    utrip->logout();
}

void Interface::runHotelsImport(const std::string &hotelsFile) {
    utrip->importHotels(hotelsFile);
}


