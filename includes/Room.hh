//
// Created by zhivar on 4/20/20.
//

#ifndef UT_AP_S99_FINAL_ROOM_H
#define UT_AP_S99_FINAL_ROOM_H

#include <vector>

struct ReservationTime {
    int arrivalTime;
    int departureTime;
};

class Room {
private:
    std::vector<ReservationTime> reservationTimes;
public:
    Room();
};

#endif //UT_AP_S99_FINAL_ROOM_H
