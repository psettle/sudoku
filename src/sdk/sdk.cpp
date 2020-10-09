/**
 * sdk.cpp - Sudoku Solver
 */
#include "sdk.hpp"
#include "sdk/Pipeline.hpp"
#include "sdk/data/LimitedTupleDatabase.hpp"
#include "sdk/rules/CollectionRule.hpp"
#include "sdk/rules/ExclusiveTupleRule.hpp"
#include "sdk/rules/LimitedTupleIdentifier.hpp"
#include "sdk/rules/LimitedTupleMatcher.hpp"
#include "sdk/rules/LimitedTupleTrimmer.hpp"

using namespace sdk;

static rules::CollectionRule* BuildCollectionRule(data::View& view,
                                                  data::LimitedTupleDatabase& database);

/**
 * Solve the provided puzzle in place.
 *
 * Return true on success, false on failure.
 */
bool sdk::Solve(data::Grid& puzzle) {
  Pipeline pipeline(&puzzle);

  data::LimitedTupleDatabase database;

  pipeline.AddRule(BuildCollectionRule(puzzle.GetRowView(), database));
  pipeline.AddRule(BuildCollectionRule(puzzle.GetColumnView(), database));
  pipeline.AddRule(BuildCollectionRule(puzzle.GetBoxView(), database));
  pipeline.AddRule(new rules::LimitedTupleTrimmer(database));

  return pipeline.Run();
}

static rules::CollectionRule* BuildCollectionRule(data::View& view,
                                                  data::LimitedTupleDatabase& database) {
  auto rule = new rules::CollectionRule(view);
  rule->AddRule(new rules::ExclusiveTupleRule(1));
  rule->AddRule(new rules::ExclusiveTupleRule(2));
  rule->AddRule(new rules::ExclusiveTupleRule(3));
  rule->AddRule(new rules::ExclusiveTupleRule(4));
  rule->AddRule(new rules::ExclusiveTupleRule(5));
  rule->AddRule(new rules::LimitedTupleIdentifier(1, database));
  rule->AddRule(new rules::LimitedTupleIdentifier(2, database));
  rule->AddRule(new rules::LimitedTupleIdentifier(3, database));
  rule->AddRule(new rules::LimitedTupleMatcher(database));
  return rule;
}