#pragma once

#include "Utility.hh"

#include <vector>
#include <string>
#include <unordered_map>

class HotelRatingWeights;

class HotelRatings
{
public:
	HotelRatings();
    HotelRatings(double location, double cleanliness, double staff,
    	double facilities, double value_for_money, double overall);
    double getRating(std::string category) const;
    void setRating(std::string category, double value);
    double estimateOverallRatingUsingWeights(const HotelRatingWeights& weights);
    bool isInitialized() const;

    static std::vector<std::string> categories;

    std::string toString() const;
private:
    utility::MapWithConstantKeys<std::string, double> ratings;
};

class HotelRatingWeights
{
public:
    HotelRatingWeights();
    HotelRatingWeights(double location, double cleanliness, double staff,
        double facilities, double value_for_money);
    double getWeight(std::string category) const;
    void setWeight(std::string category, double value);
    bool isInitialized() const;

    static std::vector<std::string> categories;

    std::string toString() const;
private:
    utility::MapWithConstantKeys<std::string, double> weights;
};