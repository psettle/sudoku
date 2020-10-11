/**
 * CollectionRule.hpp - Collection Rule
 *
 * Rule that applies to a collection
 */
#include "sdk/rules/CollectionRule.hpp"

using namespace sdk::rules;

/**
 * CollectionRule ctor
 */
CollectionRule::CollectionRule(data::Grid* puzzle, interfaces::ICollectionRule* rule)
    : puzzle_(puzzle), rule_(std::unique_ptr<interfaces::ICollectionRule>(rule)) {}

/**
 * Apply all rules to each collection.
 */
bool CollectionRule::Apply() {
  bool progress = false;

  // Apply rule to each element of each view
  for (auto& collection : puzzle_->GetBoxView()) {
    progress |= rule_->Apply(collection);
  }
  for (auto& collection : puzzle_->GetRowView()) {
    progress |= rule_->Apply(collection);
  }
  for (auto& collection : puzzle_->GetColumnView()) {
    progress |= rule_->Apply(collection);
  }

  return progress;
}