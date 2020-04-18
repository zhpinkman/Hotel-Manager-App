#include <iostream>
#include "../includes/Hotel.hpp"
#include "../includes/Room_service.hpp"
#include "../includes/constants.hpp"

Hotel::Hotel(const std::string &hotelId, std::string hotelName, int hotelRating, std::string hotelOverview,
             Amenities amenities, City city, std::string imageUrl)
        : hotelId(hotelId), hotelName(hotelName), hotelRating(hotelRating), hotel_overview(hotelOverview),
          amenities(amenities), city(city), image_url(imageUrl) {
    room_service = new Room_service();
}

void Hotel::print() {
    std::string hotel_description;
    hotel_description += "id: " + hotelId + ENTER;
    hotel_description += "name: " + hotelName + ENTER;
    hotel_description += "star: " + std::to_string(hotelRating) + ENTER;
    hotel_description += "overview: " + hotel_overview + ENTER;
    hotel_description += "amenities: " + getAmenities() + ENTER;
    hotel_description += "city: " + city.cityName + ENTER;
    hotel_description += "latitude: " + std::to_string(city.latitude) + ENTER;
    hotel_description += "logitude: " + std::to_string(city.longitude) + ENTER;
    std::cout << hotel_description << std::endl;
}


std::string Hotel::getAmenities() {
    std::string amenitiesString;
    for (size_t i = 0; i < amenities.size() - 1; i++) {
        amenitiesString += amenities[i] + AMENITY_SEPARATOR;
    }
    amenitiesString += amenities[amenities.size() - 1];
    return amenitiesString;
}

void Hotel::printBriefly() {
    std::string hotel_description;
    hotel_description += "id: " + hotelId + SPACE;
    hotel_description += "name: " + hotelName + SPACE;
    hotel_description += "star: " + std::to_string(hotelRating) + SPACE;
    hotel_description += "city: " + city.cityName + SPACE;
//    todo other attributes
    std::cout << hotel_description << std::endl;
}

bool Hotel::idsMatches(const std::string &_hotelId) {
    return hotelId == _hotelId;
}
