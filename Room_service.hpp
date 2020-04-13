#ifndef __ROOM_SERVICE_H__
#define __ROOM_SERVICE_H__ __ROOM_SERVICE_H__

#include "Room.hpp"

#include <vector>

typedef std::vector<Room> Rooms;

class Room_service {
private:
  Rooms rooms;

public:
  Room_service(/* args */);
  ~Room_service();
};

Room_service::Room_service(/* args */) {}

Room_service::~Room_service() {}

#endif // MACRO
