#include "HotelRatings.hh"
#include "Utility.hh"

#include <exception>
#include <string>
#include <algorithm>
#include <iostream>
#include <typeinfo>

using namespace std;

// ======================== HotelRatings ==========================: 

std::vector<std::string> HotelRatings::categories = {"location", "cleanliness",
	"staff", "facilities", "value_for_money", "overall"};

HotelRatings::HotelRatings() : ratings(categories) {}

HotelRatings::HotelRatings(double location, double cleanliness, double staff,
 double facilities, double value_for_money, double overall) 
 	: ratings(categories) 
{
	ratings.set("location", location);
	ratings.set("cleanliness", cleanliness);
	ratings.set("staff", staff);
	ratings.set("facilities", facilities);
	ratings.set("value_for_money", value_for_money);
	ratings.set("overall", overall);
}

double HotelRatings::getRating(string category) const {return ratings.get(category);}

void HotelRatings::setRating(string category, double value) {ratings.set(category, value);}

bool HotelRatings::isInitialized() const {return ratings.isInitialized();}


// ======================== HotelRatingWeights ==========================: 

std::vector<std::string> HotelRatingWeights::categories = {"location", "cleanliness",
	"staff", "facilities", "value_for_money"};

HotelRatingWeights::HotelRatingWeights() : weights(categories) {}

HotelRatingWeights::HotelRatingWeights(double location, double cleanliness, double staff,
	double facilities, double value_for_money) 
	: weights(categories) 
{
	weights.set("location", location);
	weights.set("cleanliness", cleanliness);
	weights.set("staff", staff);
	weights.set("facilities", facilities);
	weights.set("value_for_money", value_for_money);
}

double HotelRatingWeights::getWeight(string category) const {return weights.get(category);}
void HotelRatingWeights::setWeight(string category, double value) {weights.set(category, value);}
bool HotelRatingWeights::isInitialized() const {return weights.isInitialized();}