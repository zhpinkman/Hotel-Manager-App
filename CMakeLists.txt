cmake_minimum_required(VERSION 3.16)
project(ut_ap_s99_final)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

add_executable(ut_ap_s99_final
    includes/CommandHandler.hpp
    includes/constants.hpp
    includes/Exception.hpp
    includes/Hotel.hpp
    includes/Reservation_time.hpp
        includes/RoomService.hpp
    includes/Tools.hpp
    includes/Wallet.hpp
    src/CommandHandler.cpp
    src/Hotel.cpp
    src/Main.cpp
        src/RoomService.cpp
    src/Tools.cpp
    src/Wallet.cpp src/Interface.cpp includes/Interface.h includes/Utrip.h src/Utrip.cpp includes/User.h src/User.cpp includes/UserManager.h src/UserManager.cpp includes/HotelManager.h src/HotelManager.cpp includes/Room.h src/Room.cpp)
