#pragma once

#include "HotelRatings.hh"


class RatingCategoryWeightEstimator {
public:
    HotelRatingWeights estimate(std::vector<HotelRatings> ratings);
    RatingCategoryWeightEstimator();

private:
    std::vector<double> estimate(std::vector<std::vector<double>> ratingsList);
    double guessOverallRating(std::vector<double> ratings, std::vector<double> currentWeights) const;
    double errorFunction(std::vector<double> ratings, std::vector<double> currentWeights, double overallRating) const;
    void splitRatings(std::vector<std::vector<double>> ratingsList, std::vector<std::vector<double>>& individualRatingsList,
        std::vector<double>& overallRatings) const;
    std::vector<double> weightDerivatives(std::vector<double> individualRatings, std::vector<double> weights, double overallRating) const;
    double weightDerivative(std::vector<double> individualRatings, std::vector<double> weights, double overallRating, int targetWeightIndex) const;

    /* 
     * Wrapping means converting a HotelRatings object into a vector of doubles, using the order defined by
     * HotelRatings::categories. Unwrapping is done prior to running the estimation algorithm in order to reduce
     * the overhead of constantly accessing the ratings via the HotelRatings interface, which uses a dictionary 
     * under the hood.
     */
    std::vector<double> unwrapRatings(HotelRatings ratings) const;
    std::vector<std::vector<double>> unwrapRatingsList(std::vector<HotelRatings> ratingsList) const;

    const int nEpochs;
    const double learningRate, epsilon;
};
