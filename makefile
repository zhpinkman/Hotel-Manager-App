CC = clang++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = includes
CFLAGS = -std=c++11 -Wall -Werror -g -I$(INCLUDE_DIR)

EXECUTABLE_FILE = UTRIP.out

LIB_OBJECTS = \
	$(BUILD_DIR)/Hotel.o \
	$(BUILD_DIR)/Tools.o \
	$(BUILD_DIR)/Wallet.o \
	$(BUILD_DIR)/RoomService.o \
	$(BUILD_DIR)/Room.o \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/HotelManager.o

OBJECTS = $(LIB_OBJECTS) $(BUILD_DIR)/Main.o

HotelSensitivityList = \
	$(SRC_DIR)/Hotel.cpp \
	$(INCLUDE_DIR)/Hotel.hh \
	$(INCLUDE_DIR)/RoomService.hh \
	$(INCLUDE_DIR)/Constants.hh

HotelManagerSensitivityList = \
	$(SRC_DIR)/HotelManager.cpp \
	$(INCLUDE_DIR)/HotelManager.hh \
	$(INCLUDE_DIR)/Constants.hh \
	$(INCLUDE_DIR)/Hotel.hh \
	$(INCLUDE_DIR)/Tools.hh

ToolsSensitivityList = \
	$(SRC_DIR)/Tools.cpp \
	$(INCLUDE_DIR)/Tools.hh \
	$(INCLUDE_DIR)/Constants.hh \
	$(INCLUDE_DIR)/Exception.hh


CommandHandlerSensitivityList = \
    $(SRC_DIR)/CommandHandler.cpp \
    $(INCLUDE_DIR)/CommandHandler.hh \
    $(INCLUDE_DIR)/Constants.hh \
    $(INCLUDE_DIR)/Tools.hh \
    $(INCLUDE_DIR)/Exception.hh \
    $(INCLUDE_DIR)/Interface.hh \
    $(INCLUDE_DIR)/Request.hh


RoomServiceSensitivityList = \
	$(SRC_DIR)/RoomService.cpp \
	$(INCLUDE_DIR)/RoomService.hh \
	$(INCLUDE_DIR)/Room.hh

RoomSensitivityList = \
	$(SRC_DIR)/Room.cpp \
	$(INCLUDE_DIR)/Room.hh

WalletSensitivityList = \
	$(SRC_DIR)/Wallet.cpp \
	$(INCLUDE_DIR)/Wallet.hh \
	$(INCLUDE_DIR)/Exception.hh \
	$(INCLUDE_DIR)/Constants.hh

MainSensitivityList = \
	$(SRC_DIR)/Main.cpp \
	$(INCLUDE_DIR)/CommandHandler.hh \
	$(INCLUDE_DIR)/Constants.hh

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/test

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

$(BUILD_DIR)/HotelManager.o: $(HotelManagerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/HotelManager.cpp -o $(BUILD_DIR)/HotelManager.o


$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

TEST_BUILD_DIR = $(BUILD_DIR)/test
TEST_DIR = test
TEST_CCFLAGS = $(CFLAGS) -I/usr/local/include -I/usr/include/ -Itest/

test-all: $(BUILD_DIR) $(TEST_BUILD_DIR)/test-utrip.out

TESTS_OBJS = $(TEST_BUILD_DIR)/TestSignup.o

$(TEST_BUILD_DIR)/test-utrip.out: $(LIB_OBJECTS) $(TEST_DIR)/Main.cpp $(TESTS_OBJS)
	$(CC) $(TEST_DIR)/Main.cpp \
	$(LIB_OBJECTS) \
	$(TESTS_OBJS) \
	$(TEST_CCFLAGS) -lgtest -lgtest_main -pthread -o $(TEST_BUILD_DIR)/test-utrip.out


$(TEST_BUILD_DIR)/TestSignup.o: $(TEST_DIR)/TestFixture.hh $(TEST_DIR)/TestSignup.cpp
	$(CC) -c $(TEST_CCFLAGS) $(TEST_DIR)/TestSignup.cpp -o $(TEST_BUILD_DIR)/TestSignup.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
