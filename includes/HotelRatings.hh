#pragma once

#include <vector>
#include <string>
#include <unordered_map>

class HotelRatings {
public:
	HotelRatings();
    HotelRatings(double location, double cleanliness, double staff,
    	double facilities, double value_for_money, double overall);
    double getRating(std::string category) const;
    void setRating(std::string category, double value);
    bool isInitialized() const;

    static std::vector<std::string> categories;
    
private:
    std::unordered_map<std::string, double> ratings;
    static double uninitialized;
};
