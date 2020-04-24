//
// Created by zhivar on 4/17/20.
//

#ifndef UT_AP_S99_FINAL_USERMANAGER_H
#define UT_AP_S99_FINAL_USERMANAGER_H

#include <vector>
#include <string>

class User;

class UserManager
{
public:
    UserManager();
    void login(const User &user);
    void signup(const User &user);
    void logout();

    bool isUserLoggedIn();

    void getWallet(double amount);

private:
    User *loggedInUser;

    std::vector<User *> users;

    User *findUser(const std::string &email);
};

#endif //UT_AP_S99_FINAL_USERMANAGER_H
