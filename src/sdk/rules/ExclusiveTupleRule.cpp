/**
 * ExclusiveTupleRule.hpp - Exclusive Tuple Rule
 *
 * If N cells consist of N possible digits, those digits cannot exist
 * in any other cells
 */
#include "sdk/rules/ExclusiveTupleRule.hpp"

#include <vector>

using namespace sdk::rules;
using ::sdk::data::Collection;
using ::sdk::data::Digit;

bool ExclusiveTupleRule::Apply(Collection& collection) {
  bool progress = false;
  // Initialize a set of iterators, we will be running through all combinations
  std::vector<Collection::iterator> it;
  for (size_t i = 0; i < order_; ++i) {
    it.push_back(collection.begin() + i);
  }

  do {
    // Add up the total number of digits represented by the selected combination
    Digit count(0);
    for (Collection::iterator& el : it) {
      count.Add(**el);
    }

    if (count.PossibleValues() == order_) {
      // The currently selected tuple contains order_ unique values, so the values
      // represented by count cannot exist in the rest of the collection
      for (Digit* digit : collection) {
        // Create a temp to check that removing count doesn't leave no possible values
        // (If it did leave no possible values, then it was a member of the tuple and shouldn't be
        // changed)
        Digit temp = *digit;
        if (temp.Remove(count) && temp.PossibleValues() > 0) {
          *digit = temp;
          progress = true;
        }
      }
    }
  } while (Increment(it, collection.end()));

  return progress;
}

bool ExclusiveTupleRule::Increment(std::vector<Collection::iterator>& iterator,
                                   Collection::iterator const& end, uint8_t order) {
  if (order == iterator.size()) {
    // Hit end of possible combinations
    return false;
  }

  // Increment iterator at the provided order
  iterator[iterator.size() - order - 1]++;

  if (iterator[iterator.size() - order - 1] == end - order) {
    // Iterator reached the last viable element, increment the higher order iterator and reset
    // ourselves to right after.
    if (Increment(iterator, end, order + 1)) {
      iterator[iterator.size() - order - 1] = iterator[iterator.size() - order - 2] + 1;
      return true;
    } else {
      // Incrementing the higher order iterator failed, so we are done.
      return false;
    }
  } else {
    // Iterator landed on a valid element, success.
    return true;
  }
}