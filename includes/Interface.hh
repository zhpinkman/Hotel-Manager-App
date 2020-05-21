#pragma once

#include <string>
#include <iomanip>
#include <sstream>

#include "Utrip.hh"
#include "Request.hh"
#include "Exception.hh"
#include "HotelRatings.hh"
#include "Utility.hh"

template <typename RequestType>
class Interface
{
    Utrip utrip;

public:
    Interface(const std::string &hotelsFilePath, const std::string ratingsFilePath)
    {
        utrip.importHotels(hotelsFilePath);
        utrip.importRatings(ratingsFilePath);
    }

    void printSuccessMessage() { std::cout << "OK" << std::endl; }

    void runSignupCommand(const RequestType &request)
    {
        const User user(request.getParam("email"),
                        request.getParam("username"),
                        request.getParam("password"));
        utrip.signup(user);
        printSuccessMessage();
    }

    void runLoginCommand(const RequestType &request)
    {
        const User user(request.getParam("email"),
                        "",
                        request.getParam("password"));
        utrip.login(user);
        printSuccessMessage();
    }

    void runLogoutCommand(const RequestType &request)
    {
        utrip.logout();
        printSuccessMessage();
    }

    void runAddWalletCommand(const RequestType &request)
    {
        utrip.addCreditToWallet(utility::extractFromString<double>(request.getParam("amount")));
        printSuccessMessage();
    }

    void runGetWalletCommand(const RequestType &request)
    {
        const auto balanceHistory = utrip.reportBalanceHistory(utility::extractFromString<double>(request.getParam("count")));
        for (const auto &balanceHistoryLine : balanceHistory)
            std::cout << balanceHistoryLine << std::endl;
    }

    void runGetHotelsCommand(const RequestType &request)
    {
        const auto &params = request.getRequestParams();
        if (params.find("id") != params.end())
            utrip.getHotel(request.getParam("id"))->print();
        else
        {
            auto hotels = utrip.getHotels();

            if (!hotels.size())
                std::cout << "Empty" << std::endl;
            for (const auto &hotel : hotels)
                hotel->printBriefly();
        }
    }

    void runAddFilterCommand(const RequestType &request)
    {
        utrip.addFilter(request.getRequestParams());
        printSuccessMessage();
    }

    void runAddCommentCommand(const RequestType &request)
    {
        utrip.addComment(request.getParam("hotel"), request.getParam("comment"));
        printSuccessMessage();
    }

    void runGetCommentsCommand(const RequestType &request)
    {
        const auto comments = utrip.getComments(request.getParam("hotel"));
        if (!comments.size())
            return;

        for (long int i = (comments.size() - 1); i >= 0; --i)
            std::cout << comments[i].getUsername() << ": " << comments[i].getComment() << std::endl;
    }

    void runAddRateCommand(const RequestType &request)
    {
        utrip.addRating(request.getParam("hotel"),
            HotelRatings(
                utility::extractFromString<double>(request.getParam("location")),
                utility::extractFromString<double>(request.getParam("cleanliness")),
                utility::extractFromString<double>(request.getParam("staff")),
                utility::extractFromString<double>(request.getParam("facilities")),
                utility::extractFromString<double>(request.getParam("value_for_money")),
                utility::extractFromString<double>(request.getParam("overall_rating"))
            )
        );
        printSuccessMessage();
    }

    void runGetRateCommand(const RequestType &request)
    {
        const auto ratings = utrip.getRating(request.getParam("hotel"));

        if (!ratings.isInitialized())
        {
            std::cout << "No Rating" << std::endl;
            return;
        }

        std::cout << std::fixed << std::setprecision(2)
                  << "location: " << ratings.getRating("location") << std::endl
                  << "cleanliness: " << ratings.getRating("cleanliness") << std::endl
                  << "staff: " << ratings.getRating("staff") << std::endl
                  << "facilities: " << ratings.getRating("facilities") << std::endl
                  << "value_for_money: " << ratings.getRating("value_for_money") << std::endl
                  << "overal_rating: " << ratings.getRating("overall") << std::endl;

        std::cout.unsetf(std::ios_base::fixed);
    }

    void runSetReserveCommand(const RequestType &request)
    {
        utrip.reserve(request.getParam("hotel"),
                      request.getParam("type"),
                      utility::extractFromString<std::size_t>(request.getParam("quantity")),
                      utility::extractFromString<std::size_t>(request.getParam("check_in")),
                      utility::extractFromString<std::size_t>(request.getParam("check_out")));
        printSuccessMessage();
    }

    void runGetReserveCommand(const RequestType &request) const
    {
        const auto userReservations = utrip.getReservations();
        if (!userReservations.size())
        {
            std::cout << "Empty" << std::endl;
            return;
        }

        for (const auto &reservation : userReservations)
            std::cout << "id: " << reservation.reservationId << " "
                      << "hotel: " << reservation.hotelId << " "
                      << "room: " << RoomService::toString(reservation.roomType) << " "
                      << "quantity: " << reservation.quantity << " "
                      << "cost: " << static_cast<std::size_t>(reservation.price) << " "
                      << "check_in: " << reservation.arrivalTime << " "
                      << "check_out: " << reservation.departureTime << std::endl;
    }

    void runDeleteReserveCommand(const RequestType &request)
    {
        utrip.deleteReservations(utility::extractFromString<std::size_t>(request.getParam("id")));
        printSuccessMessage();
    }

    void runResetFilterCommand(const RequestType &)
    {
        utrip.resetFilters();
        printSuccessMessage();
    }

    void runSortCommand(const RequestType& request) 
    {
        utrip.setSortSettings(request.getParam("property"), request.getParam("order"));
        printSuccessMessage();
    }

    void runGetManualWeightsCommand(const RequestType& request) 
    {
        bool manualWightsAreActive = utrip.getWeightsAreManual();
        HotelRatingWeights weights = utrip.getManualWeights();
        std::cout<<"active "<<(manualWightsAreActive ? "true " : "false");
        if (manualWightsAreActive)
        {
            for (std::string category: HotelRatingWeights::categories)
                std::cout<<category<<" "<<weights.getWeight(category)<<" ";
        }
        std::cout<<std::endl;
    }

    void runSetManualWeightsCommand(const RequestType& request) 
    {   
        double isActive = utility::extractFromString<bool>(request.getParam("active"));
        if (isActive) {
            std::vector<std::string> allKeywords = utility::vectorCat({"active"}, HotelRatingWeights::categories);
            if (request.containsExactly(allKeywords)) {
                utrip.activateManualWeights(HotelRatingWeights(
                    utility::extractFromString<double>(request.getParam("location")),
                    utility::extractFromString<double>(request.getParam("cleanliness")),
                    utility::extractFromString<double>(request.getParam("staff")),
                    utility::extractFromString<double>(request.getParam("facilities")),
                    utility::extractFromString<double>(request.getParam("value_for_money"))
                ));
            } else 
                throw new BadRequestException();
        } else {
            if (request.containsExactly({"active"})) {
                utrip.deactivateManualWeights();
            } else 
                throw new BadRequestException();
        }
        printSuccessMessage();
    }
};
