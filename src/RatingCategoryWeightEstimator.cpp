#include "RatingCategoryWeightEstimator.hh"
#include "Utility.hh"

#include <cmath>
#include <iostream>

using namespace std;
using namespace utility;

CategoryToWeightMap RatingCategoryWeightEstimator::estimate(vector<HotelRatings> ratings) 
{
    vector<double> rawResult = estimate(unwrapRatingsList(ratings));
    CategoryToWeightMap result;
    /* 
     * the -1 in the following line, is because the "overall" category has no weights
     * associated with it, and it is guaranteed to always be the last category in 
     * HotelRatings::categories.
     */
    for (int i = 0; i < HotelRatings::categories.size()-1; i++) { 
        result[HotelRatings::categories[i]] = rawResult[i];
    }
    return result;
}

vector<double> RatingCategoryWeightEstimator::estimate(vector<vector<double>> ratingsList) 
{
    vector<vector<double>> individualRatingsList;
    vector<double> overallRatings;
    splitRatings(ratingsList, individualRatingsList, overallRatings);

    vector<double> estimatedWeights = {3.85, 1.2, 3.94, 1.47, 4.8}; //randomUniform(1., 5., 5); 

    for (int epoch = 0; epoch < this->nEpochs; epoch++) {
        vector<double> derivativeSums(individualRatingsList[0].size(),0.);
        for (int i = 0; i < individualRatingsList.size(); i++) {
            derivativeSums = vectorSum(derivativeSums,
                weightDerivatives(individualRatingsList[i], estimatedWeights, overallRatings[i]));
        }
        estimatedWeights = vectorDifference(estimatedWeights, vectorScale(derivativeSums, this->learningRate));
        estimatedWeights = vectorClamp(estimatedWeights, 1., 5.);
    }

    return estimatedWeights;
}

RatingCategoryWeightEstimator::RatingCategoryWeightEstimator() :
    nEpochs(500), learningRate(1.), epsilon(1e-4) {}


double RatingCategoryWeightEstimator::guessOverallRating(std::vector<double> ratings, std::vector<double> currentWeights) const {
    return weightedAverage(ratings, currentWeights);
}

double RatingCategoryWeightEstimator::errorFunction(vector<double> ratings, vector<double> currentWeights, double overallRating) const {
    return pow(guessOverallRating(ratings, currentWeights) - overallRating, 2.);
}

void RatingCategoryWeightEstimator::splitRatings(std::vector<std::vector<double>> ratingsList,
    std::vector<std::vector<double>>& individualRatingsList, std::vector<double>& overallRatings) const {
    for (vector<double> ratings: ratingsList) {
        individualRatingsList.push_back(vector<double>(ratings.begin(), ratings.end()-1));
        overallRatings.push_back(ratings.back());
    }
}

vector<double> RatingCategoryWeightEstimator::weightDerivatives(vector<double> individualRatings, vector<double> weights,
    double overallRating) const {
    vector<double> result;
    for (int i = 0; i < weights.size(); i++) {
        result.push_back(weightDerivative(individualRatings, weights, overallRating, i));
    }
    return result;
}

double RatingCategoryWeightEstimator::weightDerivative(vector<double> individualRatings, vector<double> weights,
    double overallRating, int targetWeightIndex) const {
    
    double y1 = errorFunction(individualRatings, weights, overallRating);
    weights[targetWeightIndex] += epsilon;
    double y2 = errorFunction(individualRatings, weights, overallRating);
    return (y2 - y1) / epsilon;
}


vector<double> RatingCategoryWeightEstimator::unwrapRatings(HotelRatings ratings) const
{
    vector<double> unwrappedRating;
    for (string category: HotelRatings::categories) {
        unwrappedRating.push_back(ratings.getRating(category));
    }
    return unwrappedRating;
}

vector<vector<double>> RatingCategoryWeightEstimator::unwrapRatingsList(vector<HotelRatings> ratingsList) const {
    vector<vector<double>> result;
    for (HotelRatings wrappedRatings: ratingsList) {
        result.push_back(unwrapRatings(wrappedRatings));
    }
    return result;
}
