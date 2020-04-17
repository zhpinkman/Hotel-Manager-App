//
// Created by zhivar on 4/17/20.
//

#ifndef UT_AP_S99_FINAL_UTRIP_H
#define UT_AP_S99_FINAL_UTRIP_H


class Utrip{
public:
    Utrip();

    void signup(std::string email, std::string username, std::string password);

    void login(std::string email, std::string password);

    void logout();

private:
};

#endif //UT_AP_S99_FINAL_UTRIP_H
