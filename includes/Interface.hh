#pragma once

#include <string>
#include <iomanip>
#include <sstream>

#include "Utrip.hh"
#include "Request.hh"

template <typename RequestType>
class Interface
{
    Utrip utrip;

    template <typename ReturnValueType>
    static ReturnValueType extractFromString(const std::string &stringValue)
    {
        std::stringstream ss(stringValue);
        ReturnValueType result;
        ss >> result;
        return result;
    }

public:
    Interface(const std::string &hotelsFilePath)
    {
        const std::ifstream &hotelsFile = Tools::open_csv_file(hotelsFilePath);
        RAW_DATA_LIST rawHotelsData = Tools::parse_csv_file(const_cast<std::ifstream &>(hotelsFile));
        utrip.importHotels(rawHotelsData);
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
        utrip.addCreditToWallet(extractFromString<double>(request.getParam("amount")));
        printSuccessMessage();
    }

    void runGetWalletCommand(const RequestType &request)
    {
        const auto balanceHistory = utrip.reportBalanceHistory(extractFromString<double>(request.getParam("count")));
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
                        std::forward<Hotel::RatingData::DataType>(
                            {extractFromString<double>(request.getParam("location")),
                             extractFromString<double>(request.getParam("cleanliness")),
                             extractFromString<double>(request.getParam("staff")),
                             extractFromString<double>(request.getParam("facilities")),
                             extractFromString<double>(request.getParam("value_for_money")),
                             extractFromString<double>(request.getParam("overall_rating"))}));
        printSuccessMessage();
    }

    void runGetRateCommand(const RequestType &request)
    {
        const auto rateData = utrip.getRating(request.getParam("hotel"));

        if (!(*rateData.begin()))
        {
            std::cout << "No Rating" << std::endl;
            return;
        }

        std::cout << std::fixed << std::setprecision(2)
                  << "location: " << rateData[0] << std::endl
                  << "cleanliness: " << rateData[1] << std::endl
                  << "staff: " << rateData[2] << std::endl
                  << "facilities: " << rateData[3] << std::endl
                  << "value_for_money: " << rateData[4] << std::endl
                  << "overal_rating: " << rateData[5] << std::endl;

        std::cout.unsetf(std::ios_base::fixed);
    }

    void runSetReserveCommand(const RequestType &request)
    {
        utrip.reserve(request.getParam("hotel"),
                      request.getParam("type"),
                      extractFromString<std::size_t>(request.getParam("quantity")),
                      extractFromString<std::size_t>(request.getParam("check_in")),
                      extractFromString<std::size_t>(request.getParam("check_out")));
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
        utrip.deleteReservations(extractFromString<std::size_t>(request.getParam("id")));
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
};
