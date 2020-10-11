/**
 * LimitedTupleIdentifier.cpp - Limited Tuple Identifier
 *
 * Identify cases where a digit is restricted to a subset of
 * cells within a collection.
 */
#include "sdk/rules/LimitedTupleIdentifier.hpp"
#include "sdk/utility/SelectionIterator.hpp"

using namespace sdk::rules;
using ::sdk::data::Cell;
using ::sdk::data::Collection;
using ::sdk::data::Digit;

/**
 * LimitedTupleIdentifier ctor
 */
LimitedTupleIdentifier::LimitedTupleIdentifier(uint8_t order, data::LimitedTupleDatabase* database)
    : order_(order), database_(database), observer_(nullptr) {}

/**
 * Set a listener for limited tuple identification
 */
void LimitedTupleIdentifier::SetObserver(interfaces::ILimitedTupleObserver* observer) {
  if (observer) {
    observer_ = observer;
  }
}

/**
 * Look for limited tuples and add the the shared database
 */
bool LimitedTupleIdentifier::Apply(Collection& collection) {
  bool progress = false;
  // Initialize a set of iterators, we will be running through all combinations
  utility::SelectionIterator<Collection::iterator> it(collection.begin(), collection.end(), order_);

  do {
    for (Digit const& digit : data::kDigits) {
      progress |= CheckSelection(collection, it.GetSelection(), digit);
    }
  } while (it.Increment());

  return progress;
}

/**
 * Check if the provided selection is a limited tuple.
 */
bool LimitedTupleIdentifier::CheckSelection(Collection& collection,
                                            std::vector<data::Collection::iterator>& selection,
                                            data::Digit const& digit) {
  // To be a limited tuple, digit must be an option on all elements of selection, and no other
  // elements of collection
  for (Cell** el : selection) {
    if (!(*el)->CanBe(digit)) {
      // Digit is not present in each element of the selection.
      return false;
    }
  }

  for (Cell* cell : collection) {
    if (cell->CanBe(digit)) {
      bool in_selection = false;
      for (Cell** el : selection) {
        if (*el == cell) {
          in_selection = true;
        }
      }

      if (!in_selection) {
        // digit is an option outside of the tuple.
        return false;
      }
    }
  }

  // digit is only present within the provided selection, so it is a limited tuple

  // handle the trivial order_ == 1 case to start
  if (order_ == 1) {
    if (!(*selection[0])->IsSolved()) {
      // Found an order 1 case that was unsolved, so this is actually a solved digit
      (**selection[0]).Set(digit);
      return true;
    } else {
      // Found an order 1 case, but it was already a solved digit so we didn't make progress
      return false;
    }
  }

  // Save the limited tuple to the database
  // The database will decide if the tuple is a new find
  std::vector<Cell*> tuple;
  for (Cell** el : selection) {
    tuple.push_back(*el);
  }

  data::LimitedTuple* new_tuple = new data::LimitedTuple(tuple, digit);

  if (database_->Add(new_tuple)) {
    SendProgress(*new_tuple);
    return true;
  } else {
    return false;
  }
}

/**
 * Send a notification describing the logical progress that was made to observer
 */
void LimitedTupleIdentifier::SendProgress(data::LimitedTuple const& tuple) const {
  if (observer_) {
    observer_->OnLimitedTupleIdentified(tuple);
  }
}