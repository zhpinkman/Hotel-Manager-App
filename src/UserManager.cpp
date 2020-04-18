//
// Created by zhivar on 4/17/20.
//

#include <iostream>
#include "../includes/UserManager.h"
#include "../includes/User.h"
#include "../includes/Exception.hpp"

UserManager::UserManager() {
    loggedInUser = nullptr;
}

void UserManager::login(const std::string& email, const std::string &password) {
    User* user = findUser(email);
    if (user->passwordMatches(password)) {
        loggedInUser = user;
    }
}

void UserManager::signup(const std::string& email, const std::string &username, const std::string &password) {
    if (findUser(email)) {
        throw new Bad_request_exception();
    }
    users.push_back(new User(email, username, password));
}

void UserManager::logout() {
    loggedInUser = nullptr;
}


User* UserManager::findUser(const std::string& email) {
    for (auto& user: users) {
        if (user->emailMatches(email)) {
            return user;
        }
    }
    return nullptr;
}


bool UserManager::isUserLoggedIn() {
    return loggedInUser != nullptr;
}

