/**
 * sdk.cpp - Sudoku Solver
 */
#include "sdk.hpp"

#include "sdk/Pipeline.hpp"
#include "sdk/rules/CollectionRule.hpp"
#include "sdk/rules/RepeatedDigitsRule.hpp"
#include "sdk/rules/UniqueSpotRule.hpp"

using namespace sdk;

static rules::CollectionRule* BuildCollectionRule(std::array<data::Collection, 9>& view);

/**
 * Solve the provided puzzle in place.
 *
 * Return true on success, false on failure.
 */
bool sdk::Solve(data::Grid& puzzle) {
  Pipeline pipeline(&puzzle);

  pipeline.AddRule(BuildCollectionRule(puzzle.GetRowView()));
  pipeline.AddRule(BuildCollectionRule(puzzle.GetColumnView()));
  pipeline.AddRule(BuildCollectionRule(puzzle.GetBoxView()));

  return pipeline.Run();
}

static rules::CollectionRule* BuildCollectionRule(std::array<data::Collection, 9>& view) {
  auto rule = new rules::CollectionRule(view);
  rule->AddRule(new rules::RepeatedDigitsRule());
  rule->AddRule(new rules::UniqueSpotRule());
  return rule;
}