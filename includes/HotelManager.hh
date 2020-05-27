#pragma once

#include "Constants.hh"
#include "Hotel.hh"
#include "Exception.hh"

#include <unordered_map>
#include <string>

class HotelManager
{
public:
    using HotelList = std::unordered_map<std::string, Hotel *>;

    HotelManager() = default;
    HotelManager(const RAW_DATA_LIST &hotelsRawData);
    Hotel *constructHotelFromHotelRawData(const RAW_DATA hotelRawData);
    void importRatings(const RAW_DATA_LIST ratingsData);

    const HotelList &getHotels() const
    {
        return hotels;
    }

    const Hotel *const getHotel(const std::string &id) const
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
    HotelList hotels;
};
