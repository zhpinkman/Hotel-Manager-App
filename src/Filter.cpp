#include <typeinfo>
#include "Filter.hh"

using namespace std;

vector<Hotel*> Filter::apply(vector<Hotel*> hotels) const {
	vector<Hotel*> result;
	std::copy_if(hotels.begin(), hotels.end(), std::back_inserter(result),
	 [this](Hotel* hotel){return this->accept(hotel);});
	return result;
}

bool CityFilter::accept(Hotel* hotel) const {
	return this->city == hotel->getCity();
}

CityFilter::CityFilter(std::string city): city(city) {}


bool StarRatingFilter::accept(Hotel* hotel) const {
	return hotel->getStar() >= this->minStarRating &&
	       hotel->getStar() <= this->maxStarRating;
}

StarRatingFilter::StarRatingFilter(uint minStarRating, uint maxStarRating) :
	minStarRating(minStarRating), maxStarRating(maxStarRating) {}


bool AveragePriceFilter::accept(Hotel* hotel) const {
	double avgPrice = hotel->getRoomService().getRoomsAveragePrice();
	return avgPrice >= this->minPrice && avgPrice <= this->maxPrice;
}

AveragePriceFilter::AveragePriceFilter(double minPrice, double maxPrice) :
	minPrice(minPrice), maxPrice(maxPrice) {}


bool FreeRoomFilter::accept(Hotel* hotel) const {
	return hotel->getRoomService().doesFreeRoomExists(this->roomType, this->quantity,
	 this->arrivalTime, this->departureTime);
}

FreeRoomFilter::FreeRoomFilter(RoomService::RoomType roomType, std::size_t quantity,
	std::size_t arrivalTime, std::size_t departureTime) :
	roomType(roomType), quantity(quantity), arrivalTime(arrivalTime), departureTime(departureTime) {}
	


void HotelFilterManager::addFilter(Filter* filterToAdd) {
	for (int i = 0; i < filters.size(); i++) {
		if (typeid(*filters[i]) == typeid(*filterToAdd)) {
			delete filters[i];
			filters[i] = filterToAdd; //replace the old filter with the new
			return;
		}
	}
	filters.push_back(filterToAdd);
}

std::vector<Hotel*> HotelFilterManager::filter(std::vector<Hotel*> hotels) const {
	std::vector<Hotel*> result = hotels;
	for (Filter* filter: filters)
		result = filter->apply(result);
	return result;
}

HotelFilterManager::~HotelFilterManager() {
	for (Filter* filter: filters)
		delete filter;
}