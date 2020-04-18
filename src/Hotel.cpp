#include <iostream>
#include "../includes/Hotel.hpp"
#include "../includes/Room_service.hpp"
#include "../includes/constants.hpp"

Hotel::Hotel(const std::string &hotelId, std::string hotelName, int hotelRating, std::string hotelOverview,
             Amenities amenities, City city, std::string imageUrl)
        : hotel_id(hotelId), hotel_name(hotelName), hotel_rating(hotelRating), hotel_overview(hotelOverview),
          amenities(amenities), city(city), image_url(imageUrl) {
    room_service = new Room_service();
}

void Hotel::print() {
    std::string hotel_description;
    hotel_description += "id: " + hotel_id + ENTER;
    hotel_description += "name: " + hotel_name + ENTER;
    hotel_description += "star: " + std::to_string(hotel_rating) + ENTER;
    hotel_description += "overview: " + hotel_overview + ENTER;
    hotel_description += "amenities: " + getAmenities() + ENTER;
    hotel_description += "city: " + city.city_name + ENTER;
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
    hotel_description += "id: " + hotel_id + SPACE;
    hotel_description += "name: " + hotel_name + SPACE;
    hotel_description += "star: " + std::to_string(hotel_rating) + SPACE;
    hotel_description += "city: " + city.city_name + SPACE;
//    todo other attributes
    std::cout << hotel_description << std::endl;
}
