//
// Created by zhivar on 4/17/20.
//

#ifndef UT_AP_S99_FINAL_INTERFACE_H
#define UT_AP_S99_FINAL_INTERFACE_H

#include <string>
#include <vector>


class Utrip;

class Interface {
public:
    Interface();


    void runLoginCommand(const std::string &email, const std::string &password);

    void runSignupCommand(const std::string &email, const std::string &username, const std::string &password);

    void runLogoutCommand();

    void runHotelsImport(const std::string &basicString);

    void runWalletCommand(const std::string &amount);

private:

    Utrip* utrip;
};

#endif //UT_AP_S99_FINAL_INTERFACE_H
