CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = includes
CFLAGS = -std=c++11 -Wall -Werror -I$(INCLUDE_DIR)

EXECUTABLE_FILE = UTRIP.out

OBJECTS = \
	$(BUILD_DIR)/Hotel.o \
	$(BUILD_DIR)/Main.o \
	$(BUILD_DIR)/Tools.o \
	$(BUILD_DIR)/Wallet.o \
	$(BUILD_DIR)/RoomService.o \
	$(BUILD_DIR)/Room.o \
	$(BUILD_DIR)/Interface.o \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/Utrip.o \
	$(BUILD_DIR)/User.o \
	$(BUILD_DIR)/UserManager.o \
	$(BUILD_DIR)/HotelManager.o


HotelSensitivityList = \
	$(SRC_DIR)/Hotel.cpp \
	$(INCLUDE_DIR)/Hotel.hpp \
	$(INCLUDE_DIR)/RoomService.hpp \
	$(INCLUDE_DIR)/constants.hpp

HotelManagerSensitivityList = \
	$(SRC_DIR)/HotelManager.cpp \
	$(INCLUDE_DIR)/HotelManager.h \
	$(INCLUDE_DIR)/constants.hpp \
	$(INCLUDE_DIR)/Hotel.hpp \
	$(INCLUDE_DIR)/Tools.hpp

UtripSensitivityList = \
	$(SRC_DIR)/Utrip.cpp \
	$(INCLUDE_DIR)/Utrip.h \
	$(INCLUDE_DIR)/UserManager.h \
	$(INCLUDE_DIR)/Exception.hpp \
	$(INCLUDE_DIR)/constants.hpp \
	$(INCLUDE_DIR)/Tools.hpp

UserSensitivityList = \
	$(SRC_DIR)/User.cpp \
	$(INCLUDE_DIR)/User.h

UserManagerSensitivityList = \
    $(SRC_DIR)/UserManager.cpp \
    $(INCLUDE_DIR)/UserManager.h \
    $(INCLUDE_DIR)/User.h \
    $(INCLUDE_DIR)/Exception.hpp


ToolsSensitivityList = \
	$(SRC_DIR)/Tools.cpp \
	$(INCLUDE_DIR)/Tools.hpp \
	$(INCLUDE_DIR)/constants.hpp \
	$(INCLUDE_DIR)/Exception.hpp


InterfaceSensitivityList = \
    $(SRC_DIR)/Interface.cpp \
    $(INCLUDE_DIR)/Interface.h \
    $(INCLUDE_DIR)/Utrip.h

CommandHandlerSensitivityList = \
    $(SRC_DIR)/CommandHandler.cpp \
    $(INCLUDE_DIR)/CommandHandler.hpp \
    $(INCLUDE_DIR)/constants.hpp \
    $(INCLUDE_DIR)/Tools.hpp \
    $(INCLUDE_DIR)/Exception.hpp \
    $(INCLUDE_DIR)/Interface.h \
    $(INCLUDE_DIR)/Request.hh


RoomServiceSensitivityList = \
	$(SRC_DIR)/RoomService.cpp \
	$(INCLUDE_DIR)/RoomService.hpp \
	$(INCLUDE_DIR)/Room.h

RoomSensitivityList = \
	$(SRC_DIR)/Room.cpp \
	$(INCLUDE_DIR)/Room.h

WalletSensitivityList = \
	$(SRC_DIR)/Wallet.cpp \
	$(INCLUDE_DIR)/Wallet.hpp \
	$(INCLUDE_DIR)/Exception.hpp \
	$(INCLUDE_DIR)/constants.hpp

MainSensitivityList = \
	$(SRC_DIR)/Main.cpp \
	$(INCLUDE_DIR)/CommandHandler.hpp \
	$(INCLUDE_DIR)/constants.hpp

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Hotel.o: $(HotelSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Hotel.cpp -o $(BUILD_DIR)/Hotel.o

$(BUILD_DIR)/Tools.o: $(ToolsSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Tools.cpp -o $(BUILD_DIR)/Tools.o

$(BUILD_DIR)/Wallet.o: $(WalletSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Wallet.cpp -o $(BUILD_DIR)/Wallet.o

$(BUILD_DIR)/RoomService.o: $(RoomServiceSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/RoomService.cpp -o $(BUILD_DIR)/RoomService.o

$(BUILD_DIR)/Room.o: $(RoomSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Room.cpp -o $(BUILD_DIR)/Room.o

$(BUILD_DIR)/Main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.cpp -o $(BUILD_DIR)/Main.o


$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o

$(BUILD_DIR)/Interface.o: $(InterfaceSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Interface.cpp -o $(BUILD_DIR)/Interface.o

$(BUILD_DIR)/Utrip.o: $(UtripSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Utrip.cpp -o $(BUILD_DIR)/Utrip.o

$(BUILD_DIR)/User.o: $(UserSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/UserManager.o: $(UserManagerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/UserManager.cpp -o $(BUILD_DIR)/UserManager.o

$(BUILD_DIR)/HotelManager.o: $(HotelManagerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/HotelManager.cpp -o $(BUILD_DIR)/HotelManager.o


$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
