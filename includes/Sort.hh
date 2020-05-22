#pragma once

#include "Hotel.hh"
#include <vector>

enum SortOrder {ASCENDING, DESCENDING};
enum SortableHotelProperty {
    ID,
    NAME,
    STAR_RATING,
    CITY,
    STANDARD_ROOM_PRICE,
    DELUXE_ROOM_PRICE,
    LUXURY_ROOM_PRICE,
    PREMIUM_ROOM_PRICE,
    AVERAGE_ROOM_PRICE,
    RATING_OVERALL,
	RATING_PERSONAL
};

SortOrder strToSortOrder(std::string str);
SortableHotelProperty strToSortableHotelProperty(std::string str);

class HotelSortManager {
public:
	HotelSortManager(SortableHotelProperty property, SortOrder sortOrder) :
		property(property), sortOrder(sortOrder) {}
	// the default behaviour is to sort ascending based on hotel id:
	HotelSortManager(): property(ID), sortOrder(ASCENDING) {}
	void setParameters(SortableHotelProperty _property, SortOrder _sortOrder) {
		property = _property;
		sortOrder = _sortOrder;
	}
	std::vector<Hotel*> sort(std::vector<Hotel*> hotels) const;
private:
	SortableHotelProperty property;
	SortOrder sortOrder;
};


class HotelComparator {
public:
	HotelComparator(SortableHotelProperty property, SortOrder sortOrder) :
	 property(property), sortOrder(sortOrder) {}
	bool operator()(const Hotel* hotel1, const Hotel* hotel2) const;
private:
	template <typename Property> bool compare(Property p1, Property p2) const {
		if (sortOrder == ASCENDING)
			return p1 < p2;
		else if (sortOrder == DESCENDING)
			return p1 > p2;
	}
	SortableHotelProperty property;
	SortOrder sortOrder;
};