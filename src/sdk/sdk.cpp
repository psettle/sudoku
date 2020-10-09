/**
 * sdk.cpp - Sudoku Solver
 */
#include "sdk.hpp"

#include "sdk/Pipeline.hpp"
#include "sdk/rules/CollectionRule.hpp"
#include "sdk/rules/ExclusiveTupleRule.hpp"
#include "sdk/rules/UniqueSpotRule.hpp"

using namespace sdk;

static rules::CollectionRule* BuildCollectionRule(data::View& view);

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

static rules::CollectionRule* BuildCollectionRule(data::View& view) {
  auto rule = new rules::CollectionRule(view);
  rule->AddRule(new rules::UniqueSpotRule());
  rule->AddRule(new rules::ExclusiveTupleRule(1));
  rule->AddRule(new rules::ExclusiveTupleRule(2));
  rule->AddRule(new rules::ExclusiveTupleRule(3));
  rule->AddRule(new rules::ExclusiveTupleRule(4));
  rule->AddRule(new rules::ExclusiveTupleRule(5));
  rule->AddRule(new rules::ExclusiveTupleRule(6));
  rule->AddRule(new rules::ExclusiveTupleRule(7));
  rule->AddRule(new rules::ExclusiveTupleRule(8));
  return rule;
}