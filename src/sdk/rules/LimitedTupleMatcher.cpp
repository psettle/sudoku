/**
 * LimitedTupleMatcher.hpp - Limited Tuple Matcher
 *
 * Use limited tuples that have already been found to
 * eliminate possible values from collections.
 */
#include "sdk/rules/LimitedTupleMatcher.hpp"

using namespace sdk::rules;
using ::sdk::data::Cell;
using ::sdk::data::Collection;
using ::sdk::data::Digit;

/**
 * LimitedTupleMatcher ctor
 */
LimitedTupleMatcher::LimitedTupleMatcher(data::LimitedTupleDatabase* database)
    : database_(database), observer_(nullptr) {}

/**
 * Set an observer for limited tuple usage notifications
 */
void LimitedTupleMatcher::SetObserver(interfaces::ILimitedTupleObserver* observer) {
  if (observer) {
    observer_ = observer;
  }
}

/**
 * Apply the exclusive tubple rule to the provided collection
 */
bool LimitedTupleMatcher::Apply(Collection& collection) {
  bool progress = false;

  for (auto const& tuple : database_->GetTuples()) {
    progress |= UseTuple(collection, *tuple);
  }

  return progress;
}

/**
 * Make any progress possible by comparing tuple to collection
 */
bool LimitedTupleMatcher::UseTuple(data::Collection& collection, data::LimitedTuple const& tuple) {
  // Check that the tuple is completely in the collection
  for (Digit const* tuple_digit : tuple.GetSelection()) {
    bool found = false;
    for (Digit* digit : collection) {
      if (digit == tuple_digit) {
        found = true;
        break;
      }
    }

    if (!found) {
      // Can't use this tuple, it isn't contained in collection
      return false;
    }
  }

  bool progress = false;
  // Find all the digits in collection that aren't in the tuple
  for (Cell* digit : collection) {
    bool found = false;
    for (Digit const* tuple_digit : tuple.GetSelection()) {
      if (digit == tuple_digit) {
        found = true;
        break;
      }
    }

    if (!found) {
      // Digit isn't is tuple, so it is a candidate to make progress on
      if (digit->Remove(tuple.GetDigit())) {
        progress = true;
        SendProgress(tuple, *digit);
      }
    }
  }

  return progress;
}

/**
 * Send a notification describing the logical progress that was made to observer
 */
void LimitedTupleMatcher::SendProgress(data::LimitedTuple const& tuple,
                                       data::Cell const& progressed_cell) const {
  if (observer_) {
    observer_->OnLimitedTupleProgress(tuple, progressed_cell);
  }
}