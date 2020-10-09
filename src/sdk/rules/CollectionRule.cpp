/**
 * CollectionRule.hpp - Collection Rule
 *
 * Rule that applies to a collection
 */
#include "sdk/rules/CollectionRule.hpp"

using namespace sdk::rules;

CollectionRule::CollectionRule(data::View& view) : view_(view) {}

void CollectionRule::AddRule(interfaces::ICollectionRule* rule) {
  rules_.push_back(std::unique_ptr<interfaces::ICollectionRule>(rule));
}

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