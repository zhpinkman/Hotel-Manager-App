#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <unordered_map>

#include "UserManager.hh"
#include "User.hh"
#include "Hotel.hh"
#include "Exception.hh"
#include "Tools.hh"
#include "Constants.hh"
#include "HotelManager.hh"
#include "Filter.hh"

class HotelManager;

class Utrip
{
    UserManager userManager;
    HotelManager hotelManager;
    Filter::HotelFilterManager hotelFilterManager;

public:
    Utrip() = default;

    void importHotels(const RAW_DATA_LIST &rawHotelsData)
    {
        hotelManager = HotelManager(rawHotelsData);
    }

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

    Filter::HotelList getHotels() const
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        Filter::HotelList hotelsResultSet;
        const auto &hotelsData = hotelManager.getHotels();
        std::transform(hotelsData.begin(), hotelsData.end(), std::back_inserter(hotelsResultSet),
                       [](std::pair<std::string, Hotel *> inputPair) { return inputPair.second; });

        return hotelFilterManager.filter(std::forward<Filter::HotelList>(hotelsResultSet));
    }

    const Hotel *const getHotel(const std::string &id) const
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        const auto hotel = hotelManager.getHotels(id);
        if (!hotel)
            throw new NotFoundException();

        return hotel;
    }

    void addFilter(const std::unordered_map<std::string, std::string> &filterObjects)
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        if (filterObjects.find("city") != filterObjects.end())
            hotelFilterManager.addFilter<Filter::CityFilter>(filterObjects.at("city"));
        else if (filterObjects.find("min_star") != filterObjects.end() &&
                 filterObjects.find("max_star") != filterObjects.end())
            hotelFilterManager.addFilter<Filter::StarsFilter>(filterObjects.at("min_star"),
                                                              filterObjects.at("max_star"));
        else if (filterObjects.find("min_price") != filterObjects.end() &&
                 filterObjects.find("max_price") != filterObjects.end())
            hotelFilterManager.addFilter<Filter::AveragePriceFilter>(filterObjects.at("min_price"),
                                                                     filterObjects.at("max_price"));
        else
            throw new BadRequestException();
    }

    void addComment(const std::string &hotelId, const std::string &commentContent)
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        const auto &username = userManager.loggedInUser->getUsername();
        hotelManager.getHotels(hotelId).addComment(username, commentContent);
    }

    const Hotel::CommentList &getComments(const std::string &hotelId) const
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        return hotelManager.getHotels(hotelId)->getComments();
    }

    void addRating(const std::string &hotelId, const Hotel::RatingData::DataType rateData)
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        const auto &username = userManager.loggedInUser->getUsername();
        hotelManager.getHotels(hotelId).addRating(username, rateData);
    }

    Hotel::RatingData::DataType getRating(const std::string &hotelId)
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        return hotelManager.getHotels(hotelId).getRating();
    }

    ~Utrip() = default;
};
