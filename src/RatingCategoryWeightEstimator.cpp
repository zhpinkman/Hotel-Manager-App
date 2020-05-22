#include "RatingCategoryWeightEstimator.hh"
#include "Utility.hh"

#include <cmath>
#include <iostream>
#include <exception>

using namespace std;
using namespace utility;

HotelRatingWeights RatingCategoryWeightEstimator::estimate(vector<HotelRatings> ratings) 
{
    if (ratings.size() == 0)
        throw invalid_argument("RatingCategoryWeightEstimator::estimate: ratings cannot be empty.");
        
    vector<double> rawResult = estimate(unwrapRatingsList(ratings));
    HotelRatingWeights result;
    for (int i = 0; i < HotelRatingWeights::categories.size(); i++)
        result.setWeight(HotelRatingWeights::categories[i], rawResult[i]);
    return result;
}

vector<double> RatingCategoryWeightEstimator::estimate(vector<vector<double>> ratingsList) 
{
    cout<<"main estimate:"<<ratingsList.size()<<endl;
    for (int i = 0; i < ratingsList.size(); i++) 
        cout<<vec2str(ratingsList[i])<<endl;

    vector<vector<double>> individualRatingsList;
    vector<double> overallRatings;
    splitRatings(ratingsList, individualRatingsList, overallRatings);

    vector<double> estimatedWeights = randomUniform(1., 5., 5);

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
