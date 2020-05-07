#pragma once

#include <string>

struct City
{
  City(const std::string &cityName,
       const double latitude,
       const double longitude)
      : cityName(cityName),
        latitude(latitude),
        longitude(longitude)
  {
  }

  std::string cityName;
  double latitude;
  double longitude;
};