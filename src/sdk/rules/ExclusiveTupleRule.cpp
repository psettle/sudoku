/**
 * ExclusiveTupleRule.hpp - Exclusive Tuple Rule
 *
 * If N cells consist of N possible digits, those digits cannot exist
 * in any other cells
 */
#include "sdk/rules/ExclusiveTupleRule.hpp"

using namespace sdk::rules;
using ::sdk::data::Cell;
using ::sdk::data::Collection;
using ::sdk::data::Digit;

/**
 * CollectionRule ctor
 */
ExclusiveTupleRule::ExclusiveTupleRule(uint8_t order) : order_(order), listener_(nullptr) {}

/**
 * Set a listener for exclusive tuple progress
 */
void ExclusiveTupleRule::SetListener(interfaces::IExclusiveTupleListener* listener) {
  if (listener) {
    listener_ = listener;
  }
}

/**
 * Apply the exclusive tubple rule to the provided collection
 */
bool ExclusiveTupleRule::Apply(Collection& collection) {
  bool progress = false;
  // Initialize a set of iterators, we will be running through all combinations
  utility::SelectionIterator<Collection::iterator> it(collection.begin(), collection.end(), order_);
  do {
    // Add up the total number of digits represented by the selected combination
    Digit count = data::kN;
    for (Collection::iterator& el : it.GetSelection()) {
      count.Add(**el);
    }

    if (count.PossibleValues() == order_) {
      // The currently selected tuple contains order_ unique values, so the values
      // represented by count cannot exist in the rest of the collection
      for (Cell* cell : collection) {
        // If cell is not in the exclusive tuple, remove all values from it
        // that are in the exclusive tuple
        bool found = false;
        for (Collection::iterator& el : it.GetSelection()) {
          if (*el == cell) {
            found = true;
          }
        }
        if (!found && cell->Remove(count)) {
          progress = true;
          SendProgress(it, count, *cell);
        }
      }
    }
  } while (it.Increment());

  return progress;
}

/**
 * Send a notification describing the logical progress that was made to listener
 */
void ExclusiveTupleRule::SendProgress(
    utility::SelectionIterator<Collection::iterator> const& exclusive_tuple,
    Digit const& exclusive_values, Cell const& removed_from) const {
  // Copy tuple from iterator into vector for listener interface
  std::vector<Cell const*> tuple;
  for (auto& it : exclusive_tuple.GetSelection()) {
    tuple.push_back(*it);
  }

  if (listener_) {
    listener_->OnExclusiveTupleProgress(tuple, exclusive_values, removed_from);
  }
}
