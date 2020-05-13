#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <exception>

#include "UserManager.hh"
#include "User.hh"
#include "Hotel.hh"
#include "Exception.hh"
#include "Tools.hh"
#include "Constants.hh"
#include "HotelManager.hh"
#include "Filter.hh"
#include "RoomService.hh"
#include "Sort.hh"

class HotelManager;

class Utrip
{
    UserManager userManager;
    HotelManager hotelManager;
    Filter::HotelFilterManager hotelFilterManager;
    HotelSortManager hotelSortManager;

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
        hotelFilterManager = Filter::HotelFilterManager();
    }

    void login(const User &user)
    {
        if (userManager.isUserLoggedIn())
            throw new BadRequestException();

        userManager.login(user);
        hotelFilterManager = Filter::HotelFilterManager();
    }

    void logout()
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        userManager.logout();
    }

    void resetFilters()
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        hotelFilterManager = Filter::HotelFilterManager();
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

        std::vector<Hotel*> filteredHotels =
            hotelFilterManager.filter(std::forward<Filter::HotelList>(hotelsResultSet));

        std::vector<Hotel*> sortedHotels = 
            hotelSortManager.sort(filteredHotels);

        return sortedHotels;
    }

    const Hotel *const getHotel(const std::string &id) const
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        const auto hotel = hotelManager.getHotel(id);
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
        else if (filterObjects.find("type") != filterObjects.end() &&
                 filterObjects.find("quantity") != filterObjects.end() &&
                 filterObjects.find("check_in") != filterObjects.end() &&
                 filterObjects.find("check_out") != filterObjects.end())
            hotelFilterManager.addFilter<Filter::FreeRoomFilter>(filterObjects.at("type"),
                                                                 filterObjects.at("quantity"),
                                                                 filterObjects.at("check_in"),
                                                                 filterObjects.at("check_out"));
        else
            throw new BadRequestException();
    }

    void setSortSettings(std::string property, std::string order) {
        try {
            hotelSortManager.setParameters(
                strToSortableHotelProperty(property),
                strToSortOrder(order)
            );
        } catch (std::invalid_argument err) {
            throw new BadRequestException();
        }
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

        return hotelManager.getHotel(hotelId)->getComments();
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

    void reserve(const std::string &hotelId,
                 const std::string &roomType,
                 const std::size_t quantity,
                 const std::size_t arrivalTime,
                 const std::size_t departureTime)
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        auto &user = userManager.loggedInUser;
        auto &roomService = hotelManager.getHotels(hotelId).getRoomService();
        const auto requestedRoomType = RoomService::convertRoomType(roomType);
        const auto calculatedPrice = roomService.calculateReservePrice(requestedRoomType, quantity);

        if (calculatedPrice > userManager.loggedInUser->getCredit())
            throw new NotEnoughCreditException();

        if (!roomService.doesFreeRoomExists(requestedRoomType, quantity, arrivalTime, departureTime))
            throw new NotEnoughRoomException();

        user->reduceCredit(calculatedPrice);
        roomService.reserve(user->getNextUserReserveId(),
                            hotelId,
                            user->getUsername(),
                            requestedRoomType,
                            quantity,
                            calculatedPrice,
                            arrivalTime,
                            departureTime);
    }

    RoomService::ReservationSet getReservations() const
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        const auto &username = userManager.loggedInUser->getUsername();
        const auto &hotels = hotelManager.getHotels();
        RoomService::ReservationSet userReservations;

        for (const auto &hotel : hotels)
        {
            const auto userReservationsInHotel = hotel.second->getRoomService().getUserReservations(username);
            userReservations.insert(userReservations.begin(),
                                    userReservationsInHotel.begin(),
                                    userReservationsInHotel.end());
        }

        std::sort(userReservations.begin(), userReservations.end(),
                  [](const RoomService::ReservationType &first, const RoomService::ReservationType &second) {
                      return first.reservationId > second.reservationId;
                  });

        return userReservations;
    }

    void deleteReservations(const std::size_t reservationId)
    {
        if (!userManager.isUserLoggedIn())
            throw new PermissionDeniedException();

        auto &user = userManager.loggedInUser;
        const auto &hotels = hotelManager.getHotels();
        RoomService::ReservationSet userReservations;

        for (const auto &hotel : hotels)
            for (const auto &reservation : hotel.second->getRoomService().getUserReservations(user->getUsername()))
                if (reservation.reservationId == reservationId)
                {
                    constexpr double CancelPaybackRatio = 0.5;
                    user->addCredit(reservation.price * CancelPaybackRatio);
                    hotel.second->getRoomService().deleteReservation(reservationId, user->getUsername());
                    return;
                }
    }


    

private:
    // returns a tuple with the mean as its first element and the standard deviation
    // as its second element.
    std::pair<double,double> calculateReservationPriceStatistics() {
        std::vector<double> reservedRoomPrices;
        for (RoomService::ReservationType reservation: this->getReservations()) {
            double unitPrice = reservation.price / reservation.quantity;
            for (int i = 0; i < reservation.quantity; i++)
                reservedRoomPrices.push_back(unitPrice);
        }

        return std::pair<double, double>(Tools::mean(reservedRoomPrices),
            Tools::standardDeviation(reservedRoomPrices));
    }

    ~Utrip() = default;
};
