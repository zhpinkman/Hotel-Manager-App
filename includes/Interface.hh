#pragma once

#include <string>
#include <vector>

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
            for (const auto &hotel : utrip.getHotels())
                hotel->printBriefly();
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
        for (const auto &comment : utrip.getComments(request.getParam("hotel")))
            std::cout << comment.getUsername() << ": " << comment.getComment() << std::endl;
    }

    void runAddRateCommand(const RequestType &request)
    {
        // TODO: store the keys in a member array

        utrip.addRating(request.getParam("hotel"),
                        std::forward<Hotel::RatingData::DataType>(
                            {extractFromString<double>(request.getParam("location")),
                             extractFromString<double>(request.getParam("cleanliness")),
                             extractFromString<double>(request.getParam("staff")),
                             extractFromString<double>(request.getParam("facilities")),
                             extractFromString<double>(request.getParam("value_for_money")),
                             extractFromString<double>(request.getParam("overall_rating"))}));
    }

    void runGetRateCommand(const RequestType &request)
    {
        const auto rateData = utrip.getRating(request.getParam("hotel"));

        if (!(*rateData.begin()))
        {
            std::cout << "No Rating" << std::endl;
            return;
        }

        std::cout << "location: " << rateData[0] << std::endl
                  << "cleanliness: " << rateData[1] << std::endl
                  << "staff: " << rateData[2] << std::endl
                  << "facilities: " << rateData[3] << std::endl
                  << "value_for_money: " << rateData[4] << std::endl
                  << "overal_rating: " << rateData[5] << std::endl;
    }
};
