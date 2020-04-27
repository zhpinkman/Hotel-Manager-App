#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <array>

#include "Constants.hh"
#include "RoomService.hh"

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

    template <std::size_t NumOfRatingFields = 6>
    class RatingData
    {
    };

    using CommentList = std::vector<Comment>;

    Hotel(const std::string &hotelId, std::string hotelName, std::uint8_t hotelRating, std::string hotelOverview,
          Amenities amenities, City city, std::string imageUrl, int numOfStandardRooms,
          int numOfDeluxeRooms, int numOfLuxuryRooms, int numOfPremiumRooms,
          double standardRoomPrice, double deluxeRoomPrice, double luxuryRoomPrice,
          double premiumRoomPrice);
    void print() const;
    std::string getAmenities() const;

    std::string getId() const
    {
        return hotelId;
    };

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
        return hotelRating;
    }

    const RoomService *const getRoomService() const
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

private:
    std::string hotelId;
    std::string hotelName;
    std::uint8_t hotelRating;
    std::string hotel_overview; // TODO
    Amenities amenities;
    City city;
    std::string image_url; // TODO
    RoomService *roomService;
    CommentList comments;
};
