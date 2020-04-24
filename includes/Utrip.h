//
// Created by zhivar on 4/17/20.
//

#ifndef UT_AP_S99_FINAL_UTRIP_H
#define UT_AP_S99_FINAL_UTRIP_H

#include <string>
#include <vector>
#include <iostream>

#include "UserManager.h"
#include "Exception.hpp"
#include "Tools.hpp"
#include "constants.hpp"
#include "HotelManager.h"

class HotelManager;

template <typename RequestType>
class Utrip
{
    UserManager userManager;
    HotelManager *hotelManager;

    void printSuccessMessage() { std::cout << "OK" << std::endl; }

public:
    Utrip() = default;

    void signup(const RequestType &request)
    {
        if (userManager.isUserLoggedIn())
            throw new BadRequestException();

        userManager.signup(request.getParam("email"), request.getParam("username"), request.getParam("password"));
        userManager.login(request.getParam("email"), request.getParam("password"));
        printSuccessMessage();
    }

    // void login(const RequestType &request);
    // void logout(const RequestType &request);
    // void getWallet(const RequestType &request);
    // void getHotels(const RequestType &request);
    // void getHotelById(const RequestType &request);

    void importHotels(const std::string &hotelsFilePath)
    {
        const std::ifstream &hotelsFile = Tools::open_csv_file(hotelsFilePath);
        RAW_DATA_LIST rawHotelsData = Tools::parse_csv_file(const_cast<std::ifstream &>(hotelsFile));
        hotelManager = new HotelManager(rawHotelsData);
    }
};

#endif // UT_AP_S99_FINAL_UTRIP_H
