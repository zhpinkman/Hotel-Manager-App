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
	$(BUILD_DIR)/Room_service.o \
	$(BUILD_DIR)/Room.o \
	$(BUILD_DIR)/Interface.o \
	$(BUILD_DIR)/CommandHandler.o

HotelSensitivityList = \
	$(SRC_DIR)/Hotel.cpp \
	$(INCLUDE_DIR)/Room_service.hpp

ToolsSensitivityList = \
	$(SRC_DIR)/Tools.cpp \
	$(INCLUDE_DIR)/Tools.hpp \
	$(INCLUDE_DIR)/constants.hpp \
	$(INCLUDE_DIR)/Exception.hpp


InterfaceSensitivityList = \
    $(SRC_DIR)/Interface.cpp \
    $(INCLUDE_DIR)/Interface.h

CommandHandlerSensitivityList = \
    $(SRC_DIR)/CommandHandler.cpp \
    $(INCLUDE_DIR)/CommandHandler.hpp


RoomServiceSensitivityList = \
	$(SRC_DIR)/Room_service.cpp \
	$(INCLUDE_DIR)/Room_service.hpp \
	$(INCLUDE_DIR)/Room.hpp 

RoomSensitivityList = \
	$(SRC_DIR)/Room.cpp \
	$(INCLUDE_DIR)/Room.hpp \
	$(INCLUDE_DIR)/Reservation_time.hpp 

WalletSensitivityList = \
	$(SRC_DIR)/Wallet.cpp \
	$(INCLUDE_DIR)/Wallet.hpp \
	$(INCLUDE_DIR)/Exception.hpp \
	$(INCLUDE_DIR)/constants.hpp

MainSensitivityList = \
	$(SRC_DIR)/Main.cpp

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Hotel.o: $(HotelSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Hotel.cpp -o $(BUILD_DIR)/Hotel.o

$(BUILD_DIR)/Tools.o: $(ToolsSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Tools.cpp -o $(BUILD_DIR)/Tools.o

$(BUILD_DIR)/Wallet.o: $(WalletSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Wallet.cpp -o $(BUILD_DIR)/Wallet.o

$(BUILD_DIR)/Room_service.o: $(RoomServiceSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Room_service.cpp -o $(BUILD_DIR)/Room_service.o

$(BUILD_DIR)/Room.o: $(RoomSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Room.cpp -o $(BUILD_DIR)/Room.o

$(BUILD_DIR)/Main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.cpp -o $(BUILD_DIR)/Main.o


$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o


$(BUILD_DIR)/Interface.o: $(InterfaceSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Interface.cpp -o $(BUILD_DIR)/Interface.o



$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
