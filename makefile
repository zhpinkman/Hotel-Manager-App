CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = includes
CFLAGS = -std=c++11 -g -I $(INCLUDE_DIR)

EXECUTABLE_FILE = utrip.out

# PATTERN RULES:

# 1- Compiling object files from correspoding cpp files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# 2- Updating .h files. This rule is needed so that every file only includes the header files
# it directly depends on, and doesn't have to worry about indirect header dependencies.
%.hh:
	@touch $@


LIB_OBJECTS = \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/Filter.o \
	$(BUILD_DIR)/Hotel.o \
	$(BUILD_DIR)/HotelManager.o \
	$(BUILD_DIR)/HotelRatings.o \
	$(BUILD_DIR)/RatingCategoryWeightEstimator.o \
	$(BUILD_DIR)/RoomService.o \
	$(BUILD_DIR)/Sort.o \
	$(BUILD_DIR)/User.o \
	$(BUILD_DIR)/Utility.o \
	$(BUILD_DIR)/Utrip.o 

OBJECTS = $(LIB_OBJECTS) $(BUILD_DIR)/Main.o


all: $(BUILD_DIR) $(EXECUTABLE_FILE)


$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/test

# object file entries:

$(BUILD_DIR)/CommandHandler.o: $(SRC_DIR)/CommandHandler.cpp \
	$(INCLUDE_DIR)/CommandHandler.hh \
	$(INCLUDE_DIR)/Constants.hh \
	$(INCLUDE_DIR)/Exception.hh \
	$(INCLUDE_DIR)/Interface.hh \
	$(INCLUDE_DIR)/Request.hh

$(BUILD_DIR)/Filter.o: $(SRC_DIR)/Filter.cpp \
	$(INCLUDE_DIR)/Filter.hh \
	$(INCLUDE_DIR)/Utrip.hh

$(BUILD_DIR)/Hotel.o: $(SRC_DIR)/Hotel.cpp \
	$(INCLUDE_DIR)/Hotel.hh \
	$(INCLUDE_DIR)/RoomService.hh \
	$(INCLUDE_DIR)/Constants.hh \
	$(INCLUDE_DIR)/User.hh \
	$(INCLUDE_DIR)/Utrip.hh \
	$(INCLUDE_DIR)/Utility.hh

$(BUILD_DIR)/HotelManager.o: $(SRC_DIR)/HotelManager.cpp \
	$(INCLUDE_DIR)/HotelManager.hh \
	$(INCLUDE_DIR)/Constants.hh \
	$(INCLUDE_DIR)/Hotel.hh \
	$(INCLUDE_DIR)/Utility.hh \
	$(INCLUDE_DIR)/Location.hh \
	$(INCLUDE_DIR)/HotelRatings.hh

$(BUILD_DIR)/HotelRatings.o: $(SRC_DIR)/HotelRatings.cpp \
	$(INCLUDE_DIR)/HotelRatings.hh \
	$(INCLUDE_DIR)/Utility.hh

$(BUILD_DIR)/Main.o: $(SRC_DIR)/Main.cpp \
	$(INCLUDE_DIR)/CommandHandler.hh

$(BUILD_DIR)/RatingCategoryWeightEstimator.o: $(SRC_DIR)/RatingCategoryWeightEstimator.cpp \
	$(INCLUDE_DIR)/RatingCategoryWeightEstimator.hh \
	$(INCLUDE_DIR)/Utility.hh

$(BUILD_DIR)/RoomService.o: $(SRC_DIR)/RoomService.cpp \
	$(INCLUDE_DIR)/RoomService.hh

$(BUILD_DIR)/Sort.o: $(SRC_DIR)/Sort.cpp \
	$(INCLUDE_DIR)/Sort.hh \
	$(INCLUDE_DIR)/Utrip.hh

$(BUILD_DIR)/User.o: $(SRC_DIR)/User.cpp \
	$(INCLUDE_DIR)/User.hh \
	$(INCLUDE_DIR)/Utrip.hh \
	$(INCLUDE_DIR)/RatingCategoryWeightEstimator.hh

$(BUILD_DIR)/Utility.o: $(SRC_DIR)/Utility.cpp \
	$(INCLUDE_DIR)/Utility.hh \
	$(INCLUDE_DIR)/Exception.hh \
	$(INCLUDE_DIR)/Constants.hh

