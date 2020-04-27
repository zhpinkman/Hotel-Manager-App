#include "RoomService.hh"
#include "Room.hh"

RoomService::RoomService(std::size_t numOfStandardRooms, std::size_t numOfDeluxeRooms, std::size_t numOfLuxuryRooms, std::size_t numOfPremiumRooms,
                         std::size_t standardRoomPrice, std::size_t deluxeRoomPrice, std::size_t luxuryRoomPrice,
                         std::size_t premiumRoomPrice)
    : standardRoomPrice(standardRoomPrice), deluxeRoomPrice(deluxeRoomPrice), luxuryRoomPrice(luxuryRoomPrice),
      premiumRoomPrice(premiumRoomPrice)
{
    for (std::size_t i = 0; i < numOfStandardRooms; i++)
    {
        standardRooms.push_back(new Room());
    }
    for (std::size_t i = 0; i < numOfDeluxeRooms; i++)
    {
        deluxeRooms.push_back(new Room());
    }
    for (std::size_t i = 0; i < numOfLuxuryRooms; i++)
    {
        luxuryRooms.push_back(new Room());
    }
    for (std::size_t i = 0; i < numOfPremiumRooms; i++)
    {
        premiumRooms.push_back(new Room());
    }
}

std::size_t RoomService::getTotalNumOfRooms() const
{
    return standardRooms.size() + deluxeRooms.size() + luxuryRooms.size() + premiumRooms.size();
}

std::size_t RoomService::getRoomsAveragePrice() const
{
    std::size_t totalPrice = 0;
    std::size_t roomTypes = 0;
    if (standardRooms.size())
    {
        totalPrice += standardRoomPrice;
        roomTypes += 1;
    }
    if (deluxeRooms.size())
    {
        totalPrice += deluxeRoomPrice;
        roomTypes += 1;
    }
    if (luxuryRooms.size())
    {
        totalPrice += luxuryRoomPrice;
        roomTypes += 1;
    }
    if (premiumRooms.size())
    {
        totalPrice += premiumRoomPrice;
        roomTypes += 1;
    }
    std::size_t averagePrice = totalPrice / roomTypes;
    return averagePrice;
}

std::size_t RoomService::getNumOfStandardRooms() const
{
    return standardRooms.size();
}

std::size_t RoomService::getNumOfDeluxeRooms() const
{
    return deluxeRooms.size();
}

std::size_t RoomService::getNumOfLuxuryRooms() const
{
    return luxuryRooms.size();
}

std::size_t RoomService::getNumOfPremiumRooms() const
{
    return premiumRooms.size();
}

std::size_t RoomService::getPriceOfStandardRooms() const
{
    return standardRoomPrice;
}

std::size_t RoomService::getPriceOfDeluxeRooms() const
{
    return deluxeRoomPrice;
}

std::size_t RoomService::getPriceOfLuxuryRooms() const
{
    return luxuryRoomPrice;
}

std::size_t RoomService::getPriceOfPremiumRooms() const
{
    return premiumRoomPrice;
}