#ifndef __ROOM_SERVICE_H__
#define __ROOM_SERVICE_H__ __ROOM_SERVICE_H__

#include <vector>

class Room;

typedef std::vector<Room *> Rooms;

class Room_service {
private:
  Rooms rooms;

public:
  Room_service(/* args */);
};

#endif // MACRO
