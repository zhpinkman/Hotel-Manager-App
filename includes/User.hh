#pragma once

#include <string>
#include <vector>

class Reservation;

class User
{
public:
    User(const std::string &email, const std::string &username, const std::string &password)
        : email(email),
          username(username),
          password(password),
          balance(0),
          balanceHistory({0})
    {
    }

    bool emailMatches(const std::string &_email) const
    {
        return (email == _email);
    }

    bool passwordMatches(const std::string &_password) const
    {
        return password == _password;
    }

    std::string getEmail() const { return email; }
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    // void getWallet(double amount) const;

private:
    std::string email;
    std::string username;
    std::string password;
    std::vector<Reservation *> reservations;
    double balance;
    std::vector<double> balanceHistory;
};
