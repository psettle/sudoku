/**
 * LimitedTuple.cpp - Limit Tuple
 *
 * A set of digits where one of them must be a specific digit
 */
#include "sdk/data/LimitedTuple.hpp"
#include <set>

using namespace sdk::data;

using ::sdk::data::Cell;
using ::sdk::data::Digit;

/**
 * Create a new limited tuple from a selection of cells and a digit that
 * must exist in that selection.
 */
LimitedTuple::LimitedTuple(std::vector<Cell*> selection, Digit const& digit)
    : selection_(selection), digit_(digit) {}

/**
 * Get the cells this limited tuple applies to.
 */
std::vector<Cell*> const& LimitedTuple::GetSelection() const { return selection_; }

/**
 * Get the digit this limited tuple must contain.
 */
Digit const& LimitedTuple::GetDigit() const { return digit_; }

/**
 * Check if this limited tuple is equal to other.
 *
 * The order of selection is not relevant to equality.
 */
bool LimitedTuple::operator==(LimitedTuple const& other) const {
  // Check that order and digit match
  if (digit_ != other.digit_) {
    return false;
  }

  if (selection_.size() != other.selection_.size()) {
    return false;
  }

  // Now we need to check if these sets reference all the same digits
  std::set<Digit*> temp;

  for (Digit* digit : other.selection_) {
    temp.emplace(digit);
  }

  for (Digit* digit : selection_) {
    temp.erase(digit);
  }

  // If temp is empty the tuples contained the same elements
  return temp.size() == 0;
}