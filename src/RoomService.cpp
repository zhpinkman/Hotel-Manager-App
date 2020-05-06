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
    std::size_t totalPrice = 0;
    std::size_t roomTypes = 0;

    if (numOfStandardRooms)
    {
        totalPrice += standardRoomPrice;
        roomTypes += 1;
    }
    if (numOfDeluxeRooms)
    {
        totalPrice += deluxeRoomPrice;
        roomTypes += 1;
    }
    if (numOfLuxuryRooms)
    {
        totalPrice += luxuryRoomPrice;
        roomTypes += 1;
    }
    if (numOfPremiumRooms)
    {
        totalPrice += premiumRoomPrice;
        roomTypes += 1;
    }

    if (!roomTypes)
        throw new std::runtime_error("No Room Types?");

    return totalPrice / roomTypes;
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