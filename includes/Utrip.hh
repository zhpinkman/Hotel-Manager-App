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
#include "Utility.hh"
#include "Constants.hh"
#include "HotelManager.hh"
#include "Filter.hh"
#include "RoomService.hh"
#include "Sort.hh"
#include "HotelRatings.hh"

class HotelManager;

class Utrip
{
    UserManager userManager;
    HotelManager hotelManager;
    HotelFilterManager hotelFilterManager;
    HotelSortManager hotelSortManager;
    HotelRatingWeights manualWeights;
    bool _weightsAreManual;

public:
    Utrip();

    void importHotels(std::string filename);
    void importHotels(const RAW_DATA_LIST &rawHotelsData);
    void importRatings(std::string filename);
    void importRatings(const RAW_DATA_LIST &rawRatingsData);
    void signup(const User &user);
    void login(const User &user);
    void logout();
    void resetFilters();
    void addCreditToWallet(const double amount);

    std::vector<double> reportBalanceHistory(const std::size_t count) const;
    std::vector<Hotel*> getHotels() const;
    const Hotel *const getHotel(const std::string &id) const;
    const Hotel::CommentList &getComments(const std::string &hotelId) const;
    RoomService::ReservationSet getReservations() const;
    bool isEligibleForHistoryBasedPriceFilter() const;
    HotelRatingWeights getManualWeights() const;
    bool getWeightsAreManual() const;

    void addFilter(const std::unordered_map<std::string, std::string> &filterObjects);
    void setSortSettings(std::string property, std::string order);
    void addComment(const std::string &hotelId, const std::string &commentContent);
    void addRating(const std::string &hotelId, const HotelRatings rateData);
    HotelRatings getRating(const std::string &hotelId);
    void reserve(const std::string &hotelId,
                 const std::string &roomType,
                 const std::size_t quantity,
                 const std::size_t arrivalTime,
                 const std::size_t departureTime);
    void deleteReservations(const std::size_t reservationId);
    void activateManualWeights(const HotelRatingWeights& manualWeights);
    void deactivateManualWeights();

    // returns a tuple with the mean as its first element and the standard deviation
    // as its second element.
    std::pair<double,double> calculateReservationPriceStatistics() const;



    ~Utrip() = default;
};
