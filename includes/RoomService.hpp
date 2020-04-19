#ifndef __ROOM_SERVICE_H__
#define __ROOM_SERVICE_H__ __ROOM_SERVICE_H__

#include <vector>

class Room;

typedef std::vector<Room*> Rooms;

class RoomService {
private:
  Rooms standardRooms;
  Rooms deluxeRooms;
  Rooms luxuryRooms;
  Rooms premiumRooms;
  int standardRoomPrice;
  int deluxeRoomPrice;
  int luxuryRoomPrice;
  int premiumRoomPrice;

public:
  RoomService(int numOfStandardRooms, int numOfDeluxeRooms, int numOfLuxuryRooms, int numOfPremiumRooms,
              int standardRoomPrice, int deluxeRoomPrice, int luxuryRoomPrice,
              int premiumRoomPrice);
  int getTotalNumOfRooms();
  int getRoomsAveragePrice();
  int getNumOfStandardRooms();
  int getNumOfDeluxeRooms();
  int getNumOfLuxuryRooms();
  int getNumOfPremiumRooms();
  int getPriceOfStandardRooms();
  int getPriceOfDeluxeRooms();
  int getPriceOfLuxuryRooms();
  int getPriceOfPremiumRooms();
};

#endif // MACRO
