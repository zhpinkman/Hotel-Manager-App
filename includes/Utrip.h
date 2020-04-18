//
// Created by zhivar on 4/17/20.
//

#ifndef UT_AP_S99_FINAL_UTRIP_H
#define UT_AP_S99_FINAL_UTRIP_H

#include <vector>
#include <string>


class UserManager;
class HotelManager;

class Utrip{
public:
    Utrip();

    void signup(const std::string& email, std::string username, const std::string& password);

    void login(std::string email, std::string password);

    void logout();

    void importHotels(const std::string &hotelsFile);

    void getWallet(const std::string &amount);

    void getHotels();

private:
    UserManager* userManager;
    HotelManager* hotelManager;

    void printSuccessMessage();
};

#endif //UT_AP_S99_FINAL_UTRIP_H
