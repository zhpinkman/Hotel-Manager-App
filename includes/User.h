//
// Created by zhivar on 4/17/20.
//

#ifndef UT_AP_S99_FINAL_USER_H
#define UT_AP_S99_FINAL_USER_H

#include <string>
#include <vector>

class Reservation;

class User {
public:
    User(std::string, std::string, std::string);

    bool emailMatches(std::string _email);

    bool passwordMatches(std::string _password);

    void getWallet(double amount);

private:
    std::string email;
    std::string username;
    std::string password;
    std::vector<Reservation*> reservations;
    double balance;
    std::vector<double> balanceHistory;

};

#endif //UT_AP_S99_FINAL_USER_H