$(BUILD_DIR)/Utrip.o: $(SRC_DIR)/Utrip.cpp \
	$(INCLUDE_DIR)/Utrip.hh \
	$(INCLUDE_DIR)/Utility.hh \
	$(INCLUDE_DIR)/User.hh


# header file entries:

$(INCLUDE_DIR)/CommandHandler.hh: $(INCLUDE_DIR)/Interface.hh \
	$(INCLUDE_DIR)/Request.hh

$(INCLUDE_DIR)/Constants.hh: # nothing

$(INCLUDE_DIR)/Exception.hh: # nothing

$(INCLUDE_DIR)/Filter.hh: $(INCLUDE_DIR)/Hotel.hh

$(INCLUDE_DIR)/Hotel.hh: $(INCLUDE_DIR)/Constants.hh \
	$(INCLUDE_DIR)/RoomService.hh \
	$(INCLUDE_DIR)/Location.hh \
	$(INCLUDE_DIR)/HotelRatings.hh

$(INCLUDE_DIR)/HotelManager.hh: $(INCLUDE_DIR)/Constants.hh \
	$(INCLUDE_DIR)/Hotel.hh \
	$(INCLUDE_DIR)/Exception.hh 

$(INCLUDE_DIR)/HotelRatings.hh: $(INCLUDE_DIR)/Utility.hh

$(INCLUDE_DIR)/Interface.hh: $(INCLUDE_DIR)/Utrip.hh \
	$(INCLUDE_DIR)/Request.hh \
	$(INCLUDE_DIR)/Exception.hh \
	$(INCLUDE_DIR)/HotelRatings.hh \
	$(INCLUDE_DIR)/Utility.hh

$(INCLUDE_DIR)/Location.hh: # nothing

$(INCLUDE_DIR)/RatingCategoryWeightEstimator.hh: $(INCLUDE_DIR)/HotelRatings.hh

$(INCLUDE_DIR)/Request.hh: $(INCLUDE_DIR)/Exception.hh

$(INCLUDE_DIR)/RoomService.hh: $(INCLUDE_DIR)/Exception.hh

$(INCLUDE_DIR)/Sort.hh: $(INCLUDE_DIR)/Hotel.hh

$(INCLUDE_DIR)/User.hh: $(INCLUDE_DIR)/Exception.hh \
	$(INCLUDE_DIR)/HotelRatings.hh \
	$(INCLUDE_DIR)/Hotel.hh

$(INCLUDE_DIR)/UserManager.hh: $(INCLUDE_DIR)/User.hh \
	$(INCLUDE_DIR)/Exception.hh

$(INCLUDE_DIR)/Utrip.hh: $(INCLUDE_DIR)/UserManager.hh \
	$(INCLUDE_DIR)/HotelManager.hh \
	$(INCLUDE_DIR)/Filter.hh \
	$(INCLUDE_DIR)/Sort.hh $(INCLUDE_DIR)/Hotel.hh \
	$(INCLUDE_DIR)/Exception.hh \
	$(INCLUDE_DIR)/Constants.hh \
	$(INCLUDE_DIR)/HotelManager.hh \
	$(INCLUDE_DIR)/RoomService.hh \
	$(INCLUDE_DIR)/HotelRatings.hh



# TEST_BUILD_DIR = $(BUILD_DIR)/test
# TEST_DIR = test
# TEST_CCFLAGS = $(CFLAGS) -I/usr/local/include -I/usr/include/ -Itest/

# test-all: $(BUILD_DIR) $(TEST_BUILD_DIR)/test-utrip.out

# TESTS_OBJS = $(TEST_BUILD_DIR)/TestSignup.o

# $(SRC_DIR)/$(TEST_BUILD_DIR)/test-utrip.out: $(LIB_OBJECTS) $(TEST_DIR)/Main.cpp $(TESTS_OBJS)
# $(SRC_DIR)/	$(CC) $(TEST_DIR)/Main.cpp \
# 	$(LIB_OBJECTS) \
# 	$(TESTS_OBJS) \
# 	$(TEST_CCFLAGS) -lgtest -lgtest_main -pthread -o $(TEST_BUILD_DIR)/test-utrip.out


# $(SRC_DIR)/$(TEST_BUILD_DIR)/TestSignup.o: $(TEST_DIR)/TestFixture.hh $(TEST_DIR)/TestSignup.cpp
# $(SRC_DIR)/	$(CC) -c $(TEST_CCFLAGS) $(TEST_DIR)/TestSignup.cpp -o $(TEST_BUILD_DIR)/TestSignup.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
