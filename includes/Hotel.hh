#pragma once

#include <string>
#include <vector>
#include "Constants.hh"

class RoomService;

class Hotel
{
public:
    Hotel(const std::string &hotelId, std::string hotelName, int hotelRating, std::string hotelOverview,
          Amenities amenities, City city, std::string imageUrl, int numOfStandardRooms,
          int numOfDeluxeRooms, int numOfLuxuryRooms, int numOfPremiumRooms,
          double standardRoomPrice, double deluxeRoomPrice, double luxuryRoomPrice,
          double premiumRoomPrice);
    void print() const;
    std::string getAmenities() const;

    std::string getId() const
    {
        return hotelId;
    };

    void printBriefly() const;

    bool idsMatches(const std::string &hotelId) const;

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
