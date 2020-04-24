#ifndef __HOTEL_H__
#define __HOTEL_H__ __HOTEL_H__

#include <string>
#include <vector>
#include "../includes/Constants.hh"

class RoomService;

class Hotel
{
public:
    Hotel(const std::string &hotelId, std::string hotelName, int hotelRating, std::string hotelOverview,
          Amenities amenities, City city, std::string imageUrl, int numOfStandardRooms,
          int numOfDeluxeRooms, int numOfLuxuryRooms, int numOfPremiumRooms,
          double standardRoomPrice, double deluxeRoomPrice, double luxuryRoomPrice,
          double premiumRoomPrice);
    void print();
    std::string getAmenities();

    void printBriefly();

    bool idsMatches(const std::string &hotelId);

private:
    std::string hotelId;
    std::string hotelName;
    int hotelRating;
    std::string hotel_overview;
    Amenities amenities;
    City city;
    std::string image_url;
    RoomService *roomService;
};

#endif