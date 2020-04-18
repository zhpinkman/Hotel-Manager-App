//
// Created by zhivar on 4/17/20.
//

#include <string>
#include <iostream>
#include "../includes/Utrip.h"
#include "../includes/UserManager.h"
#include "../includes/Exception.hpp"
#include "../includes/constants.hpp"

Utrip::Utrip() {
    userManager = new UserManager();
    hotelManager = nullptr;
}


void Utrip::signup(const std::string& email, std::string username, const std::string& password) {
    if (userManager->isUserLoggedIn()) {
        throw new Bad_request_exception();
    }
    userManager->signup(email, username, password);
    userManager->login(email, password);
    printSuccessMessage();
}


void Utrip::login(std::string email, std::string password) {
    if (userManager->isUserLoggedIn()) {
        throw new Bad_request_exception();
    }
    userManager->login(email, password);
    printSuccessMessage();
}


void Utrip::logout() {
    if (!userManager->isUserLoggedIn()) {
        throw new Bad_request_exception();
    }
    userManager->logout();
    printSuccessMessage();
}


void Utrip::printSuccessMessage() {
    std::cout << OK << std::endl;
}