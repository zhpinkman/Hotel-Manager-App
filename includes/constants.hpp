#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define INPUT_CSV_FILE_INDEX 1
#define AMENITIES_ARG_INDEX 4
#define CITY_ARG_INDEX 5
#define LATITUDE_ARG_INDEX 6
#define LONGITUDE_ARG_INDEX 7
#define HOTEL_ID_ARG_INDEX 0
#define HOTEL_NAME_ARG_INDEX 1
#define HOTEL_RATING_ARG_INDEX 2
#define HOTEL_OVERVIEW_ARG_INDEX 3
#define HOTEL_IMAGE_ARG_INDEX 8
#define OK "OK"
#define BAD_REQUEST "Bad Request"
#define ENTER '\n'
#define SUCCESS true
#define FAILED false
#define SEPERATOR " | "
#define POST "POST"
#define GET "GET"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin"
#define ADMIN_EMAIL "admin@gmail.com"

#define SIGNUP "signup"
#define LOGIN "login"
#define LOGOUT "logout"
#define WALLET "wallet"
#define HOTELS_GET "hotels"
#define SPACE ' '
#define COMMA ','


#define AMENITY_SEPARATOR '|'

#define CREDIT "credit"

typedef std::vector<std::vector<std::string>> RAW_DATA_LIST;
typedef std::vector<std::string> RAW_DATA;
typedef std::vector<std::string> Amenities;

struct City {
    City(const std::string _city, const double _latitude, const double _longitude) {
        city_name = _city;
        latitude = _latitude;
        longitude = _longitude;
    }
    std::string city_name;
    double latitude;
    double longitude;
};

#endif