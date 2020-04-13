#ifndef __HOTEL_H__
#define __HOTEL_H__ __HOTEL_H__

#include <string>
#include <vector>

typedef std::vector<std::string> Amenities;

class Room_service;

struct City {
  std::string city_name;
  double latitude;
  double longitude;
};

class Hotel {
public:
  Hotel();

private:
  std::string hotel_id;
  std::string hotel_name;
  int hotel_rating;
  std::string hotel_overview;
  Amenities amenities;
  City city;
  std::string image_url;
  Room_service *room_service;
};

#endif