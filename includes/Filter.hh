#pragma once

#include <string>
#include <utility>
#include <limits>
#include <sstream>

#include "Hotel.hh"

namespace Filter
{

template <typename... Args>
struct FilterManager : public Args...
{
  template <typename FilterType>
  FilterType &getFilter()
  {
    return static_cast<FilterType &>(*this);
  }

  template <typename FilterType>
  const FilterType &getFilter() const
  {
    return static_cast<const FilterType &>(*this);
  }
};

using HotelList = std::vector<Hotel *>;

struct CityFilter
{
  std::string city;
  bool isInitialized;

  CityFilter() : isInitialized(false)
  {
  }

  const HotelList filter(const HotelList &&input) const
  {
    if (!isInitialized)
      return input;

    HotelList resultSet;
    for (const auto &hotel : input)
      if (hotel->getCity() == city)
        resultSet.push_back(hotel);

    return resultSet;
  }

  void addFilter(const std::string &ExpectedCity)
  {
    isInitialized = true;
    city = ExpectedCity;
  }
};

struct StarsFilter
{
  std::uint8_t minStar;
  std::uint8_t maxStar;

  StarsFilter() : minStar(std::numeric_limits<std::uint8_t>::min()),
                  maxStar(std::numeric_limits<std::uint8_t>::max())
  {
  }

  const HotelList filter(const HotelList &&input) const
  {
    HotelList resultSet;
    for (const auto &hotel : input)
      if (hotel->getStar() <= maxStar && hotel->getStar() >= minStar)
        resultSet.push_back(hotel);

    return resultSet;
  }

  void addFilter(const std::string &minStarString,
                 const std::string &maxStarString)
  {
    const auto convertedMinStar = static_cast<std::uint8_t>(stoi(minStarString));
    const auto convertedMaxStar = static_cast<std::uint8_t>(stoi(maxStarString));

    constexpr std::uint8_t maxPossibleStar = 5;
    if (convertedMaxStar < convertedMinStar ||
        convertedMaxStar > maxPossibleStar)
      throw new BadRequestException();

    minStar = convertedMinStar;
    maxStar = convertedMaxStar;
  }
};

struct AveragePriceFilter
{
  double minPrice;
  double maxPrice;

  AveragePriceFilter() : minPrice(std::numeric_limits<double>::min()),
                         maxPrice(std::numeric_limits<double>::max())
  {
  }

  const HotelList filter(const HotelList &&input) const
  {
    HotelList resultSet;
    for (const auto &hotel : input)
      if (hotel->getRoomService().getRoomsAveragePrice() >= minPrice &&
          hotel->getRoomService().getRoomsAveragePrice() <= maxPrice)
        resultSet.push_back(hotel);

    return resultSet;
  }

  void addFilter(const std::string &minPriceString,
                 const std::string &maxPriceString)
  {
    const auto convertedMinPrice = static_cast<std::size_t>(stoi(minPriceString));
    const auto convertedMaxPrice = static_cast<std::size_t>(stoi(maxPriceString));

    if (convertedMaxPrice < convertedMinPrice)
      throw new BadRequestException();

    minPrice = convertedMinPrice;
    maxPrice = convertedMaxPrice;
  }
};

struct FreeRoomFilter
{
  bool isInitialized;
  RoomService::RoomType roomType;
  std::size_t quantity;
  std::size_t arrivalTime;
  std::size_t departureTime;

  FreeRoomFilter() : isInitialized(false)
  {
  }

  const HotelList filter(const HotelList &&input) const
  {
    if (!isInitialized)
      return input;

    HotelList resultSet;
    for (const auto &hotel : input)
      if (hotel->getRoomService().doesFreeRoomExists(roomType, quantity, arrivalTime, departureTime))
        resultSet.push_back(hotel);

    return resultSet;
  }

  template <typename ReturnValueType>
  static ReturnValueType extractFromString(const std::string &stringValue)
  {
    std::stringstream ss(stringValue);
    ReturnValueType result;
    ss >> result;
    return result;
  }

  void addFilter(const std::string &roomTypeString,
                 const std::string &quantityString,
                 const std::string &arrivalTimeString,
                 const std::string &departureTimeString)
  {
    isInitialized = true;
    roomType = RoomService::convertRoomType(roomTypeString);
    quantity = extractFromString<std::size_t>(quantityString);
    arrivalTime = extractFromString<std::size_t>(quantityString);
    departureTime = extractFromString<std::size_t>(quantityString);
  }
};

struct HotelFilterManager : public FilterManager<CityFilter,
                                                 StarsFilter,
                                                 AveragePriceFilter,
                                                 FreeRoomFilter>
{
  HotelList filter(HotelList &&hotels) const
  {
    const auto &cityFilter = this->getFilter<CityFilter>();
    const auto &starsFilter = this->getFilter<StarsFilter>();
    const auto &averagePriceFilter = this->getFilter<AveragePriceFilter>();
    const auto &freeRoomFilter = this->getFilter<FreeRoomFilter>();

    return freeRoomFilter.filter(
        averagePriceFilter.filter(
            starsFilter.filter(
                cityFilter.filter(std::forward<HotelList>(hotels)))));
  }

  template <typename FilterType, typename... Args>
  void addFilter(Args &&... args)
  {
    auto &filter = this->getFilter<FilterType>();
    filter.addFilter(std::forward<Args>(args)...);
  }
};

} // namespace Filter
