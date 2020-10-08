/**
 * sdk.cpp - Sudoku Solver
 */
#include "sdk.hpp"

#include "sdk_Pipeline.hpp"
#include "sdk_RepeatedDigitsRule.hpp"

using namespace sdk;

/**
 * Solve the provided puzzle in place.
 *
 * Return true on success, false on failure.
 */
bool sdk::Solve(Grid& puzzle) {
  Pipeline pipeline(&puzzle);

  pipeline.AddRule(new RepeatedDigitsRule(&puzzle.GetRowView()));
  pipeline.AddRule(new RepeatedDigitsRule(&puzzle.GetColumnView()));
  pipeline.AddRule(new RepeatedDigitsRule(&puzzle.GetBoxView()));

  return pipeline.Run();
}