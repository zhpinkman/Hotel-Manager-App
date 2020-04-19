#include "../includes/RoomService.hpp"
#include "../includes/Room.h"



RoomService::RoomService(int numOfStandardRooms, int numOfDeluxeRooms, int numOfLuxuryRooms, int numOfPremiumRooms,
                         int standardRoomPrice, int deluxeRoomPrice, int luxuryRoomPrice,
                         int premiumRoomPrice)
        : standardRoomPrice(standardRoomPrice), deluxeRoomPrice(deluxeRoomPrice), luxuryRoomPrice(luxuryRoomPrice),
          premiumRoomPrice(premiumRoomPrice) {
    for (int i = 0; i < numOfStandardRooms; i++) {
        standardRooms.push_back(new Room());
    }
    for (int i = 0; i < numOfDeluxeRooms; i++) {
        deluxeRooms.push_back(new Room());
    }
    for (int i = 0; i < numOfLuxuryRooms; i++) {
        luxuryRooms.push_back(new Room());
    }
    for (int i = 0; i < numOfPremiumRooms; i++) {
        premiumRooms.push_back(new Room());
    }

}

int RoomService::getTotalNumOfRooms() {
    return standardRooms.size() + deluxeRooms.size() + luxuryRooms.size() + premiumRooms.size();
}

int RoomService::getRoomsAveragePrice() {
    int totalPrice = 0;
    int roomTypes = 0;
    if (standardRooms.size()) {
        totalPrice += standardRoomPrice;
        roomTypes += 1;
    }
    if (deluxeRooms.size()) {
        totalPrice += deluxeRoomPrice;
        roomTypes += 1;
    }
    if (luxuryRooms.size()){
        totalPrice += luxuryRoomPrice;
        roomTypes += 1;
    }
    if (premiumRooms.size()){
        totalPrice += premiumRoomPrice;
        roomTypes += 1;
    }
    int averagePrice = totalPrice / roomTypes;
    return averagePrice;
}

int RoomService::getNumOfStandardRooms() {
    return standardRooms.size();
}

int RoomService::getNumOfDeluxeRooms() {
    return deluxeRooms.size();
}

int RoomService::getNumOfLuxuryRooms() {
    return luxuryRooms.size();
}

int RoomService::getNumOfPremiumRooms() {
    return premiumRooms.size();
}

int RoomService::getPriceOfStandardRooms() {
    return standardRoomPrice;
}

int RoomService::getPriceOfDeluxeRooms() {
    return deluxeRoomPrice;
}

int RoomService::getPriceOfLuxuryRooms() {
    return luxuryRoomPrice;
}

int RoomService::getPriceOfPremiumRooms() {
    return premiumRoomPrice;
}