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

    void runSignupCommand(const std::vector<std::string> &vector);

    void runLoginCommand(const std::vector<std::string> &vector);

    void runLogoutCommand(const std::vector<std::string> &vector);

private:
    Utrip* utrip;

};

#endif //UT_AP_S99_FINAL_INTERFACE_H
