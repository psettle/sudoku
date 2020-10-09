/**
 * CollectionRule.hpp - Collection Rule
 *
 * Rule that applies to a collection
 */
#include "sdk/rules/CollectionRule.hpp"

using namespace sdk::rules;
using ::sdk::data::Collection;

CollectionRule::CollectionRule(std::array<Collection, 9>& view) : view_(view) {}

bool CollectionRule::Apply() {
  bool progress = false;
  // Apply rule to each element of the view
  for (auto& collection : view_) {
    for (auto& rule : rules_) {
      progress |= rule->Apply(collection);
    }
  }

  return progress;
}