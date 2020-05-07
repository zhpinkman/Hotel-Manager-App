#include "RoomService.hh"

RoomService::RoomService(std::size_t numOfStandardRooms,
                         std::size_t numOfDeluxeRooms,
                         std::size_t numOfLuxuryRooms,
                         std::size_t numOfPremiumRooms,
                         std::size_t standardRoomPrice,
                         std::size_t deluxeRoomPrice,
                         std::size_t luxuryRoomPrice,
                         std::size_t premiumRoomPrice)
    : numOfStandardRooms(numOfStandardRooms),
      numOfDeluxeRooms(numOfDeluxeRooms),
      numOfLuxuryRooms(numOfLuxuryRooms),
      numOfPremiumRooms(numOfPremiumRooms),
      standardRoomPrice(standardRoomPrice),
      deluxeRoomPrice(deluxeRoomPrice),
      luxuryRoomPrice(luxuryRoomPrice),
      premiumRoomPrice(premiumRoomPrice)
{
}

std::size_t RoomService::getTotalNumOfRooms() const
{
    return numOfStandardRooms + numOfDeluxeRooms + numOfLuxuryRooms + numOfPremiumRooms;
}

double RoomService::getRoomsAveragePrice() const
{
    double totalPrice = 0;
    std::size_t roomTypes = 0;

    if (standardRoomPrice)
    {
        totalPrice += standardRoomPrice;
        roomTypes += 1;
    }
    if (deluxeRoomPrice)
    {
        totalPrice += deluxeRoomPrice;
        roomTypes += 1;
    }
    if (luxuryRoomPrice)
    {
        totalPrice += luxuryRoomPrice;
        roomTypes += 1;
    }
    if (premiumRoomPrice)
    {
        totalPrice += premiumRoomPrice;
        roomTypes += 1;
    }

    double averagePrice;
    if (roomTypes != 0)
        averagePrice = totalPrice / roomTypes;
    else
        averagePrice = 0;

    return averagePrice;
}

std::size_t RoomService::getNumOfStandardRooms() const
{
    return numOfStandardRooms;
}

std::size_t RoomService::getNumOfDeluxeRooms() const
{
    return numOfDeluxeRooms;
}

std::size_t RoomService::getNumOfLuxuryRooms() const
{
    return numOfLuxuryRooms;
}

std::size_t RoomService::getNumOfPremiumRooms() const
{
    return numOfPremiumRooms;
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