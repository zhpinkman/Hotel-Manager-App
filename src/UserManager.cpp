//
// Created by zhivar on 4/17/20.
//

#include "../includes/Exception.hpp"
#include "../includes/User.h"
#include "../includes/UserManager.h"
#include <iostream>

UserManager::UserManager() { loggedInUser = nullptr; }

void UserManager::login(const User &user)
{
    User *foundedUser = findUser(user.getEmail());
    if (foundedUser->passwordMatches(user.getPassword()))
        loggedInUser = foundedUser;
}

void UserManager::signup(const User &user)
{
    if (findUser(user.getEmail()))
        throw new BadRequestException();

    users.push_back(new User(user.getEmail(), user.getUsername(), user.getPassword()));
}

void UserManager::logout() { loggedInUser = nullptr; }

User *UserManager::findUser(const std::string &email)
{
    for (auto &user : users)
    {
        if (user->emailMatches(email))
        {
            return user;
        }
    }
    return nullptr;
}

bool UserManager::isUserLoggedIn() { return loggedInUser != nullptr; }

void UserManager::getWallet(double amount) { loggedInUser->getWallet(amount); }
