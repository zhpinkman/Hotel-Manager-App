//
// Created by zhivar on 4/17/20.
//

#ifndef UT_AP_S99_FINAL_USERMANAGER_H
#define UT_AP_S99_FINAL_USERMANAGER_H

#include <vector>
#include <string>

class User;

class UserManager {
public:
    UserManager();
    void login(std::string email, std::string password);
    void signup(std::string email, std::string username, std::string password);
    void logout();

    bool isUserLoggedIn();

private:
    User* loggedInUser;
    std::vector<User*> users;

    User *findUser(std::string email);

};

#endif //UT_AP_S99_FINAL_USERMANAGER_H
