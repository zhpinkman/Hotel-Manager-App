#include <iostream>
#include "Hotel.hh"
#include "RoomService.hh"
#include "Constants.hh"

Hotel::Hotel(const std::string &hotelId,
             std::string hotelName,
             std::uint8_t hotelRating,
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
      hotelRating(hotelRating),
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

void Hotel::print() const /// TODO : use stringstream
{
    std::string hotel_description;
    hotel_description += hotelId + ENTER;
    hotel_description += hotelName + ENTER;
    hotel_description += "star: " + std::to_string(hotelRating) + ENTER;
    hotel_description += "overview: " + hotel_overview + ENTER;
    hotel_description += "amenities: " + getAmenities() + ENTER;
    hotel_description += "city: " + city.cityName + ENTER;
    hotel_description += "latitude: " + std::to_string(city.latitude) + ENTER;
    hotel_description += "logitude: " + std::to_string(city.longitude) + ENTER;
    hotel_description += "#rooms: " + std::to_string(roomService.getNumOfStandardRooms()) + SPACE +
                         std::to_string(roomService.getNumOfDeluxeRooms()) + SPACE +
                         std::to_string(roomService.getNumOfLuxuryRooms()) + SPACE +
                         std::to_string(roomService.getNumOfPremiumRooms()) + ENTER;
    hotel_description += "price: " + std::to_string(roomService.getPriceOfStandardRooms()) + SPACE +
                         std::to_string(roomService.getPriceOfDeluxeRooms()) + SPACE +
                         std::to_string(roomService.getPriceOfLuxuryRooms()) + SPACE +
                         std::to_string(roomService.getPriceOfPremiumRooms()) + ENTER;
    std::cout << hotel_description << std::endl;
}

std::string Hotel::getAmenities() const
{
    std::string amenitiesString;
    for (size_t i = 0; i < amenities.size() - 1; i++)
    {
        amenitiesString += amenities[i] + AMENITY_SEPARATOR;
    }
    amenitiesString += amenities[amenities.size() - 1];
    return amenitiesString;
}

void Hotel::printBriefly() const
{
    std::string hotel_description;
    hotel_description += hotelId + SPACE;
    hotel_description += hotelName + SPACE;
    hotel_description += std::to_string(hotelRating) + SPACE;
    hotel_description += city.cityName + SPACE;
    hotel_description += std::to_string(roomService.getTotalNumOfRooms()) + SPACE;
    hotel_description += std::to_string(roomService.getRoomsAveragePrice()) + SPACE;
    std::cout << hotel_description << std::endl;
}

bool Hotel::idsMatches(const std::string &_hotelId) const
{
    return hotelId == _hotelId;
}
