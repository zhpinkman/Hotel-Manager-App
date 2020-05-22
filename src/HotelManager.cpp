#include "HotelManager.hh"
#include "Constants.hh"
#include "Hotel.hh"
#include "Utility.hh"
#include "Location.hh"
#include <iostream>

using namespace std;
using namespace utility;

HotelManager::HotelManager(const RAW_DATA_LIST &hotelsRawData)
{
    for (size_t i = 1; i < hotelsRawData.size(); i++)
    {
        Hotel *hotel = constructHotelFromHotelRawData(hotelsRawData[i]);
        hotels.emplace(hotel->getId(), hotel);
    }
}

Hotel *HotelManager::constructHotelFromHotelRawData(const RAW_DATA hotelRawData)
{
    Amenities amenities = utility::split_by_char(hotelRawData[AMENITIES_ARG_INDEX], AMENITY_SEPARATOR);

    return new Hotel(hotelRawData[HOTEL_ID_ARG_INDEX],
                     hotelRawData[HOTEL_NAME_ARG_INDEX],
                     static_cast<std::uint8_t>(std::stoi(hotelRawData[HOTEL_RATING_ARG_INDEX])),
                     hotelRawData[HOTEL_OVERVIEW_ARG_INDEX],
                     amenities,
                     hotelRawData[CITY_ARG_INDEX],
                     Location(std::stod(hotelRawData[LATITUDE_ARG_INDEX]),
                              std::stod(hotelRawData[LONGITUDE_ARG_INDEX])),
                     hotelRawData[HOTEL_IMAGE_ARG_INDEX],
                     std::stoi(hotelRawData[NUM_OF_STANDARD_ROOMS_ARG_INDEX]),
                     std::stoi(hotelRawData[NUM_OF_DELUXE_ROOMS_ARG_INDEX]),
                     std::stoi(hotelRawData[NUM_OF_LUXURY_ROOMS_ARG_INDEX]),
                     std::stoi(hotelRawData[NUM_OF_PREMIUM_ROOMS_ARG_INDEX]),
                     std::stoi(hotelRawData[PRICE_OF_STANDARD_ROOMS_ARG_INDEX]),
                     std::stoi(hotelRawData[PRICE_OF_DELUXE_ROOMS_ARG_INDEX]),
                     std::stoi(hotelRawData[PRICE_OF_LUXURY_ROOMS_ARG_INDEX]),
                     std::stoi(hotelRawData[PRICE_OF_PREMIUM_ROOMS_ARG_INDEX]));
}


void HotelManager::importRatings(const RAW_DATA_LIST ratingsData) 
{
    for (int i = 1; i < ratingsData.size(); i++) 
    {   
        string hotelId = ratingsData[i][0];
        hotels[hotelId]->setAverageRatings(HotelRatings(
            extractFromString<double>(ratingsData[i][1]),
            extractFromString<double>(ratingsData[i][2]),
            extractFromString<double>(ratingsData[i][3]),
            extractFromString<double>(ratingsData[i][4]),
            extractFromString<double>(ratingsData[i][5]),
            extractFromString<double>(ratingsData[i][6])
        ));
    }   
}
