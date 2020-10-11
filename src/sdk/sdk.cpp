/**
 * sdk.cpp - Sudoku Solver
 */
#include "sdk.hpp"
#include <iostream>
#include "sdk/Pipeline.hpp"
#include "sdk/data/LimitedTupleDatabase.hpp"
#include "sdk/rules/AlignedLimitedTupleRule.hpp"
#include "sdk/rules/BisectRule.hpp"
#include "sdk/rules/CollectionRule.hpp"
#include "sdk/rules/ExclusiveTupleRule.hpp"
#include "sdk/rules/LimitedTupleIdentifier.hpp"
#include "sdk/rules/LimitedTupleMatcher.hpp"
#include "sdk/rules/LimitedTupleTrimmer.hpp"

using namespace sdk;

/**
 * Solve the provided puzzle in place.
 */
data::Grid::SolveResult sdk::Solve(data::Grid& puzzle, interfaces::ISolveObserver* observer,
                                   uint8_t bisect_order, uint32_t bisect_depth) {
  Pipeline pipeline(&puzzle);

  data::LimitedTupleDatabase database;

  auto exclusive_tuple_rule = new rules::ExclusiveTupleRule(1);
  exclusive_tuple_rule->SetListener(observer);
  pipeline.AddTrivialRule(new rules::CollectionRule(&puzzle, exclusive_tuple_rule));

  exclusive_tuple_rule = new rules::ExclusiveTupleRule(2);
  exclusive_tuple_rule->SetListener(observer);
  pipeline.AddTrivialRule(new rules::CollectionRule(&puzzle, exclusive_tuple_rule));

  exclusive_tuple_rule = new rules::ExclusiveTupleRule(3);
  exclusive_tuple_rule->SetListener(observer);
  pipeline.AddComplexRule(new rules::CollectionRule(&puzzle, exclusive_tuple_rule));

  exclusive_tuple_rule = new rules::ExclusiveTupleRule(4);
  exclusive_tuple_rule->SetListener(observer);
  pipeline.AddComplexRule(new rules::CollectionRule(&puzzle, exclusive_tuple_rule));

  exclusive_tuple_rule = new rules::ExclusiveTupleRule(5);
  exclusive_tuple_rule->SetListener(observer);
  pipeline.AddHammerRule(new rules::CollectionRule(&puzzle, exclusive_tuple_rule));

  auto limited_tuple_identifier = new rules::LimitedTupleIdentifier(1, &database);
  limited_tuple_identifier->SetObserver(observer);
  pipeline.AddTrivialRule(new rules::CollectionRule(&puzzle, limited_tuple_identifier));

  limited_tuple_identifier = new rules::LimitedTupleIdentifier(2, &database);
  limited_tuple_identifier->SetObserver(observer);
  pipeline.AddComplexRule(new rules::CollectionRule(&puzzle, limited_tuple_identifier));

  limited_tuple_identifier = new rules::LimitedTupleIdentifier(3, &database);
  limited_tuple_identifier->SetObserver(observer);
  pipeline.AddComplexRule(new rules::CollectionRule(&puzzle, limited_tuple_identifier));

  auto limited_tuple_trimmer = new rules::LimitedTupleTrimmer(&database);
  limited_tuple_trimmer->SetObserver(observer);
  pipeline.AddComplexRule(limited_tuple_trimmer);

  auto limited_tuple_matcher = new rules::LimitedTupleMatcher(&database);
  limited_tuple_matcher->SetObserver(observer);
  pipeline.AddComplexRule(new rules::CollectionRule(&puzzle, limited_tuple_matcher));

  auto aligned_rule = new rules::AlignedLimitedTupleRule(2, &database, &puzzle.GetColumnView());
  aligned_rule->SetListener(observer);
  pipeline.AddHammerRule(aligned_rule);
  aligned_rule = new rules::AlignedLimitedTupleRule(2, &database, &puzzle.GetColumnView());
  aligned_rule->SetListener(observer);
  pipeline.AddHammerRule(aligned_rule);
  aligned_rule = new rules::AlignedLimitedTupleRule(2, &database, &puzzle.GetBoxView());
  aligned_rule->SetListener(observer);
  pipeline.AddHammerRule(aligned_rule);

  aligned_rule = new rules::AlignedLimitedTupleRule(3, &database, &puzzle.GetRowView());
  aligned_rule->SetListener(observer);
  pipeline.AddHammerRule(aligned_rule);
  aligned_rule = new rules::AlignedLimitedTupleRule(3, &database, &puzzle.GetColumnView());
  aligned_rule->SetListener(observer);
  pipeline.AddHammerRule(aligned_rule);
  aligned_rule = new rules::AlignedLimitedTupleRule(3, &database, &puzzle.GetBoxView());
  aligned_rule->SetListener(observer);
  pipeline.AddHammerRule(aligned_rule);

  auto bisect = new rules::BisectRule(&puzzle, bisect_order, bisect_depth);
  bisect->SetObserver(observer);
  pipeline.AddHammerRule(bisect);

  return pipeline.Run();
}