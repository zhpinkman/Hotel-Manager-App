#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <exception>

#include "UserManager.hh"
#include "HotelManager.hh"
#include "Filter.hh"
#include "Sort.hh"
#include "Hotel.hh"
#include "Exception.hh"
#include "Constants.hh"
#include "HotelManager.hh"
#include "RoomService.hh"
#include "HotelRatings.hh"

class User;

class Utrip
{
    UserManager userManager;
    HotelManager hotelManager;
    HotelFilterManager hotelFilterManager;
    HotelSortManager hotelSortManager;

    static Utrip* singleton_instance;

public:
    static Utrip* instance();
    
    Utrip() = default;

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
    HotelManager::HotelList getAllHotels() const;
    const Hotel *const getHotel(const std::string &id) const;
    const Hotel::CommentList &getComments(const std::string &hotelId) const;
    RoomService::ReservationSet getReservations() const;
    HotelRatings getRating(const std::string &hotelId);
    bool isEligibleForHistoryBasedPriceFilter() const;
    User* getLoggedInUser();
    const User* getLoggedInUser() const;
    bool getWeightsAreManual() const;
    HotelRatingWeights getManualWeights() const;
    HotelRatingWeights getEstimatedWeights();

    void addFilter(const std::unordered_map<std::string, std::string> &filterObjects);
    void setSortSettings(std::string property, std::string order);
    void addComment(const std::string &hotelId, const std::string &commentContent);
    void addRating(const std::string &hotelId, const HotelRatings rateData);
    void reserve(const std::string &hotelId,
                 const std::string &roomType,
                 const std::size_t quantity,
                 const std::size_t arrivalTime,
                 const std::size_t departureTime);
    void deleteReservations(const std::size_t reservationId);
    void activateManualWeights(HotelRatingWeights weights);
    void deactivateManualWeights();
    void setDefaultPriceFilterIsActive(bool isActive);

    // returns a tuple with the mean as its first element and the standard deviation
    // as its second element.
    std::pair<double,double> calculateReservationPriceStatistics() const;

    ~Utrip() = default;
};
