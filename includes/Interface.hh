#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>

#include "Utrip.hh"
#include "Request.hh"
#include "Exception.hh"
#include "HotelRatings.hh"
#include "Utility.hh"

template <typename RequestType>
class Interface
{
public:
    Interface(const std::string &hotelsFilePath, const std::string ratingsFilePath)
    {
        Utrip::instance()->importHotels(hotelsFilePath);
        Utrip::instance()->importRatings(ratingsFilePath);
    }

    void printSuccessMessage() { std::cout << "OK" << std::endl; }

    void runSignupCommand(const RequestType &request)
    {
        const User user(request.getParam("email"),
                        request.getParam("username"),
                        request.getParam("password"));
        Utrip::instance()->signup(user);
        printSuccessMessage();
    }

    void runLoginCommand(const RequestType &request)
    {
        const User user(request.getParam("email"),
                        "",
                        request.getParam("password"));
        Utrip::instance()->login(user);
        printSuccessMessage();
    }

    void runLogoutCommand(const RequestType &request)
    {
        Utrip::instance()->logout();
        printSuccessMessage();
    }

    void runAddWalletCommand(const RequestType &request)
    {
        Utrip::instance()->addCreditToWallet(utility::extractFromString<double>(request.getParam("amount")));
        printSuccessMessage();
    }

    void runGetWalletCommand(const RequestType &request)
    {
        std::cout << std::fixed;
        const auto balanceHistory = Utrip::instance()->reportBalanceHistory(
            utility::extractFromString<double>(request.getParam("count")));
        for (const auto &balanceHistoryLine : balanceHistory)
            std::cout << (int)balanceHistoryLine << std::endl;
    }

    void runGetHotelsCommand(const RequestType &request)
    {
        const auto &params = request.getRequestParams();
        if (params.find("id") != params.end())
            Utrip::instance()->getHotel(request.getParam("id"))->print();
        else
        {
            auto hotels = Utrip::instance()->getHotels();

            if (Utrip::instance()->defaultPriceFilterWillBeApplied())
                std::cout<<"* Results have been filtered by the default price filter."<<std::endl;

            if (!hotels.size())
                std::cout << "Empty" << std::endl;
            else for (const auto &hotel : hotels)
                hotel->printBriefly();
        }
    }

    void runAddFilterCommand(const RequestType &request)
    {
        Utrip::instance()->addFilter(request.getRequestParams());
        printSuccessMessage();
    }

    void runAddCommentCommand(const RequestType &request)
    {
        Utrip::instance()->addComment(request.getParam("hotel"), request.getParam("comment"));
        printSuccessMessage();
    }

    void runGetCommentsCommand(const RequestType &request)
    {
        const auto comments = Utrip::instance()->getComments(request.getParam("hotel"));
        if (!comments.size())
            return;

        for (long int i = (comments.size() - 1); i >= 0; --i)
            std::cout << comments[i].getUsername() << ": " << comments[i].getComment() << std::endl;
    }

    void runAddRateCommand(const RequestType &request)
    {
        Utrip::instance()->addRating(request.getParam("hotel"),
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
        const auto ratings = Utrip::instance()->getRating(request.getParam("hotel"));

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
        Utrip::instance()->reserve(request.getParam("hotel"),
                      request.getParam("type"),
                      utility::extractFromString<std::size_t>(request.getParam("quantity")),
                      utility::extractFromString<std::size_t>(request.getParam("check_in")),
                      utility::extractFromString<std::size_t>(request.getParam("check_out")));
        printSuccessMessage();
    }

    void runGetReserveCommand(const RequestType &request) const
    {
        const auto userReservations = Utrip::instance()->getReservations();
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
        Utrip::instance()->deleteReservations(utility::extractFromString<std::size_t>(request.getParam("id")));
        printSuccessMessage();
    }

    void runResetFilterCommand(const RequestType &)
    {
        Utrip::instance()->resetFilters();
        printSuccessMessage();
    }

    void runSortCommand(const RequestType& request) 
    {
        Utrip::instance()->setSortSettings(request.getParam("property"), request.getParam("order"));
        printSuccessMessage();
    }

    void runGetManualWeightsCommand(const RequestType& request) 
    {
        bool manualWightsAreActive = Utrip::instance()->getWeightsAreManual();
        HotelRatingWeights weights = Utrip::instance()->getManualWeights();
        std::cout<<"active "<<(manualWightsAreActive ? "true " : "false");
        if (manualWightsAreActive)
        {
            std::cout<<std::fixed<<std::setprecision(2);
            for (std::string category: HotelRatingWeights::categories)
                std::cout<<category<<" "<<utility::truncate(weights.getWeight(category), 2)<<" ";
            std::cout.unsetf(std::ios_base::fixed);
        }
        std::cout<<std::endl;
    }

    void runSetManualWeightsCommand(const RequestType& request) 
    {
        try 
        {
            double isActive = utility::extractFromString<bool>(request.getParam("active"));
            if (isActive) {
                std::vector<std::string> allKeywords = utility::vectorCat({"active"}, HotelRatingWeights::categories);
                if (request.containsExactly(allKeywords)) {
                    Utrip::instance()->activateManualWeights(HotelRatingWeights(
                        utility::extractFromString<double>(request.getParam("location")),
                        utility::extractFromString<double>(request.getParam("cleanliness")),
                        utility::extractFromString<double>(request.getParam("staff")),
                        utility::extractFromString<double>(request.getParam("facilities")),
                        utility::extractFromString<double>(request.getParam("value_for_money"))
                    ));
                } else 
                    throw new BadRequestException();
            } else {
                if (request.containsExactly({"active"}))
                    Utrip::instance()->deactivateManualWeights();
                else 
                    throw new BadRequestException();
            }
            printSuccessMessage();
        } catch (std::invalid_argument ex) 
        {
            throw new BadRequestException();
        }
    }

    void runGetEstimatedWeightsCommand(const RequestType& request)
    {
        HotelRatingWeights weights = Utrip::instance()->getEstimatedWeights();
        std::cout<<std::fixed<<std::setprecision(2);
        for (std::string category: HotelRatingWeights::categories)
            std::cout<<category<<" "<<weights.getWeight(category)<<" ";
        std::cout.unsetf(std::ios_base::fixed);
        std::cout<<std::endl;
    }

    void runSetDefaultPriceFilterIsActiveCommand(const RequestType& request)
    {
        try {
            Utrip::instance()->setDefaultPriceFilterIsActive(
                utility::extractFromString<bool>(request.getParam("active"))
            );
            printSuccessMessage();
        } catch (ParseException ex) 
        {
            throw new BadRequestException();
        }
    }
};
