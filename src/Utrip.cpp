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


void Utrip::signup(std::string email, std::string username, std::string password) {
    if (userManager->isUserLoggedIn()) {
        throw new Bad_request_exception();
    }
    userManager->signup(email, username, password);
    userManager->login(email, password);
    std::cout << OK << std::endl;
}


void Utrip::login(std::string email, std::string password) {
    if (userManager->isUserLoggedIn()) {
        throw new Bad_request_exception();
    }
    userManager->login(email, password);
    std::cout << OK << std::endl;
}


void Utrip::logout() {
    if (!userManager->isUserLoggedIn()) {
        throw new Bad_request_exception();
    }
    userManager->logout();
    std::cout << OK << std::endl;
}