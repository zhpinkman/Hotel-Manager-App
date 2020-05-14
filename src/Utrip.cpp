#include "Utrip.hh"


void Utrip::importHotels(const RAW_DATA_LIST &rawHotelsData)
{
    hotelManager = HotelManager(rawHotelsData);
}

void Utrip::signup(const User &user)
{
    if (userManager.isUserLoggedIn())
        throw new BadRequestException();

    userManager.signup(user);
    userManager.login(user);
    hotelFilterManager = Filter::HotelFilterManager();
}

void Utrip::login(const User &user)
{
    if (userManager.isUserLoggedIn())
        throw new BadRequestException();

    userManager.login(user);
    hotelFilterManager = Filter::HotelFilterManager();
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

    hotelFilterManager = Filter::HotelFilterManager();
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

Filter::HotelList Utrip::getHotels() const
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    Filter::HotelList hotelsResultSet;
    const auto &hotelsData = hotelManager.getHotels();
    std::transform(hotelsData.begin(), hotelsData.end(), std::back_inserter(hotelsResultSet),
                   [](std::pair<std::string, Hotel *> inputPair) { return inputPair.second; });

    std::vector<Hotel*> filteredHotels =
        hotelFilterManager.filter(std::forward<Filter::HotelList>(hotelsResultSet));

    std::vector<Hotel*> sortedHotels = 
        hotelSortManager.sort(filteredHotels);

    return sortedHotels;
}

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
        hotelFilterManager.addFilter<Filter::CityFilter>(filterObjects.at("city"));
    else if (filterObjects.find("min_star") != filterObjects.end() &&
             filterObjects.find("max_star") != filterObjects.end())
        hotelFilterManager.addFilter<Filter::StarsFilter>(filterObjects.at("min_star"),
                                                          filterObjects.at("max_star"));
    else if (filterObjects.find("min_price") != filterObjects.end() &&
             filterObjects.find("max_price") != filterObjects.end())
        hotelFilterManager.addFilter<Filter::AveragePriceFilter>(filterObjects.at("min_price"),
                                                                 filterObjects.at("max_price"));
    else if (filterObjects.find("type") != filterObjects.end() &&
             filterObjects.find("quantity") != filterObjects.end() &&
             filterObjects.find("check_in") != filterObjects.end() &&
             filterObjects.find("check_out") != filterObjects.end())
        hotelFilterManager.addFilter<Filter::FreeRoomFilter>(filterObjects.at("type"),
                                                             filterObjects.at("quantity"),
                                                             filterObjects.at("check_in"),
                                                             filterObjects.at("check_out"));
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

void Utrip::addRating(const std::string &hotelId, const Hotel::RatingData::DataType rateData)
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    const auto &username = userManager.loggedInUser->getUsername();
    hotelManager.getHotels(hotelId).addRating(username, rateData);
}

Hotel::RatingData::DataType Utrip::getRating(const std::string &hotelId)
{
    if (!userManager.isUserLoggedIn())
        throw new PermissionDeniedException();

    return hotelManager.getHotels(hotelId).getRating();
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
std::pair<double,double> Utrip::calculateReservationPriceStatistics() {
    std::vector<double> reservedRoomPrices;
    for (RoomService::ReservationType reservation: this->getReservations()) {
        double unitPrice = reservation.price / reservation.quantity;
        for (int i = 0; i < reservation.quantity; i++)
            reservedRoomPrices.push_back(unitPrice);
    }

    return std::pair<double, double>(utility::mean(reservedRoomPrices),
        utility::standardDeviation(reservedRoomPrices));
}

