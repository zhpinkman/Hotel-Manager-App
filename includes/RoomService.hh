#pragma once
#include <vector>
#include <cstdlib>

class Room;

typedef std::vector<Room *> RoomList;

class RoomService
{
private:
  RoomList standardRooms;
  RoomList deluxeRooms;
  RoomList luxuryRooms;
  RoomList premiumRooms;
  std::size_t standardRoomPrice;
  std::size_t deluxeRoomPrice;
  std::size_t luxuryRoomPrice;
  std::size_t premiumRoomPrice;

public:
  RoomService(std::size_t numOfStandardRooms,
              std::size_t numOfDeluxeRooms,
              std::size_t numOfLuxuryRooms,
              std::size_t numOfPremiumRooms,
              std::size_t standardRoomPrice,
              std::size_t deluxeRoomPrice,
              std::size_t luxuryRoomPrice,
              std::size_t premiumRoomPrice);
  std::size_t getTotalNumOfRooms() const;
  std::size_t getRoomsAveragePrice() const;

  std::size_t getNumOfStandardRooms() const;
  std::size_t getNumOfDeluxeRooms() const;
  std::size_t getNumOfLuxuryRooms() const;
  std::size_t getNumOfPremiumRooms() const;

  std::size_t getPriceOfStandardRooms() const;
  std::size_t getPriceOfDeluxeRooms() const;
  std::size_t getPriceOfLuxuryRooms() const;
  std::size_t getPriceOfPremiumRooms() const;
};
