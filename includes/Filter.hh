#pragma once

#include <string>
#include <utility>

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

struct BasicFilter
{
  bool isInitialized;

  BasicFilter() : isInitialized(false)
  {
  }

  virtual const HotelList filter(const HotelList &&input) const = 0;
};

struct CityFilter
{
  std::string cityName;
  bool isInitialized;

  const HotelList filter(const HotelList &&input) const
  {
    if (!isInitialized)
      return input;

    HotelList resultSet;
    for (const auto &hotel : input)
      if (hotel->getCity().cityName == cityName)
        resultSet.push_back(hotel);

    return resultSet;
  }

  void addFilter(const std::string &ExpectedCityName)
  {
    isInitialized = true;
    cityName = ExpectedCityName;
  }
};

struct StarsFilter : public BasicFilter
{
  const HotelList filter(const HotelList &&input) const
  {
    return input; /// TODO implement
  }
};

struct AveragePriceFilter : public BasicFilter
{
  const HotelList filter(const HotelList &&input) const
  {
    return input; /// TODO implement
  }
};

struct FreeRoomFilter : public BasicFilter
{
  const HotelList filter(const HotelList &&input) const
  {
    return input; /// TODO implement
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
