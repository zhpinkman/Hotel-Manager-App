#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "UserManager.hh"
#include "User.hh"
#include "Hotel.hh"
#include "Exception.hh"
#include "Tools.hh"
#include "Constants.hh"
#include "HotelManager.hh"

class HotelManager;

class Utrip
{
    UserManager userManager;
    HotelManager hotelManager;

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

    void addCreditToWallet(const double amount)
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        constexpr double MinimumCreditAddition = 0;
        if (amount <= MinimumCreditAddition)
            throw new BadRequestException();

        userManager.loggedInUser->addCredit(amount);
    }

    std::vector<double> reportBalanceHistory(const std::size_t count) const
    {
        return userManager.getBalanceHistory(count);
    }

    const HotelManager::HotelList &getHotels() const
    {
        return hotelManager.getHotels();
    }

    const Hotel *const getHotels(const std::string &id) const
    {
        const auto hotel = hotelManager.getHotels(id);
        if (!hotel)
            throw new NotFoundException();

        return hotel;
    }

    void importHotels(const RAW_DATA_LIST &rawHotelsData)
    {
        hotelManager = HotelManager(rawHotelsData);
    }

    ~Utrip() = default;
};
