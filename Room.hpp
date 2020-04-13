#ifndef __ROOM_H__
#define __ROOM_H__ __ROOM_H__

#include "Reservation_time.hpp"

#include <vector>

typedef std::vector<Reservation_time> Room_reservations;

class Room {
private:
  double room_id;
  double room_price;
  Room_reservations room_reservations;

public:
  Room(double _room_id, double room_price);
  ~Room();
};

Room::Room(double _room_id, double _room_price) {
  room_id = _room_id;
  room_price = _room_price;
}

Room::~Room() {}

#endif //