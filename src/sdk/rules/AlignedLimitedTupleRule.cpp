/**
 * AlignedLimitedTupleRule.hpp - Aligned Limit Tuple Rule
 *
 * If N limited tuples of the same digit together touch exactly N
 * distinct collections, then that digit cannot exist withing the
 * touched collections outside the members of the limited tuples.
 *
 * (More commonly known as X-wing, Swordfish, etc.)
 */
#include "sdk/rules/AlignedLimitedTupleRule.hpp"
#include <memory>
#include <set>

using namespace sdk::rules;
using ::sdk::data::Cell;
using ::sdk::data::Collection;
using ::sdk::data::Digit;

AlignedLimitedTupleRule::AlignedLimitedTupleRule(uint8_t order,
                                                 data::LimitedTupleDatabase& database,
                                                 data::View& view)
    : order_(order), database_(database), view_(view) {}

/**
 * Implements IRule::Apply
 */
bool AlignedLimitedTupleRule::Apply() {
  // Iterate over all combinations of limited tuple of order order_
  LimitedTupleList const& limited_tuples = database_.GetTuples();

  if (limited_tuples.size() < order_) {
    // Not enough tuples found for this check
    return false;
  }

  utility::SelectionIterator<LimitedTupleList::const_iterator> iterator(
      limited_tuples.begin(), limited_tuples.end(), order_);

  bool progress = false;
  do {
    progress |= CheckSelection(iterator.GetSelection());
  } while (iterator.Increment());

  return progress;
};

/**
 * Check for any x-wing style patterns in the provided selection of tuples
 */
bool AlignedLimitedTupleRule::CheckSelection(
    std::vector<LimitedTupleList::const_iterator> const& selection) {
  // Selection is only usable if all the associated digits are identical
  Digit const& digit = (**selection[0]).GetDigit();
  for (auto const& it : selection) {
    if ((**it).GetDigit() != digit) {
      return false;
    }
  }

  // Collect all the cells involved in this selection.
  std::set<Cell*> cells;
  for (auto const& it : selection) {
    for (Cell* cell : (**it).GetSelection()) {
      if (cells.count(cell) > 0) {
        // x-wing logic is not valid if limited tuples overlap
        return false;
      }
      cells.emplace(cell);
    }
  }

  std::set<Collection*> collections;
  // For each cell, find the collection it belongs to and save it
  for (Cell* cell : cells) {
    for (Collection& collection : view_) {
      for (Cell* member : collection) {
        if (cell == member) {
          // The cell from the limited tuple touches this collection
          collections.emplace(&collection);
          break;
        }
      }
    }
  }

  // If the number of touched collections matches the order_ of this rule, we've found a pattern
  if (collections.size() != order_) {
    return false;
  }

  // Check all the members of the matched collections and see if we can use this match to make
  // progress
  bool progress = false;
  for (Collection* collection : collections) {
    for (Cell* cell : *collection) {
      if (cells.count(cell) > 0) {
        // This cell is a member of limited tuples, so
        // we can't (logically) change it
        continue;
      }

      // Attempt to remove the digit associated with the tuple
      if (cell->Remove(digit)) {
        progress = true;
      }
    }
  }

  return progress;
}