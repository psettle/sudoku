/**
 * ExclusiveTupleRule.hpp - Exclusive Tuple Rule
 *
 * If N cells consist of N possible digits, those digits cannot exist
 * in any other cells
 */
#include "sdk/rules/ExclusiveTupleRule.hpp"
#include "sdk/utility/SelectionIterator.hpp"

using namespace sdk::rules;
using ::sdk::data::Collection;
using ::sdk::data::Digit;

/**
 * Apply the exclusive tubple rule to the provided collection
 */
bool ExclusiveTupleRule::Apply(Collection& collection) {
  bool progress = false;
  // Initialize a set of iterators, we will be running through all combinations
  utility::SelectionIterator<Collection::iterator> it(collection.begin(), collection.end(), order_);

  do {
    // Add up the total number of digits represented by the selected combination
    Digit count(0);
    for (Collection::iterator& el : it.GetSelection()) {
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
  } while (it.Increment());

  return progress;
}