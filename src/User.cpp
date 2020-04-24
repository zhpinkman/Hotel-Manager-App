//
// Created by zhivar on 4/17/20.
//

#include <iostream>
#include "../includes/User.hh"

User::User(std::string _email, std::string _username, std::string _password)
{
    email = _email;
    username = _username;
    password = _password;
    balance = 0;
    balanceHistory.push_back(balance);
}

bool User::emailMatches(std::string _email) const
{
    return email == _email;
}

bool User::passwordMatches(std::string _password) const
{
    return password == _password;
}

void User::getWallet(double amount) const
{
    int balanceSize = balanceHistory.size();
    for (int i = balanceSize - 1; i >= std::max(balanceSize - amount, 0.0); i--)
    {
        std::cout << balanceHistory[i] << std::endl;
    }
}
