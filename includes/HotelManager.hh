#pragma once

#include <unordered_map>
#include <string>
#include "Constants.hh"
#include "Hotel.hh"
#include "Exception.hh"

class HotelManager
{
public:
    using HotelList = std::unordered_map<std::string, Hotel *>;

    HotelManager() = default;
    HotelManager(const RAW_DATA_LIST &hotelsRawData);
    Hotel *constructHotelFromHotelRawData(const RAW_DATA hotelRawData);

    const HotelList &getHotels() const
    {
        return hotels;
    }

    const Hotel *const getHotels(const std::string &id) const
    {
        if (hotels.find(id) == hotels.end())
            return nullptr;

        return hotels.at(id);
    }

    Hotel &getHotels(const std::string &id)
    {
        if (hotels.find(id) == hotels.end())
            throw new NotFoundException();

        return *hotels.at(id);
    }

    void getHotelById(const std::string &hotelId);

private:
    std::unordered_map<std::string, Hotel *> hotels;
};
