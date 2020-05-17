#include "HotelRatings.hh"
#include <exception>
#include <string>
#include <algorithm>

using namespace std;

double HotelRatings::uninitialized = -1;
std::vector<std::string> HotelRatings::categories = {"location", "cleanliness",
	"staff", "facilities", "value_for_money", "overall"};

HotelRatings::HotelRatings() {
	for (string category : categories)
		ratings[category] = uninitialized;
}

HotelRatings::HotelRatings(double location, double cleanliness, double staff,
 double facilities, double value_for_money, double overall) {
	ratings["location"] = location;
	ratings["cleanliness"] = cleanliness;
	ratings["staff"] = staff;
	ratings["facilities"] = facilities;
	ratings["value_for_money"] = value_for_money;
	ratings["overall"] = overall;
}

double HotelRatings::getRating(string category) const {
	if (ratings.find(category) != ratings.end()) {
		if (ratings.at(category) != uninitialized)
			return ratings.at(category);
		else 
			throw logic_error("getRating: requesting access to uninitialized category:" + category);
	}
	throw invalid_argument("getRating: Invalid category:" + category);
}

void HotelRatings::setRating(string category, double value) {
	if (ratings.find(category) != ratings.end()) {
		if (value >= 1 && value <= 5) 
			ratings[category] = value;
		else 
			throw invalid_argument("setRating: Invalid value:" + to_string(value));
	} else 
		throw invalid_argument("setRating: Invalid category:" + category);
}


bool HotelRatings::isInitialized() const {
    return std::all_of(categories.begin(), categories.end(),
		[this](string category){return ratings.at(category)!=uninitialized;});
}
