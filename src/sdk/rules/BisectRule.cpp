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
using sdk::data::kU;

bool BisectRule::Apply() {
  if (0 == depth_) {
    // End of bisect recursive
    return false;
  }

  bool progress = false;

  // Check each cell for a bisect candidate
  for (auto& collection : puzzle_->GetRowView()) {
    for (data::Cell* cell : collection) {
      progress |= BisectCell(cell);
    }
  }

  return progress;
}

bool BisectRule::BisectCell(data::Cell* cell) {
  if (cell->PossibleValues() > order_ || cell->PossibleValues() == 1) {
    // Either solved cell, or too many options to bisect, no progress
    return false;
  }
  bool progress = false;

  // Set of differences between the current puzzle and bisect results
  std::vector<data::Grid> bisect_results;

  for (data::Digit const& digit : data::kDigits) {
    if (cell->CanBe(digit)) {
      data::Grid copy(*puzzle_);
      copy.GetRowView()[cell->GetRow()][cell->GetColumn()]->Set(digit);

      data::Grid::SolveResult result = Solve(copy, nullptr, order_, depth_ - 1);

      if (result == data::Grid::SolveResult::kBroken) {
        // Trying this option broke the puzzle, the digit we tried cannot be a part
        // of a correct solution
        progress = true;
        cell->Remove(digit);
      } else {
        // Either solved or not solved results. We can't take a solve at face value
        // because the bisect may have fixed an indeterminate puzzle
        bisect_results.push_back(data::Grid(*puzzle_));
        bisect_results.back().RemoveOptions(copy);
      }
    }
  }

  // Go through the bisect results and find any changes shared by all bisect results
  data::Grid shared_results = data::Grid({{kU, kU, kU, kU, kU, kU, kU, kU, kU},
                                          {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                                          {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                                          {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                                          {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                                          {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                                          {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                                          {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                                          {kU, kU, kU, kU, kU, kU, kU, kU, kU}});

  for (data::Grid const& bisect_result : bisect_results) {
    shared_results.IntersectOptions(bisect_result);
  }

  // Apply all the shared progress to the real puzzle
  return progress || puzzle_->RemoveOptions(shared_results);
}