#include <iostream>
#include <iomanip>
#include <sstream>

#include "Hotel.hh"
#include "RoomService.hh"
#include "Constants.hh"
#include "City.hh"

Hotel::Hotel(const std::string &hotelId,
             std::string hotelName,
             std::size_t starRating,
             std::string hotelOverview,
             Amenities amenities,
             City city,
             std::string imageUrl,
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
    std::cout << hotelId << std::endl
              << hotelName << std::endl
              << "star: " << starRating << std::endl
              << "overview: " << hotel_overview << std::endl
              << "amenities: " << getAmenities() << std::endl
              << "city: " << city.cityName << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "latitude: " << city.latitude << std::endl
              << "logitude: " << city.longitude << std::endl;

    std::cout.unsetf(std::ios_base::fixed);

    std::cout << "#rooms: "
              << roomService.getNumOfStandardRooms() << " "
              << roomService.getNumOfDeluxeRooms() << " "
              << roomService.getNumOfLuxuryRooms() << " "
              << roomService.getNumOfPremiumRooms() << std::endl;

    std::cout << "price: "
              << roomService.getPriceOfStandardRooms() << " "
              << roomService.getPriceOfDeluxeRooms() << " "
              << roomService.getPriceOfLuxuryRooms() << " "
              << roomService.getPriceOfPremiumRooms() << std::endl;
}

std::string Hotel::getAmenities() const
{
    std::string amenitiesString;
    for (size_t i = 0; i < amenities.size() - 1; i++)
        amenitiesString += amenities[i] + AMENITY_SEPARATOR;

    amenitiesString += amenities[amenities.size() - 1];
    return amenitiesString;
}

void Hotel::printBriefly() const
{
    std::cout << hotelId << " "
              << starRating << " "
              << city.cityName << " "
              << std::to_string(roomService.getTotalNumOfRooms()) << " "
              << std::to_string(static_cast<std::size_t>(roomService.getRoomsAveragePrice())) << " "
              << std::endl;
}

bool Hotel::idsMatches(const std::string &_hotelId) const
{
    return hotelId == _hotelId;
}
