#pragma once

#include <string>
#include <vector>

#include "Exception.hh"

class Reservation;

class User
{
public:
    User(const std::string &email, const std::string &username, const std::string &password)
        : email(email),
          username(username),
          password(password),
          credit(0),
          balanceHistory({0}),
          nextUserReserveId(1)
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
    const std::string &getUsername() const { return username; }
    std::string getPassword() const { return password; }

    void addCredit(const double amount)
    {
        credit += amount;
        balanceHistory.push_back(credit);
    }

    std::vector<double> getBalanceHistoryReport(const std::size_t count) const
    {
        std::vector<double> result;
        for (std::size_t i = balanceHistory.size() - 1; (balanceHistory.size() - 1 - i) < count; i--)
        {
            result.push_back(balanceHistory[i]);
            if (!i)
                return result;
        }

        return result;
    }

    double getCredit() const
    {
        return credit;
    }

    void reduceCredit(const double cost)
    {
        if (cost > credit)
            throw new NotEnoughCreditException();

        credit -= cost;
        balanceHistory.push_back(credit);
    }

    std::size_t getNextUserReserveId()
    {
        return nextUserReserveId++;
    }

private:
    std::string email;
    std::string username;
    std::string password;
    std::vector<Reservation *> reservations;
    double credit;
    std::vector<double> balanceHistory;
    std::size_t nextUserReserveId;
};
