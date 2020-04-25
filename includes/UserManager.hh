#pragma once

#include <unordered_map>
#include <string>
#include "User.hh"
#include "Exception.hh"

#include <iostream> // TODO

struct UserManager
{
    User *loggedInUser; // TODO: It could be replaced with std::optional in C++17
    std::unordered_map<std::string, User *> users;
    User *findUser(const std::string &email)
    {
        if (users.find(email) == users.end())
            return nullptr;

        return users[email];
    }

public:
    UserManager() : loggedInUser(nullptr)
    {
    }

    void login(const User &user)
    {
        User *const foundedUser = findUser(user.getEmail());

        if (foundedUser && foundedUser->passwordMatches(user.getPassword()))
            loggedInUser = foundedUser;
        else
            throw new BadRequestException();
    }

    void signup(const User &user)
    {
        if (findUser(user.getEmail()))
            throw new BadRequestException();

        users.emplace(user.getEmail(), new User(user.getEmail(),
                                                user.getUsername(),
                                                user.getPassword()));
    }

    void logout()
    {
        loggedInUser = nullptr;
    }

    std::vector<double> getBalanceHistory(const std::size_t count) const
    {
        return loggedInUser->getBalanceHistoryReport(count);
    }

    bool isUserLoggedIn() const
    {
        return loggedInUser != nullptr;
    }
};
