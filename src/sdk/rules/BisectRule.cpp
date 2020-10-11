/**
 * BisectRule.hpp - Bisect Rule
 *
 * Educated guess and check. Find cells with highly restricted options
 * and try the options to see if they break the grid or lead to shared outcomes.
 */
#include "sdk/rules/BisectRule.hpp"
#include "sdk/data/Cell.hpp"
#include "sdk/sdk.hpp"

using namespace sdk::rules;
using ::sdk::data::Cell;
using ::sdk::data::Digit;
using ::sdk::data::Grid;
using ::sdk::data::kU;

/**
 * BisectRule ctor
 */
BisectRule::BisectRule(data::Grid* puzzle, uint8_t order, uint32_t depth)
    : puzzle_(puzzle), order_(order), depth_(depth), observer_(nullptr) {}

/**
 * Set an observer for bisect progress updates
 */
void BisectRule::SetObserver(interfaces::ISolveObserver* observer) {
  if (observer) {
    observer_ = observer;
  }
}

/**
 * Attempt a bisect on every cell of the grid
 */
bool BisectRule::Apply() {
  if (0 == depth_) {
    // End of bisect recursive
    return false;
  }

  bool progress = false;

  // Check each cell for a bisect candidate
  for (auto& collection : puzzle_->GetRowView()) {
    for (Cell* cell : collection) {
      progress |= BisectCell(cell);
    }
  }

  return progress;
}

/**
 * See if the provided cell is a good bisect option, then
 * run a bisect on it.
 */
bool BisectRule::BisectCell(Cell* cell) {
  if (cell->PossibleValues() > order_ || cell->PossibleValues() == 1) {
    // Either solved cell, or too many options to bisect, no progress
    return false;
  }
  bool progress = false;

  // Set of differences between the current puzzle and bisect results
  std::vector<Grid> bisect_results;

  for (Digit const& digit : data::kDigits) {
    if (cell->CanBe(digit)) {
      Grid copy(*puzzle_);

      // Try the selected digit on the copy
      copy.GetRowView()[cell->GetRow()][cell->GetColumn()]->Set(digit);
      SendBisectStart(*cell, digit);
      Grid::SolveResult result = Solve(copy, observer_, order_, depth_ - 1);

      if (result == Grid::SolveResult::kBroken) {
        // Trying this option broke the puzzle, the digit we tried cannot be a part
        // of a correct solution
        progress = true;
        cell->Remove(digit);
        SendBisectBreak(*cell, digit);
      } else {
        // Either solved or not solved results. We can't take a solve at face value
        // because the bisect may have fixed an indeterminate puzzle
        bisect_results.push_back(Grid(*puzzle_));
        bisect_results.back().RemoveOptions(copy);
      }
    }
  }

  // Go through the bisect results and find any changes shared by all bisect results
  Grid shared_results = Grid({{kU, kU, kU, kU, kU, kU, kU, kU, kU},
                              {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                              {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                              {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                              {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                              {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                              {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                              {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                              {kU, kU, kU, kU, kU, kU, kU, kU, kU}});

  for (Grid const& bisect_result : bisect_results) {
    shared_results.IntersectOptions(bisect_result);
  }

  // Apply all the shared progress to the real puzzle
  return progress || puzzle_->RemoveOptions(shared_results);
}

/**
 * Send a bisect start notification to observer
 */
void BisectRule::SendBisectStart(Cell const& target, Digit const& digit) const {
  if (observer_) {
    observer_->OnBisectStart(target, digit);
  }
}

/**
 * Send an impossible digit notification to observers
 */
void BisectRule::SendBisectBreak(Cell const& target, Digit const& impossible_value) const {
  if (observer_) {
    observer_->OnBisectBreak(target, impossible_value);
  }
}

/**
 * Send a bisect start notification to observer
 */
void BisectRule::SendBisectComplete(Grid const& impossible_values) const {
  if (observer_) {
    observer_->OnBisectComplete(impossible_values);
  }
}