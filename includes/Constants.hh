#pragma once

#include <vector>

#define AMENITIES_ARG_INDEX 4
#define CITY_ARG_INDEX 5
#define LATITUDE_ARG_INDEX 6
#define LONGITUDE_ARG_INDEX 7
#define HOTEL_ID_ARG_INDEX 0
#define HOTEL_NAME_ARG_INDEX 1
#define HOTEL_RATING_ARG_INDEX 2
#define HOTEL_OVERVIEW_ARG_INDEX 3
#define HOTEL_IMAGE_ARG_INDEX 8
#define NUM_OF_STANDARD_ROOMS_ARG_INDEX 9
#define NUM_OF_DELUXE_ROOMS_ARG_INDEX 10
#define NUM_OF_LUXURY_ROOMS_ARG_INDEX 11
#define NUM_OF_PREMIUM_ROOMS_ARG_INDEX 12
#define PRICE_OF_STANDARD_ROOMS_ARG_INDEX 13
#define PRICE_OF_DELUXE_ROOMS_ARG_INDEX 14
#define PRICE_OF_LUXURY_ROOMS_ARG_INDEX 15
#define PRICE_OF_PREMIUM_ROOMS_ARG_INDEX 16

#define OK "OK"
#define ENTER '\n'
#define SUCCESS true
#define FAILED false
#define SEPERATOR " | "
// #define POST "POST"
// #define GET "GET"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin"
#define ADMIN_EMAIL "admin@gmail.com"

#define SPACE ' '
#define COMMA ','

#define AMENITY_SEPARATOR '|'

typedef std::vector<std::vector<std::string>> RAW_DATA_LIST;
typedef std::vector<std::string> RAW_DATA;
typedef std::vector<std::string> Amenities;
