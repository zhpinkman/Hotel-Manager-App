#include "../includes/HotelManager.hh"
#include "../includes/Constants.hh"
#include "../includes/Hotel.hh"
#include "../includes/Tools.hh"
#include <iostream>

HotelManager::HotelManager(const RAW_DATA_LIST &hotelsRawData)
{
    for (size_t i = 1; i < hotelsRawData.size(); i++)
    {
        Hotel *hotel = constructHotelFromHotelRawData(hotelsRawData[i]);
        hotels.push_back(hotel);
    }
}

Hotel *HotelManager::constructHotelFromHotelRawData(const RAW_DATA hotelRawData)
{
    Amenities amenities = Tools::split_by_char(hotelRawData[AMENITIES_ARG_INDEX], AMENITY_SEPARATOR);
    City city = City(hotelRawData[CITY_ARG_INDEX], std::stod(hotelRawData[LATITUDE_ARG_INDEX]), std::stod(hotelRawData[LONGITUDE_ARG_INDEX]));
    return new Hotel(hotelRawData[HOTEL_ID_ARG_INDEX], hotelRawData[HOTEL_NAME_ARG_INDEX],
                     std::stoi(hotelRawData[HOTEL_RATING_ARG_INDEX]),
                     hotelRawData[HOTEL_OVERVIEW_ARG_INDEX], amenities, city, hotelRawData[HOTEL_IMAGE_ARG_INDEX],
                     std::stoi(hotelRawData[NUM_OF_STANDARD_ROOMS_ARG_INDEX]), std::stoi(hotelRawData[NUM_OF_DELUXE_ROOMS_ARG_INDEX]),
                     std::stoi(hotelRawData[NUM_OF_LUXURY_ROOMS_ARG_INDEX]), std::stoi(hotelRawData[NUM_OF_PREMIUM_ROOMS_ARG_INDEX]),
                     std::stoi(hotelRawData[PRICE_OF_STANDARD_ROOMS_ARG_INDEX]), std::stoi(hotelRawData[PRICE_OF_DELUXE_ROOMS_ARG_INDEX]),
                     std::stoi(hotelRawData[PRICE_OF_LUXURY_ROOMS_ARG_INDEX]), std::stoi(hotelRawData[PRICE_OF_PREMIUM_ROOMS_ARG_INDEX]));
}

void HotelManager::getHotels()
{
    for (auto hotel : hotels)
    {
        hotel->printBriefly();
    }
}

void HotelManager::getHotelById(const std::string &hotelId)
{
    for (auto hotel : hotels)
    {
        if (hotel->idsMatches(hotelId))
        {
            hotel->print();
        }
    }
}
