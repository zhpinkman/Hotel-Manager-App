//
// Created by zhivar on 4/17/20.
//

#ifndef UT_AP_S99_FINAL_USER_H
#define UT_AP_S99_FINAL_USER_H

#include <string>
#include <vector>

class Reservation;

class User
{
public:
    User(std::string, std::string, std::string);

    bool emailMatches(std::string _email) const;

    bool passwordMatches(std::string _password) const;

    void getWallet(double amount) const;

    std::string getEmail() const
    {
        return email;
    }
    std::string getUsername() const
    {
        return username;
    }
    std::string getPassword() const
    {
        return password;
    }

private:
    std::string email;
    std::string username;
    std::string password;
    std::vector<Reservation *> reservations;
    double balance;
    std::vector<double> balanceHistory;
};

#endif //UT_AP_S99_FINAL_USER_H
