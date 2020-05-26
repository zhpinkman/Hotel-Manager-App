#include "Utrip.hh"
#include "Utility.hh"
#include "User.hh"

using namespace utility;
using namespace std;

Utrip* Utrip::singleton_instance = nullptr;

Utrip* Utrip::instance()
{
    if (singleton_instance == nullptr)
        singleton_instance = new Utrip;
    return singleton_instance;
}

Utrip::Utrip(): hotelFilterManager(this) {}

void Utrip::importHotels(std::string filename) {
    const std::ifstream &hotelsFile = utility::open_csv_file(filename);
    RAW_DATA_LIST rawHotelsData = utility::parse_csv_file(const_cast<std::ifstream &>(hotelsFile));
    importHotels(rawHotelsData);
}

void Utrip::importHotels(const RAW_DATA_LIST &rawHotelsData) {
    hotelManager = HotelManager(rawHotelsData);
}

void Utrip::importRatings(std::string filename) {
    const std::ifstream &ratingsFile = utility::open_csv_file(filename);
    RAW_DATA_LIST rawRatingsData = utility::parse_csv_file(const_cast<std::ifstream &>(ratingsFile));
    importRatings(rawRatingsData);
}

void Utrip::importRatings(const RAW_DATA_LIST &rawRatingsData) {
    hotelManager.importRatings(rawRatingsData);
}

void Utrip::signup(const User &user)
{
    if (userManager.isUserLoggedIn())
        throw new BadRequestException();

    userManager.signup(user);
    userManager.login(user);
    hotelFilterManager = HotelFilterManager(this);
}

void Utrip::login(const User &user)
{
    if (userManager.isUserLoggedIn())
        throw new BadRequestException();

    userManager.login(user);
    hotelFilterManager = HotelFilterManager(this);
}

void Utrip::logout()
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    userManager.logout();
}

void Utrip::resetFilters()
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    hotelFilterManager = HotelFilterManager(this);
}

void Utrip::addCreditToWallet(const double amount)
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    constexpr double MinimumCreditAddition = 0;
    if (amount <= MinimumCreditAddition)
        throw new BadRequestException();

    userManager.loggedInUser->addCredit(amount);
}

std::vector<double> Utrip::reportBalanceHistory(const std::size_t count) const
{
    return userManager.getBalanceHistory(count);
}

std::vector<Hotel*> Utrip::getHotels() const
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    std::vector<Hotel*> hotelsResultSet;
    const auto &hotelsData = hotelManager.getHotels();
    std::transform(hotelsData.begin(), hotelsData.end(), std::back_inserter(hotelsResultSet),
                   [](std::pair<std::string, Hotel *> inputPair) { return inputPair.second; });

    std::vector<Hotel*> filteredHotels =
        hotelFilterManager.filter(std::forward<std::vector<Hotel*>>(hotelsResultSet));

    std::vector<Hotel*> sortedHotels = 
        hotelSortManager.sort(filteredHotels);

    return sortedHotels;
}

HotelManager::HotelList Utrip::getAllHotels() const { return hotelManager.getHotels(); }

const Hotel *const Utrip::getHotel(const std::string &id) const
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    const auto hotel = hotelManager.getHotel(id);
    if (!hotel)
        throw new NotFoundException();

    return hotel;
}

void Utrip::addFilter(const std::unordered_map<std::string, std::string> &filterObjects)
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    if (filterObjects.find("city") != filterObjects.end())
        hotelFilterManager.addFilter(new CityFilter(
            filterObjects.at("city")
        ));

    else if (filterObjects.find("min_star") != filterObjects.end() &&
             filterObjects.find("max_star") != filterObjects.end())
        hotelFilterManager.addFilter(new StarRatingFilter(
            extractFromString<uint>(filterObjects.at("min_star")),
            extractFromString<uint>(filterObjects.at("max_star"))
        ));

    else if (filterObjects.find("min_price") != filterObjects.end() &&
             filterObjects.find("max_price") != filterObjects.end())
        hotelFilterManager.addFilter(new AveragePriceFilter(
            extractFromString<double>(filterObjects.at("min_price")), 
            extractFromString<double>(filterObjects.at("max_price"))
        ));

    else if (filterObjects.find("type") != filterObjects.end() &&
             filterObjects.find("quantity") != filterObjects.end() &&
             filterObjects.find("check_in") != filterObjects.end() &&
             filterObjects.find("check_out") != filterObjects.end())
        hotelFilterManager.addFilter(new FreeRoomFilter(
            RoomService::convertRoomType(filterObjects.at("type")),
            extractFromString<std::size_t>(filterObjects.at("quantity")),
            extractFromString<std::size_t>(filterObjects.at("check_in")),
            extractFromString<std::size_t>(filterObjects.at("check_out"))
        ));

    else
        throw new BadRequestException();
}

