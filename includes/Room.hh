#pragma once

#include <vector>

struct ReservationTime
{
    int arrivalTime;
    int departureTime;
};

class Room
{
private:
    std::vector<ReservationTime> reservationTimes;

public:
    Room();
};
