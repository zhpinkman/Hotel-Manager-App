#ifndef _WALLET_H_
#define _WALLET_H_

#include <string>
#include <vector>

class Wallet
{
public:
    Wallet(int id);
    std::vector<double> getHistory(int bound);
    void charge(double amount);
    void withdraw(double amount);
    bool hasEnoughMoney(double money);

private:
    int id;
    double balance;
    std::vector<double> history;
};

#endif