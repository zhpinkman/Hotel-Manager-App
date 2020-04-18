//
// Created by zhivar on 4/18/20.
//



#include "../includes/HotelManager.h"
#include "../includes/constants.hpp"
#include "../includes/Hotel.hpp"
#include "../includes/Tools.hpp"
#include <iostream>

HotelManager::HotelManager(const RAW_DATA_LIST &hotelsRawData) {
    for (size_t i = 1;i < hotelsRawData.size(); i++) {
        Hotel* hotel = constructHotelFromHotelRawData(hotelsRawData[i]);
        hotels.push_back(hotel);
    }
    hotels[0]->print();
}


Hotel *HotelManager::constructHotelFromHotelRawData(const RAW_DATA hotelRawData) {
    Amenities amenities = Tools::split_by_char(hotelRawData[AMENITIES_ARG_INDEX], AMENITY_SEPARATOR);
    City city = City(hotelRawData[CITY_ARG_INDEX], std::stod(
            hotelRawData[LATITUDE_ARG_INDEX]), std::stod(hotelRawData[LONGITUDE_ARG_INDEX]));
    return new Hotel(hotelRawData[HOTEL_ID_ARG_INDEX], hotelRawData[HOTEL_NAME_ARG_INDEX],
            std::stoi(hotelRawData[HOTEL_RATING_ARG_INDEX]),
            hotelRawData[HOTEL_OVERVIEW_ARG_INDEX], amenities, city, hotelRawData[HOTEL_IMAGE_ARG_INDEX]);
}

