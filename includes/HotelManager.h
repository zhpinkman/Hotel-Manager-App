//
// Created by zhivar on 4/18/20.
//

#ifndef UT_AP_S99_FINAL_HOTELMANAGER_H
#define UT_AP_S99_FINAL_HOTELMANAGER_H



#include <vector>
#include <string>
#include "../includes/constants.hpp"

class Hotel;

class HotelManager {
public:
    HotelManager(const RAW_DATA_LIST &hotelsRawData);
    Hotel *constructHotelFromHotelRawData(const RAW_DATA hotelRawData);
private:
    std::vector<Hotel*> hotels;
};



#endif //UT_AP_S99_FINAL_HOTELMANAGER_H
