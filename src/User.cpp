//
// Created by zhivar on 4/17/20.
//

#include "../includes/User.h"

User::User(std::string _email, std::string _username, std::string _password) {
    email = _email;
    username = _username;
    password = _password;
}


bool User::emailMatches(std::string _email) {
    return email == _email;
}

bool User::passwordMatches(std::string _password) {
    return password == _password;
}
