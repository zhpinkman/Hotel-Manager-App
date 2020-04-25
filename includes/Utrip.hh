#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "UserManager.hh"
#include "User.hh"
#include "Exception.hh"
#include "Tools.hh"
#include "Constants.hh"
#include "HotelManager.hh"

class HotelManager;

class Utrip
{
    UserManager userManager;
    HotelManager *hotelManager;

public:
    Utrip() = default;

    void signup(const User &user)
    {
        if (userManager.isUserLoggedIn())
            throw new BadRequestException();

        userManager.signup(user);
        userManager.login(user);
    }

    void login(const User &user)
    {
        if (userManager.isUserLoggedIn())
            throw new BadRequestException();

        userManager.login(user);
    }

    void logout()
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        userManager.logout();
    }

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
