#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "UserManager.h"
#include "User.h"
#include "Exception.hpp"
#include "Tools.hpp"
#include "constants.hpp"
#include "HotelManager.h"

class HotelManager;

class Utrip
{
    UserManager userManager;
    HotelManager *hotelManager;

    void printSuccessMessage() { std::cout << "OK" << std::endl; }

public:
    Utrip() = default;

    void signup(const User &user)
    {
        if (userManager.isUserLoggedIn())
            throw new BadRequestException();

        userManager.signup(user);
        userManager.login(user);
        printSuccessMessage();
    }

    // void login(const RequestType &request);
    // void logout(const RequestType &request);
    // void getWallet(const RequestType &request);
    // void getHotels(const RequestType &request);
    // void getHotelById(const RequestType &request);

    void importHotels(const RAW_DATA_LIST &rawHotelsData)
    {
        hotelManager = new HotelManager(rawHotelsData);
    }

    ~Utrip()
    {
        delete hotelManager;
    }
};
