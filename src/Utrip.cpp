//
// Created by zhivar on 4/17/20.
//

#include "../includes/Exception.hpp"
#include "../includes/HotelManager.h"
#include "../includes/Tools.hpp"
#include "../includes/UserManager.h"
#include "../includes/Utrip.h"
#include "../includes/constants.hpp"
#include <iostream>
#include <string>

Utrip::Utrip() { userManager = new UserManager(); }

void Utrip::signup(const std::string &email, std::string username,
                   const std::string &password) {
  if (userManager->isUserLoggedIn()) {
    throw new BadRequestException();
  }
  userManager->signup(email, username, password);
  userManager->login(email, password);
  printSuccessMessage();
}

void Utrip::login(std::string email, std::string password) {
  if (userManager->isUserLoggedIn()) {
    throw new BadRequestException();
  }
  userManager->login(email, password);
  printSuccessMessage();
}

void Utrip::logout() {
  if (!userManager->isUserLoggedIn()) {
    throw new BadRequestException();
  }
  userManager->logout();
  printSuccessMessage();
}

void Utrip::printSuccessMessage() { std::cout << OK << std::endl; }

void Utrip::importHotels(const std::string &hotelsFilePath) {
  const std::ifstream &hotelsFile = Tools::open_csv_file(hotelsFilePath);
  RAW_DATA_LIST rawHotelsData =
      Tools::parse_csv_file(const_cast<std::ifstream &>(hotelsFile));
  hotelManager = new HotelManager(rawHotelsData);
}

void Utrip::getWallet(const std::string &amount) {
  if (!userManager->isUserLoggedIn()) {
    throw new BadRequestException();
  }
  try {
    double amountValue = std::stod(amount);
    if (amountValue < 0) {
      throw new BadRequestException();
    }
    userManager->getWallet(amountValue);
  } catch (std::exception &exception) {
    throw new BadRequestException();
  }
}

void Utrip::getHotels() {
  if (!userManager->isUserLoggedIn()) {
    throw new BadRequestException();
  }
  hotelManager->getHotels();
}

void Utrip::getHotelById(const std::string &hotelId) {
  if (!userManager->isUserLoggedIn()) {
    throw new BadRequestException();
  }
  hotelManager->getHotelById(hotelId);
}
