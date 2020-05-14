#pragma once

#include <utility>
#include <vector>

#include "Hotel.hh"

class Filter {
public:
  std::vector<Hotel*> apply(std::vector<Hotel*> hotels) const;
  virtual bool accept(Hotel* hotel) const = 0;
};

class CityFilter : public Filter {
public:
  virtual bool accept(Hotel* hotel) const;
  CityFilter(std::string city);
private:
  std::string city;
};


class StarRatingFilter: public Filter {
public:
  virtual bool accept(Hotel* hotel) const;
  StarRatingFilter(uint minStarRating, uint maxStarRating);
private:
  uint minStarRating, maxStarRating;
};

class AveragePriceFilter: public Filter {
public:
  virtual bool accept(Hotel* hotel) const;
  AveragePriceFilter(double minPrice, double maxPrice);
private:
  double minPrice, maxPrice;
};


class FreeRoomFilter: public Filter {
public:
  virtual bool accept(Hotel* hotel) const;
  FreeRoomFilter(RoomService::RoomType roomType, std::size_t quantity,
                 std::size_t arrivalTime, std::size_t departureTime);
private:
  RoomService::RoomType roomType;
  std::size_t quantity;
  std::size_t arrivalTime;
  std::size_t departureTime;
};


class HotelFilterManager {
public:
  void addFilter(Filter* filter);
  std::vector<Hotel*> filter(std::vector<Hotel*> hotels) const;
  ~HotelFilterManager();
private:
  std::vector<Filter*> filters;
};