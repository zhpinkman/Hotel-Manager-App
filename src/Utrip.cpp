//
// Created by zhivar on 4/17/20.
//

#include <string>
#include <iostream>
#include "../includes/Utrip.h"
#include "../includes/UserManager.h"
#include "../includes/Exception.hpp"
#include "../includes/constants.hpp"
#include "../includes/Tools.hpp"
#include "../includes/HotelManager.h"

Utrip::Utrip() {
    userManager = new UserManager();
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

void Utrip::importHotels(const std::string &hotelsFilePath) {
    const std::ifstream &hotelsFile = Tools::open_csv_file(hotelsFilePath);
    RAW_DATA_LIST rawHotelsData = Tools::parse_csv_file(
            const_cast<std::ifstream &>(hotelsFile));
    hotelManager = new HotelManager(rawHotelsData);
}

void Utrip::getWallet(const std::string &amount) {
    if (!userManager->isUserLoggedIn()) {
        throw new Bad_request_exception();
    }
    try {
        double amountValue = std::stod(amount);
        if (amountValue < 0) {
            throw new Bad_request_exception();
        }
        userManager->getWallet(amountValue);
    }
    catch (std::exception &exception) {
        throw new Bad_request_exception();
    }
}

void Utrip::getHotels() {
    if (!userManager->isUserLoggedIn()) {
        throw new Bad_request_exception();
    }
    hotelManager->getHotels();
}

void Utrip::getHotelById(const std::string &hotelId) {
    if (!userManager->isUserLoggedIn()) {
        throw new Bad_request_exception();
    }
    hotelManager->getHotelById(hotelId);
}
