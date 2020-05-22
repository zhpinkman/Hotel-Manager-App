#pragma once

#include <string>
#include <vector>

#include "Exception.hh"
#include "HotelRatings.hh"
#include "Hotel.hh"

class Reservation;
class Utrip;

class User
{
public:
    User(const std::string &email, const std::string &username, const std::string &password);

    bool emailMatches(const std::string &_email) const { return (email == _email); }

    bool passwordMatches(const std::string &_password) const { return password == _password; }

    std::string getEmail() const { return email; }
    const std::string &getUsername() const { return username; }
    std::string getPassword() const { return password; }
    double getCredit() const { return credit; }
    std::vector<double> getBalanceHistoryReport(const std::size_t count) const;
    std::vector<HotelRatings> getRatings() const;
    HotelRatingWeights getManualWeights() const;
    bool getWeightsAreManual() const;
    HotelRatingWeights getEstimatedWeights();

    std::size_t getNextUserReserveId() { return nextUserReserveId++; }

    void addCredit(const double amount);
    void reduceCredit(const double cost);
    void activateManualWeights(const HotelRatingWeights& manualWeights);
    void deactivateManualWeights();
    void invalidateEstimatedWeights() { estimatedWeightsAreUpToDate = false; }
private:
    std::string email;
    std::string username;
    std::string password;
    std::vector<Reservation *> reservations;
    double credit;
    std::vector<double> balanceHistory;
    std::size_t nextUserReserveId;

    HotelRatingWeights manualWeights;
    bool _weightsAreManual;

    HotelRatingWeights estimatedWeights;
    bool estimatedWeightsAreUpToDate;
};
