#ifndef __HOTEL_H__
#define __HOTEL_H__ __HOTEL_H__

#include <string>
#include <vector>
#include "../includes/constants.hpp"


class Room_service;



class Hotel {
public:
    Hotel(const std::string &hotelId, std::string hotelName, int hotelRating, std::string hotelOverview,
          Amenities amenities, City city, std::string imageUrl);
    void print();
    std::string getAmenities();

    void printBriefly();

private:
    std::string hotel_id;
    std::string hotel_name;
    int hotel_rating;
    std::string hotel_overview;
    Amenities amenities;
    City city;
    std::string image_url;

  Room_service *room_service;
};

#endif