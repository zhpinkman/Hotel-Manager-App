#include "../includes/Exception.hh"
#include "../includes/Wallet.hh"
#include "../includes/Constants.hh"
#include <iostream>

using namespace std;

Wallet::Wallet(int _id)
{
  balance = 0;
  id = _id;
}

vector<double> Wallet::getHistory(unsigned int bound)
{
  vector<double> walletHistory;
  for (unsigned int i = 0; i < bound && i < history.size(); i++)
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
    throw BadRequestException();
  }
}

void Wallet::withdraw(double amount)
{
  balance -= amount;
  history.push_back(balance);
}

bool Wallet::hasEnoughMoney(double money) { return money <= balance; }