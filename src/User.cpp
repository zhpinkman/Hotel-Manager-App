#include "User.hh"
#include "Utrip.hh"
#include "RatingCategoryWeightEstimator.hh"

#include <vector>
#include <iostream>

using namespace std;

User::User(const string &email, const string &username, const string &password)
    : email(email),
    username(username),
    password(password),
    _weightsAreManual(false),
    estimatedWeightsAreUpToDate(false),
    credit(0),
    balanceHistory({0}),
    nextUserReserveId(1)
{}

void User::addCredit(const double amount)
{
    credit += amount;
    balanceHistory.push_back(credit);
}

vector<double> User::getBalanceHistoryReport(const size_t count) const
{
    vector<double> result;
    for (size_t i = balanceHistory.size() - 1; (balanceHistory.size() - 1 - i) < count; i--)
    {
        result.push_back(balanceHistory[i]);
        if (!i)
            return result;
    }
    return result;
}

void User::reduceCredit(const double cost)
{
    if (cost > credit)
        throw new NotEnoughCreditException();

    credit -= cost;
    balanceHistory.push_back(credit);
}

vector<HotelRatings> User::getRatings() const 
{
    vector<HotelRatings> result;
    for (pair<string, Hotel*> element: Utrip::instance()->getAllHotels())
    {
        Hotel::RatesList hotelRatings = element.second->getRatings();
        if (hotelRatings.find(username) != hotelRatings.end())
            result.push_back(hotelRatings.at(username));
    }
    return result;
}

void User::activateManualWeights(const HotelRatingWeights& manualWeights) 
{
    _weightsAreManual = true;
    this->manualWeights = manualWeights;
}

void User::deactivateManualWeights() 
{
    _weightsAreManual = false;
}

HotelRatingWeights User::getManualWeights() const
{
    return manualWeights;
}

bool User::getWeightsAreManual() const 
{
    return _weightsAreManual;
}

HotelRatingWeights User::getEstimatedWeights()  
{
    if (estimatedWeightsAreUpToDate)
        return estimatedWeights;
    else 
    {
        vector<HotelRatings> ratings = this->getRatings();
        if (ratings.size() < 5)
            throw new InsufficientRatingsException();
        estimatedWeights = RatingCategoryWeightEstimator().estimate(ratings);
        // cout<<"learned weights are: "<<endl;
        // for (string s: HotelRatingWeights::categories)
            // cout<<estimatedWeights.getWeight(s) * (4./estimatedWeights.getWeight("location"))<<" ";
        // cout<<endl;
        estimatedWeightsAreUpToDate = true;
        return estimatedWeights;
    }
}