void Utrip::setSortSettings(std::string property, std::string order) {
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    try {
        hotelSortManager.setParameters(
            strToSortableHotelProperty(property),
            strToSortOrder(order)
        );
    } catch (std::invalid_argument err) {
        throw new BadRequestException();
    }
}

void Utrip::addComment(const std::string &hotelId, const std::string &commentContent)
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    const auto &username = userManager.loggedInUser->getUsername();
    hotelManager.getHotels(hotelId).addComment(username, commentContent);
}

const Hotel::CommentList& Utrip::getComments(const std::string &hotelId) const
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    return hotelManager.getHotel(hotelId)->getComments();
}

void Utrip::addRating(const std::string &hotelId, const HotelRatings rateData)
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();
    hotelManager.getHotels(hotelId).addRating(userManager.loggedInUser, rateData);
}

HotelRatings Utrip::getRating(const std::string &hotelId)
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    return hotelManager.getHotels(hotelId).getAverageRatings();
}

void Utrip::reserve(const std::string &hotelId,
             const std::string &roomType,
             const std::size_t quantity,
             const std::size_t arrivalTime,
             const std::size_t departureTime)
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    auto &user = userManager.loggedInUser;
    auto &roomService = hotelManager.getHotels(hotelId).getRoomService();
    const auto requestedRoomType = RoomService::convertRoomType(roomType);
    const auto calculatedPrice = roomService.calculateReservePrice(requestedRoomType, quantity);

    if (calculatedPrice > userManager.loggedInUser->getCredit())
        throw new NotEnoughCreditException();

    if (!roomService.doesFreeRoomExists(requestedRoomType, quantity, arrivalTime, departureTime))
        throw new NotEnoughRoomException();

    user->reduceCredit(calculatedPrice);
    roomService.reserve(user->getNextUserReserveId(),
                        hotelId,
                        user->getUsername(),
                        requestedRoomType,
                        quantity,
                        calculatedPrice,
                        arrivalTime,
                        departureTime);
}

RoomService::ReservationSet Utrip::getReservations() const
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    const auto &username = userManager.loggedInUser->getUsername();
    const auto &hotels = hotelManager.getHotels();
    RoomService::ReservationSet userReservations;

    for (const auto &hotel : hotels)
    {
        const auto userReservationsInHotel = hotel.second->getRoomService().getUserReservations(username);
        userReservations.insert(userReservations.begin(),
                                userReservationsInHotel.begin(),
                                userReservationsInHotel.end());
    }

    std::sort(userReservations.begin(), userReservations.end(),
              [](const RoomService::ReservationType &first, const RoomService::ReservationType &second) {
                  return first.reservationId > second.reservationId;
              });

    return userReservations;
}

void Utrip::deleteReservations(const std::size_t reservationId)
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    auto &user = userManager.loggedInUser;
    const auto &hotels = hotelManager.getHotels();
    RoomService::ReservationSet userReservations;

    for (const auto &hotel : hotels)
        for (const auto &reservation : hotel.second->getRoomService().getUserReservations(user->getUsername()))
            if (reservation.reservationId == reservationId)
            {
                constexpr double CancelPaybackRatio = 0.5;
                user->addCredit(reservation.price * CancelPaybackRatio);
                hotel.second->getRoomService().deleteReservation(reservationId, user->getUsername());
                return;
            }
}



// returns a tuple with the mean as its first element and the standard deviation
// as its second element.
pair<double,double> Utrip::calculateReservationPriceStatistics() const {
    vector<double> reservedRoomPrices;
    for (RoomService::ReservationType reservation: this->getReservations()) {
        double unitPrice = reservation.price / reservation.quantity;
        for (int i = 0; i < reservation.quantity; i++)
            reservedRoomPrices.push_back(unitPrice);
    }

    return std::pair<double, double>(utility::mean(reservedRoomPrices),
        utility::sampleStandardDeviation(reservedRoomPrices));
}

bool Utrip::isEligibleForHistoryBasedPriceFilter() const {
    return (this->getReservations().size() >= 10);
}

User* Utrip::getLoggedInUser() { return userManager.loggedInUser; }

const User* Utrip::getLoggedInUser() const { return userManager.loggedInUser; }

bool Utrip::getWeightsAreManual() const
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    return getLoggedInUser()->getWeightsAreManual();
}

HotelRatingWeights Utrip::getManualWeights() const
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    return getLoggedInUser()->getManualWeights();

}
HotelRatingWeights Utrip::getEstimatedWeights()
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    return getLoggedInUser()->getEstimatedWeights();
}


void Utrip::activateManualWeights(HotelRatingWeights weights)
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException(); 

    getLoggedInUser()->activateManualWeights(weights);
}

void Utrip::deactivateManualWeights() 
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException(); 

    getLoggedInUser()->deactivateManualWeights();
}