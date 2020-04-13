#ifndef __ROOM_H__
#define __ROOM_H__ __ROOM_H__

#include <vector>

class Reservation_time;

typedef std::vector<Reservation_time *> Room_reservations;

class Room {
private:
  double room_id;
  double room_price;
  Room_reservations room_reservations;

public:
  Room(double _room_id, double room_price);
};

#endif //