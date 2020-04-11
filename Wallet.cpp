#include <iostream>
#include "Wallet.hpp"
#include "constants.hpp"
#include "Exceptions.hpp"
using namespace std;

Wallet::Wallet(int _id)
{
    balance = 0;
    id = _id;
}

vector<double> Wallet::getHistory(int bound)
{
    vector<double> walletHistory;
    int historyIndex = 0;
    for (int i = 0; i < bound && i < history.size(); i++)
    {
        walletHistory.push_back(history[history.size() - 1 - i]);
    }
    return walletHistory;
}

void Wallet::charge(double amount)
{
    if (amount > 0)
    {
        balance += amount;
        history.push_back(balance);
        cout << OK << '\n';
    }
    else
    {
        throw Bad_Request_Exception();
    }
}

void Wallet::withdraw(double amount)
{
    balance -= amount;
    history.push_back(balance);
}

bool Wallet::hasEnoughMoney(double money)
{
    return money <= balance;
}