/**
 * LimitedTupleIdentifier.cpp - Limited Tuple Identifier
 *
 * Identify cases where a digit is restricted to a subset of
 * cells within a collection.
 */
#include "sdk/rules/LimitedTupleIdentifier.hpp"
#include "sdk/utility/SelectionIterator.hpp"

using namespace sdk::rules;
using ::sdk::data::Collection;
using ::sdk::data::Digit;

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
  for (Digit** el : selection) {
    if (!(*el)->CanBe(digit)) {
      // Digit is not present in each element of the selection.
      return false;
    }
  }

  for (Digit* cell : collection) {
    if (cell->CanBe(digit)) {
      bool in_selection = false;
      for (Digit** el : selection) {
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
      **selection[0] = digit;
      return true;
    } else {
      // Found an order 1 case, but it was already a solved digit so we didn't make progress
      return false;
    }
  }

  // Save the limited tuple to the database
  // The database will decide if the tuple is a new find
  std::vector<Digit*> tuple;
  for (Digit** el : selection) {
    tuple.push_back(*el);
  }

  return database_.Add(new data::LimitedTuple(tuple, digit));
}