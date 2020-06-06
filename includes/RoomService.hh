#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <set>
#include <iostream>

#include "Exception.hh"

struct RoomService
{
  enum class RoomType
  {
    STANDARD,
    DELUXE,
    LUXURY,
    PREMIUM,
  };

  template <typename DateType = std::size_t>
  struct Reservation
  {
    Reservation(const std::size_t reservationId,
                const std::string &hotelId,
                const std::string &username,
                const RoomType roomType,
                const std::size_t quantity,
                const double price,
                const std::size_t arrivalTime,
                const std::size_t departureTime)
        : reservationId(reservationId),
          hotelId(hotelId),
          username(username),
          roomType(roomType),
          quantity(quantity),
          price(price),
          arrivalTime(arrivalTime),
          departureTime(departureTime)
    {
    }

    std::size_t reservationId;
    std::string hotelId;
    std::string username;
    RoomType roomType;
    std::size_t quantity;
    double price;
    DateType arrivalTime;
    DateType departureTime;
    std::set<std::size_t> roomIds;
  };

  using ReservationType = Reservation<>;
  using ReservationSet = std::vector<ReservationType>; // TODO can replace with set

private:
  std::size_t numOfStandardRooms;
  std::size_t numOfDeluxeRooms;
  std::size_t numOfLuxuryRooms;
  std::size_t numOfPremiumRooms;

  std::size_t standardRoomPrice;
  std::size_t deluxeRoomPrice;
  std::size_t luxuryRoomPrice;
  std::size_t premiumRoomPrice;

  ReservationSet reservations;

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
  double getRoomsAveragePrice() const;

  std::size_t getNumOfStandardRooms() const;
  std::size_t getNumOfDeluxeRooms() const;
  std::size_t getNumOfLuxuryRooms() const;
  std::size_t getNumOfPremiumRooms() const;

  std::size_t getPriceOfStandardRooms() const;
  std::size_t getPriceOfDeluxeRooms() const;
  std::size_t getPriceOfLuxuryRooms() const;
  std::size_t getPriceOfPremiumRooms() const;

  static std::string toString(const RoomService::RoomType roomType)
  {
    switch (roomType)
    {
    case RoomService::RoomType::STANDARD:
      return "standard";
    case RoomService::RoomType::DELUXE:
      return "deluxe";
    case RoomService::RoomType::LUXURY:
      return "luxury";
    case RoomService::RoomType::PREMIUM:
      return "premium";
    default:
      throw new BadRequestException();
    }
  }

  static RoomType convertRoomType(const std::string &roomTypeName)
  {
    if (roomTypeName == "standard")
      return RoomService::RoomType::STANDARD;
    else if (roomTypeName == "deluxe")
      return RoomService::RoomType::DELUXE;
    else if (roomTypeName == "luxury")
      return RoomService::RoomType::LUXURY;
    else if (roomTypeName == "premium")
      return RoomService::RoomType::PREMIUM;

    throw new BadRequestException();
  }

  std::size_t calculateReservePrice(const RoomType roomType, const std::size_t quantity) const
  {
    std::size_t unitPrice = 0;
    switch (roomType)
    {
    case RoomType::STANDARD:
      unitPrice = standardRoomPrice;
      break;
    case RoomType::DELUXE:
      unitPrice = deluxeRoomPrice;
      break;
    case RoomType::LUXURY:
      unitPrice = luxuryRoomPrice;
      break;
    case RoomType::PREMIUM:
      unitPrice = premiumRoomPrice;
      break;
    default:
      throw new BadRequestException();
    }

    return quantity * unitPrice;
  }

  ReservationSet findInterferingReservations(const RoomType roomType,
                                             const std::size_t arrivalTime,
                                             const std::size_t departureTime) const
  {
    ReservationSet interferingReservations;

    for (const auto &reservation : reservations)
      if ((reservation.roomType == roomType) &&
          ((reservation.departureTime >= arrivalTime) ||
           (reservation.arrivalTime <= departureTime)))
        interferingReservations.push_back(reservation);

    return interferingReservations;
  }

  std::size_t findRoomTypeQuantity(const RoomType roomType) const
  {
    switch (roomType)
    {
    case RoomType::STANDARD:
      return numOfStandardRooms;
      break;
    case RoomType::DELUXE:
      return numOfDeluxeRooms;
      break;
    case RoomType::LUXURY:
      return numOfLuxuryRooms;
      break;
    case RoomType::PREMIUM:
      return numOfPremiumRooms;
      break;
    default:
      return 0;
    }
  }

  bool doesFreeRoomExists(const RoomType roomType,
                          const std::size_t quantity,
                          const std::size_t arrivalTime,
                          const std::size_t departureTime) const
  {
    std::size_t numOfOccupiedRooms = 0;

    const auto interferingReservations = findInterferingReservations(roomType, arrivalTime, departureTime);
    for (const auto &reservation : interferingReservations)
      numOfOccupiedRooms += reservation.quantity;

    return (findRoomTypeQuantity(roomType) - numOfOccupiedRooms) >= quantity;
  }

  ReservationType reserve(const std::size_t reservationId,
                          const std::string &hotelId,
                          const std::string &username,
                          const RoomType roomType,
                          const std::size_t quantity,
                          const double price,
                          const std::size_t arrivalTime,
                          const std::size_t departureTime)
  {
    ReservationType newReservation(reservationId, hotelId, username, roomType, quantity, price, arrivalTime,
                                   departureTime);
    const auto interferingReservations = findInterferingReservations(roomType, arrivalTime, departureTime);

    std::set<std::size_t> occupiedRoomIds;
    for (const auto &reservation : interferingReservations)
      occupiedRoomIds.insert(reservation.roomIds.begin(), reservation.roomIds.end()); // Could be refactored with std::transform

    for (std::size_t id = 1; id <= findRoomTypeQuantity(roomType) && newReservation.roomIds.size() < quantity; id++)
      if (occupiedRoomIds.find(id) == occupiedRoomIds.end())
        newReservation.roomIds.insert(id);

    reservations.push_back(newReservation);
    return newReservation;
  }

  ReservationSet getUserReservations(const std::string &username) const
  {
    ReservationSet userReservations;

    for (const auto &reservation : reservations)
      userReservations.push_back(reservation);

    return userReservations;
  }

  void deleteReservation(const std::size_t reservationId, const std::string &username)
  {
    for (std::size_t i = 0; i < reservations.size(); ++i)
      if (username == reservations[i].username &&
          reservationId == reservations[i].reservationId)
      {
        reservations.erase(reservations.begin() + i);
        return;
      }

    throw new NotFoundException();
  }
};
