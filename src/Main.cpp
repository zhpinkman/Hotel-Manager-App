#include "../includes/CommandHandler.hh"
#include "../includes/Constants.hh"
#include <cstdlib>
#include <iostream>
#include <string>


// int main(int argc, char const *argv[]) {
//   constexpr std::size_t HOTELS_FILE_INDEX = 1;
//   constexpr std::size_t RATINGS_FILE_INDEX = 2;

//   CommandHandler *commandHandler =
//       new CommandHandler(argv[HOTELS_FILE_INDEX], argv[RATINGS_FILE_INDEX]);
//   commandHandler->start();
//   return 0;
// }


#include "Utility.hh"
#include "RatingCategoryWeightEstimator.hh"

using namespace std;

int main() {
  vector<HotelRatings> ratingsList = {
    HotelRatings(2.1, 1.6, 4.6, 2.3, 1.5, 2.58),
    HotelRatings(4.2, 1.8, 2.9, 2.7, 4.9, 3.44),
    HotelRatings(2.,  4.5, 2.6, 1.1, 2.8, 2.19),
    HotelRatings(2.5, 3.7, 3.4, 4.5, 2.4, 3.3),
    HotelRatings(2.5, 2.1, 1.1, 1.8, 3.7, 2.14),
    HotelRatings(4.,  3.9, 2.,  4.5, 2.1, 3.44),
    HotelRatings(2.5, 3.1, 3.8, 3.8, 3.3, 3.27),
    HotelRatings(2.,  2.7, 3.8, 2.1, 4.6, 2.82),
    HotelRatings(3.2, 1.1, 4.,  3.1, 4.,  3.29),
    HotelRatings(4.9, 2.3, 2.9, 4.5, 1.6, 3.72)
  };

  RatingCategoryWeightEstimator estimator;
  CategoryToWeightMap result = estimator.estimate(ratingsList);
  // for (pair<string, double> elem: result) {
    // cout<<elem.first<<" "<<elem.second<<" ";
  // }
  for (string category: {"location", "cleanliness","staff", "facilities", "value_for_money"}) {
    cout<<result[category] * (4.9/result["location"])<<" ";
  }
  cout<<endl;
}