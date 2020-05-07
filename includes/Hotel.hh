#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <utility>

#include "Constants.hh"
#include "RoomService.hh"
#include "City.hh"

#define NumOfRatingFields std::size_t(6)

class Hotel
{
public:
    class Comment
    {
        std::string username;
        std::string comment;

    public:
        Comment(const std::string &username, const std::string &comment)
            : username(username),
              comment(comment)
        {
        }

        const std::string &getUsername() const
        {
            return username;
        }

        const std::string &getComment() const
        {
            return comment;
        }
    };

    struct RatingData
    {
        using DataType = std::array<double, NumOfRatingFields>;

        RatingData() : ratesData()
        {
            for (auto data : ratesData)
                data = 0;
        }

        const DataType &getRatingData() const
        {
            return ratesData;
        }

        DataType &getRatingData()
        {
            return ratesData;
        }

    private:
        DataType ratesData;
    };

    using CommentList = std::vector<Comment>;
    using RatesList = std::unordered_map<std::string, RatingData>;

    Hotel(const std::string &hotelId,
          std::string hotelName,
          std::size_t hotelRating,
          std::string hotelOverview,
          Amenities amenities, City city,
          std::string imageUrl,
          int numOfStandardRooms,
          int numOfDeluxeRooms,
          int numOfLuxuryRooms,
          int numOfPremiumRooms,
          double standardRoomPrice,
          double deluxeRoomPrice,
          double luxuryRoomPrice,
          double premiumRoomPrice);
    void print() const;
    std::string getAmenities() const;

    std::string getId() const
    {
        return hotelId;
    };

    std::string getHotelName() const 
    {
        return hotelName;
    }

    std::string getCityName() const 
    {
        return city.cityName;
    }

    int getNumOfStandardRooms() const { return roomService.getNumOfStandardRooms(); }
    int getNumOfDeluxeRooms() const { return roomService.getNumOfDeluxeRooms(); }
    int getNumOfLuxuryRooms() const { return roomService.getNumOfLuxuryRooms(); }
    int getNumOfPremiumRooms() const { return roomService.getNumOfPremiumRooms(); }

    double getStandardRoomPrice() const { return roomService.getPriceOfStandardRooms(); }
    double getDeluxeRoomPrice() const { return roomService.getPriceOfDeluxeRooms(); }
    double getLuxuryRoomPrice() const { return roomService.getPriceOfLuxuryRooms(); }
    double getPremiumRoomPrice() const { return roomService.getPriceOfPremiumRooms(); }

    void printBriefly() const;

    bool idsMatches(const std::string &hotelId) const;

    const City &getCity() const
    {
        return city;
    }

    City &getCity()
    {
        return city;
    }

    std::uint8_t getStar() const
    {
        return starRating;
    }

    const RoomService &getRoomService() const
    {
        return roomService;
    }

    RoomService &getRoomService()
    {
        return roomService;
    }

    template <typename... Args>
    void addComment(const Args &... args)
    {
        comments.emplace_back(args...);
    }

    const CommentList &getComments() const
    {
        return comments;
    }

    void addRating(const std::string &username, const RatingData::DataType &addedRate)
    {
        std::copy(addedRate.begin(), addedRate.end(), rates[username].getRatingData().begin());
    }

    RatingData::DataType getRating() const
    {
        RatingData::DataType averageRating;
        for (auto &data : averageRating)
            data = 0;

        for (const auto &rate : rates)
            for (std::size_t i = 0; i < NumOfRatingFields; ++i)
                averageRating[i] += rate.second.getRatingData()[i];

        return averageRating;
    }

private:
    std::string hotelId;
    std::string hotelName;
    std::size_t starRating;
    std::string hotel_overview; // TODO
    Amenities amenities;
    City city;
    std::string image_url; // TODO
    RoomService roomService;
    CommentList comments;
    RatesList rates;
};
