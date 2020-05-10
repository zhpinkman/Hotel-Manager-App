#include "Sort.hh"
#include <exception>
#include <map>

using namespace std;

vector<Hotel*> HotelSortManager::sort(vector<Hotel*> hotels) const {
	vector<Hotel*> result = hotels;
	std::sort(result.begin(), result.end(), HotelComparator(property));
	if (sortOrder == DESCENDING)
		std::reverse(result.begin(), result.end());
	return result;
}


bool HotelComparator::operator()(const Hotel* hotel1, const Hotel* hotel2) const {
	if (property == SortableHotelProperty::ID) 
		return hotel1->getId() < hotel2->getId();
	if (property == SortableHotelProperty::NAME) 
		return hotel1->getHotelName() < hotel2->getHotelName();
	if (property == SortableHotelProperty::STAR_RATING) 
		return hotel1->getStar() < hotel2->getStar();
	if (property == SortableHotelProperty::CITY) 
		return hotel1->getCity() < hotel2->getCity();
	if (property == SortableHotelProperty::STANDARD_ROOM_PRICE) 
		return hotel1->getStandardRoomPrice() < hotel2->getStandardRoomPrice();
	if (property == SortableHotelProperty::DELUXE_ROOM_PRICE) 
		return hotel1->getDeluxeRoomPrice() < hotel2->getDeluxeRoomPrice();
	if (property == SortableHotelProperty::LUXURY_ROOM_PRICE) 
		return hotel1->getLuxuryRoomPrice() < hotel2->getLuxuryRoomPrice();
	if (property == SortableHotelProperty::PREMIUM_ROOM_PRICE) 
		return hotel1->getPremiumRoomPrice() < hotel2->getPremiumRoomPrice();
	if (property == SortableHotelProperty::AVERAGE_ROOM_PRICE) 
		return hotel1->getRoomService().getRoomsAveragePrice() < hotel2->getRoomService().getRoomsAveragePrice();
	throw logic_error("invalid HotelComparator state: unexpected property value: " + to_string(property));
}


SortOrder strToSortOrder(std::string str) {
  map<string, SortOrder> strToEnum;
  strToEnum["ascending"] = SortOrder::ASCENDING;
  strToEnum["descending"] = SortOrder::DESCENDING;
  if (strToEnum.find(str) != strToEnum.end())
  	return strToEnum[str];
  throw invalid_argument("Cannot convert string: " + str + " to SortOrder.");
}

SortableHotelProperty strToSortableHotelProperty(string str) {
  map<string, SortableHotelProperty> strToEnum;
  strToEnum["id"] = SortableHotelProperty::ID;
  strToEnum["name"] = SortableHotelProperty::NAME;
  strToEnum["star_rating"] = SortableHotelProperty::STAR_RATING;
  strToEnum["city"] = SortableHotelProperty::CITY;
  strToEnum["standard_room_price"] = SortableHotelProperty::STANDARD_ROOM_PRICE;
  strToEnum["deluxe_room_price"] = SortableHotelProperty::DELUXE_ROOM_PRICE;
  strToEnum["luxury_room_price"] = SortableHotelProperty::LUXURY_ROOM_PRICE;
  strToEnum["premium_room_price"] = SortableHotelProperty::PREMIUM_ROOM_PRICE;
  strToEnum["average_room_price"] = SortableHotelProperty::AVERAGE_ROOM_PRICE;
  if (strToEnum.find(str) != strToEnum.end())
  	return strToEnum[str];
  throw invalid_argument("Cannot convert string: " + str + " to SortableHotelProperty.");
}

