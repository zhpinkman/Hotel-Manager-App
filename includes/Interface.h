//
// Created by zhivar on 4/17/20.
//

#ifndef UT_AP_S99_FINAL_INTERFACE_H
#define UT_AP_S99_FINAL_INTERFACE_H

#include <string>
#include <vector>

#include "Utrip.h"
#include "Request.hh"

template <typename RequestType>
class Interface
{
    Utrip utrip;

public:
    Interface() = default;

    void runSignupCommand(const RequestType &request)
    {
        const User user(request.getParam("email"),
                        request.getParam("username"),
                        request.getParam("password"));
        utrip.signup(user);
    }

    // void runLoginCommand(const UtripType::RequestType &reqeust);
    // void runLogoutCommand(const UtripType::RequestType &reqeust);
    // void runWalletCommand(const UtripType::RequestType &reqeust);
    // void runGetHotelsCommand(const UtripType::RequestType &reqeust);
    // void runGetHotelCommand(const UtripType::RequestType &reqeust);

    void runHotelsImport(const std::string &basicString)
    {
        utrip.importHotels(basicString);
    }
};

#endif //UT_AP_S99_FINAL_INTERFACE_H
