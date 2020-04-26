cmake_minimum_required(VERSION 3.16)
project(ut_ap_s99_final)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

add_executable(ut_ap_s99_final
    includes/CommandHandler.hpp
    includes/constants.hh
    includes/Exception.hh
    includes/Hotel.hh
    includes/ReservationTime.hpp
        includes/RoomService.hpp
    includes/Tools.hh
    includes/Wallet.hh
    src/CommandHandler.cpp
    src/Hotel.cpp
    src/Main.cpp
        src/RoomService.cpp
    src/Tools.cpp
    src/Wallet.cpp src/Interface.cpp includes/Interface.hh includes/Utrip.h src/Utrip.cpp includes/User.h src/User.cpp includes/UserManager.hh src/UserManager.cpp includes/HotelManager.hh src/HotelManager.cpp includes/Room.hh src/Room.cpp)
