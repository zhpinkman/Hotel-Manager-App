#include "Filter.hh"
#include "Utrip.hh"

#include <iostream>
#include <typeinfo>

using namespace std;

vector<Hotel*> Filter::apply(vector<Hotel*> hotels) const {
	vector<Hotel*> result;
	std::copy_if(hotels.begin(), hotels.end(), std::back_inserter(result),
	 [this](Hotel* hotel){return this->accepts(hotel);});
	return result;
}

bool CityFilter::accepts(Hotel* hotel) const {
	return this->city == hotel->getCity();
}

CityFilter::CityFilter(std::string city): city(city) {}


bool StarRatingFilter::accepts(Hotel* hotel) const {
	return hotel->getStar() >= this->minStarRating &&
	       hotel->getStar() <= this->maxStarRating;
}

StarRatingFilter::StarRatingFilter(uint minStarRating, uint maxStarRating) :
	minStarRating(minStarRating), maxStarRating(maxStarRating) {}


bool AveragePriceFilter::accepts(Hotel* hotel) const {
	double avgPrice = hotel->getRoomService().getRoomsAveragePrice();
	return avgPrice >= this->minPrice && avgPrice <= this->maxPrice;
}

AveragePriceFilter::AveragePriceFilter(double minPrice, double maxPrice) :
	minPrice(minPrice), maxPrice(maxPrice) {}


bool FreeRoomFilter::accepts(Hotel* hotel) const {
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

	if (defaultPriceFilterIsActive && 
		Utrip::instance()->isEligibleForHistoryBasedPriceFilter() &&
		!this->hasFilterOfType<AveragePriceFilter>())
		result = this->filterByHistoryBasedPriceFilter(result);

	return result;
}

std::vector<Hotel*> HotelFilterManager::filterByHistoryBasedPriceFilter(std::vector<Hotel*> hotels) const {
	double mean, standardDeviation;
	std::tie(mean, standardDeviation) = Utrip::instance()->calculateReservationPriceStatistics();
	return AveragePriceFilter(mean - 2*standardDeviation, mean + 2*standardDeviation).apply(hotels);
}

void HotelFilterManager::setDefaultPriceFilterIsActive(bool isActive)
{
	defaultPriceFilterIsActive = isActive;
}

HotelFilterManager::HotelFilterManager() : defaultPriceFilterIsActive(true) {}

HotelFilterManager::~HotelFilterManager() {
	for (Filter* filter: filters)
		delete filter;
}