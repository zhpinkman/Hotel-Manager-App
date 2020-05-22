#include <iostream>
#include <iomanip>
#include <sstream>

#include "Hotel.hh"
#include "RoomService.hh"
#include "Constants.hh"
#include "User.hh"
#include "RatingCategoryWeightEstimator.hh"
#include "Utrip.hh"
#include "Utility.hh"

using namespace std;

Hotel::Hotel(const string &hotelId,
             string hotelName,
             size_t starRating,
             string hotelOverview,
             Amenities amenities,
             string city,
             Location location,
             string imageUrl,
             int numOfStandardRooms,
             int numOfDeluxeRooms,
             int numOfLuxuryRooms,
             int numOfPremiumRooms,
             double standardRoomPrice,
             double deluxeRoomPrice,
             double luxuryRoomPrice,
             double premiumRoomPrice)
    : hotelId(hotelId),
      hotelName(hotelName),
      starRating(starRating),
      hotel_overview(hotelOverview),
      amenities(amenities),
      city(city),
      location(location),
      image_url(imageUrl),
      roomService(numOfStandardRooms,
                  numOfDeluxeRooms,
                  numOfLuxuryRooms,
                  numOfPremiumRooms,
                  standardRoomPrice,
                  deluxeRoomPrice,
                  luxuryRoomPrice,
                  premiumRoomPrice)
{
}

void Hotel::print() const
{
    cout << hotelId << endl
              << hotelName << endl
              << "star: " << starRating << endl
              << "overview: " << hotel_overview << endl
              << "amenities: " << getAmenities() << endl
              << "city: " << city << endl;
    cout << fixed << setprecision(2);
    cout << "latitude: " << location.latitude << endl
              << "logitude: " << location.longitude << endl;

    cout.unsetf(ios_base::fixed);

    cout << "#rooms: "
              << roomService.getNumOfStandardRooms() << " "
              << roomService.getNumOfDeluxeRooms() << " "
              << roomService.getNumOfLuxuryRooms() << " "
              << roomService.getNumOfPremiumRooms() << endl;

    cout << "price: "
              << roomService.getPriceOfStandardRooms() << " "
              << roomService.getPriceOfDeluxeRooms() << " "
              << roomService.getPriceOfLuxuryRooms() << " "
              << roomService.getPriceOfPremiumRooms() << endl;
}

string Hotel::getAmenities() const
{
    string amenitiesString;
    for (size_t i = 0; i < amenities.size() - 1; i++)
        amenitiesString += amenities[i] + AMENITY_SEPARATOR;

    amenitiesString += amenities[amenities.size() - 1];
    return amenitiesString;
}

void Hotel::printBriefly() const
{
    cout << hotelId << " "
              << hotelName << " "
              << starRating << " "
              << city << " "
              << roomService.getTotalNumOfRooms() << " "
              << fixed << setprecision(2) << " "
              << roomService.getRoomsAveragePrice() << " "
              << averageRatings.getRating("overall") << " "
              << "-- "<<getPersonalRatingOfUser(Utrip::instance()->getLoggedInUser()) << " " //FOR TESTING PURPOSES ONLY
              << endl;
    cout.unsetf(ios_base::fixed);
}

bool Hotel::idsMatches(const string &_hotelId) const
{
    return hotelId == _hotelId;
}

double Hotel::getPersonalRatingOfUser(User* user) const
{
    if (rates.find(user->getUsername()) != rates.end()) // if user has already rated this hotel
        return rates.at(user->getUsername()).getRating("overall");
    else if (user->getWeightsAreManual()) 
        return getAverageRatings().estimateOverallRatingUsingWeights(user->getManualWeights());
    else 
        return getAverageRatings().estimateOverallRatingUsingWeights(user->getEstimatedWeights());
}

void Hotel::addRating(User* user, const HotelRatings &addedRate) 
{
    rates[user->getUsername()] = addedRate;
    user->invalidateEstimatedWeights();
}
