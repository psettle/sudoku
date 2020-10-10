/**
 * sdk.cpp - Sudoku Solver
 */
#include "sdk.hpp"
#include <iostream>
#include "sdk/Pipeline.hpp"
#include "sdk/data/LimitedTupleDatabase.hpp"
#include "sdk/rules/AlignedLimitedTupleRule.hpp"
#include "sdk/rules/CollectionRule.hpp"
#include "sdk/rules/ExclusiveTupleRule.hpp"
#include "sdk/rules/LimitedTupleIdentifier.hpp"
#include "sdk/rules/LimitedTupleMatcher.hpp"
#include "sdk/rules/LimitedTupleTrimmer.hpp"

using namespace sdk;

static rules::CollectionRule* BuildCollectionRule(data::View& view,
                                                  data::LimitedTupleDatabase& database,
                                                  interfaces::ISolveObserver* observer);

/**
 * Solve the provided puzzle in place.
 *
 * Return true on success, false on failure.
 */
bool sdk::Solve(data::Grid& puzzle, interfaces::ISolveObserver* observer) {
  Pipeline pipeline(&puzzle);

  data::LimitedTupleDatabase database;

  pipeline.AddRule(BuildCollectionRule(puzzle.GetRowView(), database, observer));
  pipeline.AddRule(BuildCollectionRule(puzzle.GetColumnView(), database, observer));
  pipeline.AddRule(BuildCollectionRule(puzzle.GetBoxView(), database, observer));

  auto limited_tuple_trimmer = new rules::LimitedTupleTrimmer(database);
  limited_tuple_trimmer->AddObserver(observer);
  pipeline.AddRule(limited_tuple_trimmer);

  auto aligned_rule = new rules::AlignedLimitedTupleRule(2, database, puzzle.GetColumnView());
  pipeline.AddRule(aligned_rule);
  aligned_rule = new rules::AlignedLimitedTupleRule(2, database, puzzle.GetColumnView());
  pipeline.AddRule(aligned_rule);
  aligned_rule = new rules::AlignedLimitedTupleRule(2, database, puzzle.GetBoxView());
  pipeline.AddRule(aligned_rule);

  aligned_rule = new rules::AlignedLimitedTupleRule(3, database, puzzle.GetRowView());
  pipeline.AddRule(aligned_rule);
  aligned_rule = new rules::AlignedLimitedTupleRule(3, database, puzzle.GetColumnView());
  pipeline.AddRule(aligned_rule);
  aligned_rule = new rules::AlignedLimitedTupleRule(3, database, puzzle.GetBoxView());
  pipeline.AddRule(aligned_rule);

  return pipeline.Run();
}

static rules::CollectionRule* BuildCollectionRule(data::View& view,
                                                  data::LimitedTupleDatabase& database,
                                                  interfaces::ISolveObserver* observer) {
  rules::ExclusiveTupleRule* exclusive_tuple_rule;
  rules::LimitedTupleIdentifier* limited_tuple_identifier;
  rules::CollectionRule* rule = new rules::CollectionRule(view);

  exclusive_tuple_rule = new rules::ExclusiveTupleRule(1);
  exclusive_tuple_rule->AddListener(observer);
  rule->AddRule(exclusive_tuple_rule);

  exclusive_tuple_rule = new rules::ExclusiveTupleRule(2);
  exclusive_tuple_rule->AddListener(observer);
  rule->AddRule(exclusive_tuple_rule);

  exclusive_tuple_rule = new rules::ExclusiveTupleRule(3);
  exclusive_tuple_rule->AddListener(observer);
  rule->AddRule(exclusive_tuple_rule);

  exclusive_tuple_rule = new rules::ExclusiveTupleRule(4);
  exclusive_tuple_rule->AddListener(observer);
  rule->AddRule(exclusive_tuple_rule);

  exclusive_tuple_rule = new rules::ExclusiveTupleRule(5);
  exclusive_tuple_rule->AddListener(observer);
  rule->AddRule(exclusive_tuple_rule);

  limited_tuple_identifier = new rules::LimitedTupleIdentifier(1, database);
  limited_tuple_identifier->AddObserver(observer);
  rule->AddRule(limited_tuple_identifier);

  limited_tuple_identifier = new rules::LimitedTupleIdentifier(2, database);
  limited_tuple_identifier->AddObserver(observer);
  rule->AddRule(limited_tuple_identifier);

  limited_tuple_identifier = new rules::LimitedTupleIdentifier(3, database);
  limited_tuple_identifier->AddObserver(observer);
  rule->AddRule(limited_tuple_identifier);

  rules::LimitedTupleMatcher* limited_tuple_matcher = new rules::LimitedTupleMatcher(database);
  limited_tuple_matcher->AddObserver(observer);
  rule->AddRule(limited_tuple_matcher);

  return rule;
}